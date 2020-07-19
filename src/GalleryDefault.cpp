#include "Data.hpp"
#include "Machine.hpp"
#include "util.hpp"

namespace MATSE::MCT {

void GalleryDefault::entry() noexcept {
  base->drawer.printDebug("gallery.default.entry");
  if (GalleryData::currentSaveTarget == 0) {
    base->drawer.gui->FillScreen(C_WHITE);
    base->drawer.gui->SetBackcolor(C_WHITE);
    base->drawer.gui->SetForecolor(C_BLACK);
    base->drawer.gui->PutString(10, 64, "No Drawings!");
  } else {
    base->drawer.gui->FillScreen(C_WHITE);
    GalleryData::buffer.reset();
    for (auto i = GalleryData::getStartIndex(); i < GalleryData::getEndIndex();
         i += 1) {
      const auto startX = (i % 2) * 63;
      const auto startY = ((i % 4) / 2) * 57;
      const auto margin = 5;
      const auto width = (128 - 4 * margin) / 2;
      const auto scaleX = [startX, width](auto x) {
        return (uint8_t)transform(0, 127, startX + margin,
                                  startX + margin + width, x);
      };
      const auto scaleY = [startY, width](auto y) {
        return (uint8_t)transform(0, 127, startY + margin,
                                  startY + margin + width, y);
      };
      const auto &plotPoints = GalleryData::images[i];
      for (int i = 0; i < plotPoints.dataIndex - 1; i += 1) {
        const auto &point1 = plotPoints.data[i];
        if (!point1.pressed) {
          continue;
        }
        const auto &point2 = plotPoints.data[i + 1];
        drawLine({scaleX(point1.x), scaleY(point1.y)},
                 {scaleX(point2.x), scaleY(point2.y)},
                 [](auto p) { GalleryData::buffer[p.y * 128 + p.x] = true; });
      }
    }
    base->drawer.print(GalleryData::buffer, C_BLACK, C_WHITE);
    drawBorders();
    base->drawer.printPage(GalleryData::getCurrentPage(),
                           GalleryData::getNumPages());
  }
}
void GalleryDefault::exit() noexcept {
  base->drawer.printDebug("gallery.default.exit");
}

void GalleryDefault::on(a_button_up) noexcept {
  base->transition(GalleryMenu{base});
}
void GalleryDefault::on(b_button_up) noexcept { base->transition(Start{base}); }

void GalleryDefault::on(joystick_left) noexcept {
  auto startIndex = GalleryData::getCurrentPage();
  GalleryData::left();
  auto newStartIndex = GalleryData::getCurrentPage();
  if (startIndex != newStartIndex) {
    entry();
  } else {
    drawBorders();
  }
}
void GalleryDefault::on(joystick_right) noexcept {
  auto startIndex = GalleryData::getCurrentPage();
  GalleryData::right();
  auto newStartIndex = GalleryData::getCurrentPage();
  if (startIndex != newStartIndex) {
    entry();
  } else {
    drawBorders();
  }
}
void GalleryDefault::on(joystick_up) noexcept {
  auto startIndex = GalleryData::getCurrentPage();
  GalleryData::up();
  auto newStartIndex = GalleryData::getCurrentPage();
  if (startIndex != newStartIndex) {
    entry();
  } else {
    drawBorders();
  }
}
void GalleryDefault::on(joystick_down) noexcept {
  auto startIndex = GalleryData::getCurrentPage();
  GalleryData::down();
  auto newStartIndex = GalleryData::getCurrentPage();
  if (startIndex != newStartIndex) {
    entry();
  } else {
    drawBorders();
  }
}

void GalleryDefault::drawBorders() noexcept {
  for (auto i = GalleryData::getStartIndex(); i < GalleryData::getEndIndex();
       i += 1) {
    const auto startX = (i % 2) * 63;
    const auto startY = ((i % 4) / 2) * 57;
    const auto margin = 5;
    const auto width = (128 - 4 * margin) / 2;

    const auto x_min = startX + margin - 1;
    const auto x_max = startX + margin + width + 1;
    const auto y_min = startY + margin - 1;
    const auto y_max = startY + margin + width + 1;
    if (i == GalleryData::getCurrentIndex()) {
      base->drawer.gui->DrawFrame(x_min, y_min, x_max, y_max, C_BLACK);
    } else {
      base->drawer.gui->DrawFrame(x_min, y_min, x_max, y_max, C_GRAY);
    }
  }
}

} // namespace MATSE::MCT
