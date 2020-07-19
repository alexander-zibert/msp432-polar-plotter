#include "Data.hpp"
#include "Machine.hpp"
#include "util.hpp"

namespace MATSE::MCT {

void GalleryMenu::entry() noexcept {
  base->drawer.printDebug("gallery.menu.entry");
  base->drawer.printMenu(menu);
}

void GalleryMenu::exit() noexcept {
  base->drawer.printDebug("gallery.menu.exit");
}

void GalleryMenu::on(a_button_up) noexcept {
  if (menu.getCurrent() == menu_state::BACK) {
    base->transition(GalleryDefault{base});
  }
  if (menu.getCurrent() == menu_state::EXIT) {
    base->transition(Start{base});
  }
  if (menu.getCurrent() == menu_state::EDIT) {
    const auto &plotPoints = GalleryData::images[GalleryData::currentIndex];
    for (int i = 0; i < plotPoints.dataIndex - 1; i += 1) {
      const auto &point1 = plotPoints.data[i];
      if (!point1.pressed) {
        continue;
      }
      const auto &point2 = plotPoints.data[i + 1];
      drawLine({point1.x, point1.y}, {point2.x, point2.y},
               [](auto p) { DrawData::buffer[p.y * 128 + p.x] = true; });
    }
    DrawData::plotData = plotPoints;
    base->transition(Draw{base});
  }
  if (menu.getCurrent() == menu_state::PLOT) {
    const auto &plotPoints = GalleryData::images[GalleryData::currentIndex];
    for (int i = 0; i < plotPoints.dataIndex - 1; i += 1) {
      const auto &point1 = plotPoints.data[i];
      if (!point1.pressed) {
        continue;
      }
      const auto &point2 = plotPoints.data[i + 1];
      drawLine({point1.x, point1.y}, {point2.x, point2.y},
               [](auto p) { PlotData::buffer[p.y * 128 + p.x] = true; });
    }
    PlotData::plotData = plotPoints;
    base->transition(Plot{base});
  }
}

void GalleryMenu::on(b_button_up) noexcept {
  base->transition(GalleryDefault{base});
}

void GalleryMenu::on(joystick_up) noexcept {
  menu.up();
  base->drawer.print(menu);
}

void GalleryMenu::on(joystick_down) noexcept {
  menu.down();
  base->drawer.print(menu);
}

} // namespace MATSE::MCT
