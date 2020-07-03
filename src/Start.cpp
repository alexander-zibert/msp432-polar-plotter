#include "Machine.hpp"

namespace MATSE::MCT {
Start::Start(DrawInterface *drawer) : drawer{drawer} {}

state Start::handle(joystick_up) noexcept {
  menu.up();
  drawer->print(menu.getCurrentItem());
  drawer->print("\n");
  return ID;
}

state Start::handle(joystick_down) noexcept {
  menu.down();
  drawer->print(menu.getCurrentItem());
  drawer->print("\n");
  return ID;
}

state Start::handle(a_button_up) noexcept {
  auto currentMenuItem = menu.getCurrent();
  if (currentMenuItem == menu_items::DRAW) {
    return state::DRAW;
  }
  if (currentMenuItem == menu_items::PLOT) {
    return state::GALLERY;
  }
  return ID;
}
void Start::cleanup() noexcept { menu.reset(); }
} // namespace MATSE::MCT