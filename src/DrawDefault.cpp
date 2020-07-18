#include "Data.hpp"
#include "Machine.hpp"

namespace MATSE::MCT {

template <typename T> constexpr int8_t sign(T t) noexcept {
  if (t < 0)
    return -1;
  if (t > 0)
    return +1;
  return 0;
}

void DrawDefault::entry() noexcept {
  base->drawer.printDebug("default.entry");
  base->drawer.print(DrawData::buffer, C_BLACK, C_WHITE);
  base->drawer.print(DrawData::cursor);
  base->drawer.printDrawProgress(0);
}
void DrawDefault::exit() noexcept { base->drawer.printDebug("default.exit"); }

void DrawDefault::on(a_button_up) noexcept {
  DrawData::pressed = !DrawData::pressed;
}
void DrawDefault::on(b_button_up) noexcept { base->transition(DrawMenu{base}); }
void DrawDefault::on(JoystickSample e) noexcept {
  if (e.isNoop()) {
    return;
  }
  auto cursorCopy = DrawData::cursor;
  if (DrawData::cursor.x <= 126 && e.right) {
    DrawData::cursor.x += 1;
  }
  if (DrawData::cursor.x > 0 && e.left) {
    DrawData::cursor.x -= 1;
  }
  if (DrawData::cursor.y <= 126 && e.down) {
    DrawData::cursor.y += 1;
  }
  if (DrawData::cursor.y > 0 && e.up) {
    DrawData::cursor.y -= 1;
  }
  if (DrawData::pressed) {
    base->drawer.print(DrawData::cursor);
    DrawData::buffer[cursorCopy.y * 128 + cursorCopy.x] = true;
    if (e != DrawData::lastJoystickSample) {
      DrawData::plotData.addPoint(
          {DrawData::cursor.x, DrawData::cursor.y, true});
      DrawData::lastJoystickSample = e;
      base->drawer.printDrawProgress(DrawData::plotData.dataIndex);
    }
  } else {
    base->drawer.print(cursorCopy,
                       DrawData::buffer[cursorCopy.y * 128 + cursorCopy.x]
                           ? C_BLACK
                           : C_WHITE);
    base->drawer.print(DrawData::cursor);
  }
}

} // namespace MATSE::MCT
