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

gpio_msp432_pin s1(PORT_PIN(5, 1));
gpio_msp432_pin s2(PORT_PIN(3, 5));

adc14_msp432_channel joy_X(15);
adc14_msp432_channel joy_Y(9);

MATSE::MCT::ButtonDebouncer a_debouncer{};
MATSE::MCT::ButtonDebouncer b_debouncer{};
MATSE::MCT::JoystickDebouncer joystick_debouncer{};

bool buttonIsPressed() { return !s1.gpioRead(); }

bool button2IsPressed() { return !s2.gpioRead(); }

volatile MATSE::MCT::state currentState{MATSE::MCT::state::START};

void callback(void *arg) {
  auto m = static_cast<MATSE::MCT::Machine *>(arg);
  a_debouncer.add(MATSE::MCT::ButtonA{buttonIsPressed()});
  b_debouncer.add(MATSE::MCT::ButtonB{button2IsPressed()});
  auto x = joy_X.adcReadRaw();
  auto y = joy_Y.adcReadRaw();
  joystick_debouncer.add({x, y});
  if (a_debouncer.isKeyUp()) {
    m->handle(MATSE::MCT::a_button_up{});
  }
  if (b_debouncer.isKeyUp()) {
    m->handle(MATSE::MCT::b_button_up{});
  }
  if (joystick_debouncer.isDownPress()) {
    m->handle(MATSE::MCT::joystick_down{});
  }
  if (joystick_debouncer.isUpPress()) {
    m->handle(MATSE::MCT::joystick_up{});
  }
  if (joystick_debouncer.isLeftPress()) {
    m->handle(MATSE::MCT::joystick_left{});
  }
  if (joystick_debouncer.isRightPress()) {
    m->handle(MATSE::MCT::joystick_right{});
  }
  currentState = m->getCurrentState();
}

class uGUIDrawer : public MATSE::MCT::DrawInterface {
public:
  uGUIDrawer(uGUI *gui) : gui{gui} {}
  void print(const char *s) override {
    gui->ConsolePutString(const_cast<char *>(s));
  }

private:
  uGUI *gui;
};

int main() {

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
  auto drawer = uGUIDrawer{&gui};

  joy_Y.adcMode(ADC::ADC_10_BIT);
  joy_X.adcMode(ADC::ADC_10_BIT);

  MATSE::MCT::Machine m{&drawer};
  timer_msp432 timer;
  timer.setPeriod(1000, TIMER::PERIODIC);
  timer.setCallback(callback, &m);
  timer.start();

  while (true) {
  }
  return 0;
}