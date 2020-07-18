#include "Data.hpp"
#include "Machine.hpp"

namespace MATSE::MCT {

void DrawMenu::entry() noexcept {
  base->drawer.print("menu.entry");
  base->drawer.printMenu(menu);
}
void DrawMenu::exit() noexcept { base->drawer.print("menu.exit"); }

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
}
void DrawMenu::on(b_button_up) noexcept { base->transition(DrawDefault{base}); }
void DrawMenu::on(joystick_up) noexcept {
  base->drawer.print("up");
  menu.up();
  base->drawer.print(menu);
}
void DrawMenu::on(joystick_down) noexcept {
  base->drawer.print("down");
  menu.down();
  base->drawer.print(menu);
}

} // namespace MATSE::MCT
