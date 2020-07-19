#include "Machine.hpp"

namespace MATSE::MCT {

void Start::entry() noexcept {
  base->drawer.printDebug("start.entry\n");
  base->drawer.clear(C_BLACK);
  base->drawer.printMenu(menu);
}
void Start::exit() noexcept { base->drawer.printDebug("start.exit\n"); }

void Start::on(a_button_up) noexcept {
  if (menu.getCurrent() == menu_state::DRAW) {
    base->transition(Draw{base});
  }
  if (menu.getCurrent() == menu_state::GALLERY) {
    base->transition(Gallery{base});
  }
}
void Start::on(joystick_up) noexcept {
  menu.up();
  base->drawer.print(menu);
}
void Start::on(joystick_down) noexcept {
  menu.down();
  base->drawer.print(menu);
}

} // namespace MATSE::MCT
