#include "Data.hpp"
#include "Machine.hpp"

namespace MATSE::MCT {

void DrawMenu::entry() noexcept {
  base->drawer.printDebug("menu.entry");
  base->drawer.printMenu(menu);
}
void DrawMenu::exit() noexcept { base->drawer.printDebug("menu.exit"); }

void DrawMenu::on(a_button_up) noexcept {
  if (menu.getCurrent() == menu_state::BACK) {
    base->transition(DrawDefault{base});
  }
  if (menu.getCurrent() == menu_state::CLEAR) {
    DrawData::reset();
    base->transition(DrawDefault{base});
  }
  if (menu.getCurrent() == menu_state::EXIT) {
    base->transition(Start{base});
  }
  if (menu.getCurrent() == menu_state::PLOT) {
    // add last point
    if (DrawData::pressed) {
      DrawData::plotData.addPoint(
          {DrawData::cursor.x, DrawData::cursor.y, true});
    }

    PlotData::plotData = DrawData::plotData;
    PlotData::buffer = DrawData::buffer;
    base->transition(Plot{base});
  }
  if (menu.getCurrent() == menu_state::SAVE) {
    // add last point
    if (DrawData::pressed) {
      DrawData::plotData.addPoint(
          {DrawData::cursor.x, DrawData::cursor.y, true});
    }
    GalleryData::addImage(DrawData::plotData);
    base->transition(DrawDefault{base});
  }
}
void DrawMenu::on(b_button_up) noexcept { base->transition(DrawDefault{base}); }
void DrawMenu::on(joystick_up) noexcept {
  menu.up();
  base->drawer.print(menu);
}
void DrawMenu::on(joystick_down) noexcept {
  menu.down();
  base->drawer.print(menu);
}

} // namespace MATSE::MCT
