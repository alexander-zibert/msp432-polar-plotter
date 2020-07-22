#ifndef MATSE_MCT_DRAW_INTERFACE_HPP
#define MATSE_MCT_DRAW_INTERFACE_HPP

#include "uGUI.h"
#include "uGUI_colors.h"

#include "lcd_interface.h"

#include "Data.hpp"
#include "Menu.hpp"
#include "Model.hpp"

namespace MATSE::MCT {

class bitset_stream : public pixel_stream {
public:
  // interface is non-const but the methods are const
  bitset_stream(const Buffer *buffer, UG_COLOR fc, UG_COLOR bc)
      : buffer{const_cast<Buffer *>(buffer)}, fc{fc}, bc{bc} {}
  color_t getColorType() override { return COLOR_TYPE(bc); }
  color_t getNext() override {
    if ((*buffer)[index++]) {
      return fc;
    } else {
      return bc;
    }
  }
  void reset() override { index = 0; }

private:
  Buffer *buffer;
  uint16_t index{0};
  UG_COLOR fc;
  UG_COLOR bc;
};

class uGUIDrawer {
public:
  void print(const char *s) {
    gui->ConsolePutString(const_cast<char *>(s));
    return;
  }

  void printDebug(const char *s) {
    // gui->ConsolePutString(const_cast<char *>(s));
    return;
  }

  template <typename EnumClass, EnumClass START_INDEX>
  void print(const Menu<EnumClass, START_INDEX> &menu) {
    gui->SetForecolor(C_BLACK);
    gui->SetBackcolor(C_GRAY);
    auto items = menu.getItems();
    gui->FillFrame(14, 14, 14 + 2 * FONT_WIDTH, 14 + items.size() * FONT_HEIGHT,
                   C_GRAY);
    auto i = static_cast<size_t>(menu.getCurrent());
    gui->PutChar('\x10', 15, 15 + i * FONT_HEIGHT, C_BLACK, C_GRAY);
  }

  template <typename EnumClass, EnumClass START_INDEX>
  void printMenu(const Menu<EnumClass, START_INDEX> &menu) {
    gui->FillFrame(14, 14, 114, 114, C_GRAY);
    gui->SetForecolor(C_BLACK);
    gui->SetBackcolor(C_GRAY);
    auto items = menu.getItems();
    for (size_t i = 0; i < items.size(); i += 1) {
      if (i == static_cast<size_t>(menu.getCurrent())) {
        gui->PutChar('\x10', 15, 15 + i * FONT_HEIGHT, C_BLACK, C_GRAY);
      }
      gui->PutString(15 + 2 * FONT_WIDTH, 15 + i * FONT_HEIGHT, items[i]);
    }
  }

  void print(const Buffer &buffer, UG_COLOR fc, UG_COLOR bc) {
    bitset_stream ps{&buffer, fc, bc};
    lcd->drawArea(0, 0, 127, 127, ps);
  }

  void printPage(uint8_t current, uint8_t max) {
    gui->SetBackcolor(C_WHITE);
    gui->SetForecolor(C_BLACK);
    snprintf(textBuffer, sizeof(textBuffer), "%d/%d", current, max);
    gui->PutString(50, 120, textBuffer);
  }

  void printDrawProgress(int number) {
    snprintf(textBuffer, sizeof(textBuffer), "%d%%",
             (int)((double)number / 1000. * 100));
    gui->PutString(50, 120, textBuffer);
  }

  void printPlotProgress(int number, int number2) {
    snprintf(textBuffer, sizeof(textBuffer), "%d/%d", number, number2);
    gui->SetForecolor(C_BLACK);
    gui->SetBackcolor(C_WHITE);
    gui->PutString(50, 120, textBuffer);
  }

  void debugPlot(TracePoint from, TracePoint to) {
    if (from.pressed) {
      snprintf(textBuffer, sizeof(textBuffer), "[x] (%d,%d)->(%d,%d)\n", from.x,
               from.y, to.x, to.y);
    } else {
      snprintf(textBuffer, sizeof(textBuffer), "[o] (%d,%d)->(%d,%d)\n", from.x,
               from.y, to.x, to.y);
    }
    gui->ConsolePutString(textBuffer);
  }

  // void debugModel(const Model &model) {
  //   snprintf(textBuffer, sizeof(textBuffer), "(%.1f, %.1f)\n", model.targetX,
  //            model.targetY);
  //   gui->ConsolePutString(textBuffer);
  // }

  void debugTransform(uint8_t x1, uint8_t y1, double x2, double y2) {
    snprintf(textBuffer, sizeof(textBuffer), "(%d,%d)->(%.0f,%.0f)\n", x1, y1,
             x2, y2);
    gui->ConsolePutString(textBuffer);
  }

  void print(Point p, UG_COLOR c = C_BLACK) { gui->DrawPixel(p.x, p.y, c); }

  void clear(UG_COLOR c = C_BLACK) { gui->FillScreen(c); }

  static inline uGUI *gui = nullptr;
  static inline lcd_interface *lcd = nullptr;
  constexpr static uint8_t FONT_HEIGHT = 10;
  constexpr static uint8_t FONT_WIDTH = 6;
  static inline char textBuffer[200];
};
} // namespace MATSE::MCT

#endif