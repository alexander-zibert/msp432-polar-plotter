#include "Machine.hpp"

namespace MATSE::MCT {
state Start::handle(event e) noexcept {
  switch (e) {
  case event::JOYSTICK_UP:
    menu.up();
    break;
  case event::JOYSTICK_DOWN:
    menu.down();
    break;
  case event::A_BUTTON_UP: {
    auto currentMenuItem = menu.getCurrent();
    cleanup();
    if (currentMenuItem == menu_items::DRAW) {
      return state::DRAW;
    }
    if (currentMenuItem == menu_items::PLOT) {
      return state::GALLERY;
    }
    break;
  }
  default:
    break;
  }
  return ID;
};

void Start::cleanup() noexcept { menu.reset(); }
} // namespace MATSE::MCT