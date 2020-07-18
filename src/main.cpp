#include <cstdio>

// general YAHAL includes
#include "adc14_msp432.h"
#include "gpio_msp432.h"
#include "timer_msp432.h"

// GUI display includes
#include "font_6x10.h"
#include "spi_msp432.h"
#include "st7735s_drv.h"
#include "uGUI.h"
#include "uGUI_colors.h"

// project includes
#include "Debouncer.hpp"
#include "DrawInterface.hpp"
#include "Machine.hpp"
#include "Model.hpp"

gpio_msp432_pin s1(PORT_PIN(5, 1));
gpio_msp432_pin s2(PORT_PIN(3, 5));

gpio_msp432_pin dirPin1(PORT_PIN(6, 1));
gpio_msp432_pin stepPin1(PORT_PIN(4, 0));
gpio_msp432_pin dirPin2(PORT_PIN(4, 5));
gpio_msp432_pin stepPin2(PORT_PIN(4, 7));

gpio_msp432_pin servo(PORT_PIN(2, 5));

adc14_msp432_channel joy_X(15);
adc14_msp432_channel joy_Y(9);

MATSE::MCT::ButtonDebouncer a_debouncer{};
MATSE::MCT::ButtonDebouncer b_debouncer{};
MATSE::MCT::JoystickDebouncer joystick_debouncer{};

bool buttonIsPressed() { return !s1.gpioRead(); }

bool button2IsPressed() { return !s2.gpioRead(); }

MATSE::MCT::Model model{};

char textBuffer[200];
int i{};

void callback(void *arg) {

  auto m = static_cast<MATSE::MCT::Machine *>(arg);
  // if (i == 0 || i == 60000 / 2) {
  //   snprintf(textBuffer, sizeof(textBuffer), "i: %d, x: %f, y: %f\n", i,
  //            model.getCurrentX(), model.getCurrentY());
  //   m->getDrawer().print(textBuffer);
  // }
  a_debouncer.add(MATSE::MCT::ButtonA{buttonIsPressed()});
  b_debouncer.add(MATSE::MCT::ButtonB{button2IsPressed()});
  auto x = joy_X.adcReadRaw();
  auto y = joy_Y.adcReadRaw();
  const auto middle = 512;
  const auto margin = 100;
  const MATSE::MCT::JoystickSample joystickSample{.left{x < middle - margin},
                                                  .right{x > middle + margin},
                                                  .up{y > middle + margin},
                                                  .down{y < middle - margin}};

  joystick_debouncer.add(joystickSample);
  if (a_debouncer.isKeyUp()) {
    m->on(MATSE::MCT::a_button_up{});
  }
  if (b_debouncer.isKeyUp()) {
    m->on(MATSE::MCT::b_button_up{});
  }
  if (joystick_debouncer.isDownPress()) {
    m->on(MATSE::MCT::joystick_down{});
  }
  if (joystick_debouncer.isUpPress()) {
    m->on(MATSE::MCT::joystick_up{});
  }
  if (joystick_debouncer.isLeftPress()) {
    m->on(MATSE::MCT::joystick_left{});
  }
  if (joystick_debouncer.isRightPress()) {
    m->on(MATSE::MCT::joystick_right{});
  }
  if (i % 5 == 0) {
    m->on(joystickSample);
  }

  stepPin1.gpioWrite(model.getMotor1Step());
  stepPin2.gpioWrite(model.getMotor2Step());
  dirPin1.gpioWrite(model.getMotor1Dir());
  dirPin2.gpioWrite(model.getMotor2Dir());
  model.timeStep();
  i += 1;
}

int main() {
  s1.gpioMode(GPIO::INPUT | GPIO::PULLUP);
  s2.gpioMode(GPIO::INPUT | GPIO::PULLUP);
  servo.gpioMode(GPIO::OUTPUT);
  // Ying - Microcontroller Engineering - Table 7.9
  // P2.5 (servo) is now driven by TA0.2 (TIMER_A0, CCR 2)
  servo.setSEL(1);

  dirPin1.gpioMode(GPIO::OUTPUT);
  stepPin1.gpioMode(GPIO::OUTPUT);
  dirPin2.gpioMode(GPIO::OUTPUT);
  stepPin2.gpioMode(GPIO::OUTPUT);

  dirPin1.gpioWrite(HIGH);
  dirPin2.gpioWrite(HIGH);

  // Setup SPI interface
  gpio_msp432_pin lcd_cs(PORT_PIN(5, 0));
  spi_msp432 spi{EUSCI_B0_SPI, lcd_cs};
  spi.setSpeed(24e6);

  // Setup LCD driver
  gpio_msp432_pin lcd_rst(PORT_PIN(5, 7));
  gpio_msp432_pin lcd_dc(PORT_PIN(3, 7));
  st7735s_drv lcd{spi, lcd_rst, lcd_dc, st7735s_drv::Crystalfontz_128x128};

  // Setup uGUI
  uGUI gui{lcd};
  gui.FillScreen(C_BLACK);
  gui.FontSelect(&FONT_6X10);
  gui.ConsoleSetArea(0, 0, 127, 127);
  gui.ConsoleSetBackcolor(C_BLACK);
  gui.ConsoleSetForecolor(C_WHITE);
  MATSE::MCT::uGUIDrawer::gui = &gui;
  MATSE::MCT::uGUIDrawer::lcd = &lcd;

  joy_Y.adcMode(ADC::ADC_10_BIT);
  joy_X.adcMode(ADC::ADC_10_BIT);

  MATSE::MCT::Machine machine{};
  machine.start();

  // MATSE::MCT::Buffer buffer{};
  // for (int i = 0; i < 128 * 128; i += 1) {
  //   if (i % 5 == 0) {
  //     buffer[i] = true;
  //   }
  // }
  // machine.drawer.print(buffer, C_HOT_PINK, C_INDIGO);
  // textBuffer[10] = 0;
  // const int start = 17;
  // for (int i = start; i < 100; i += 1) {
  //   textBuffer[(i - start) % 10] = i;
  //   if ((i - start) % 10 == 0) {
  //     machine.drawer.print(textBuffer);
  //   }
  // }
  timer_msp432 timer;
  timer.setPeriod(10 * 1000, TIMER::PERIODIC);
  timer.setCallback(callback, &machine);

  // timer_msp432 timer2(TIMER32_2);
  // timer2.setPeriod(500, TIMER::PERIODIC);
  // timer2.setCallback(callback2, &model);

  timer.start();
  // timer2.start();
  model.move(400, 250);
  while (true) {
  }
  return 0;
}