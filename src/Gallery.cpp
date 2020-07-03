#include "Machine.hpp"

namespace MATSE::MCT {

state Gallery::handle(event e) noexcept {
  switch (current) {
  case gallery_state::DEFAULT:
    return handleDefault(e);
  case gallery_state::MENU:
    return handleMenu(e);
  }
};

state Gallery::handleMenu(event e) noexcept {
  switch (e) {
  case event::JOYSTICK_UP:
    menu.up();
    return ID;
  case event::JOYSTICK_DOWN:
    menu.down();
    return ID;
  case event::A_BUTTON_UP: {
    auto currentMenuItem = menu.getCurrent();
    switch (currentMenuItem) {
    case menu_items::BACK:
      current = gallery_state::DEFAULT;
      return ID;
    case menu_items::PLOT:
      return state::PLOT;
    case menu_items::EDIT:
      return state::DRAW;
    default:
      break;
    }
    menu.reset();
    return ID;
  }
  case event::B_BUTTON_UP: {
    current = gallery_state::DEFAULT;
    // revert to prev display state
    return ID;
  }
  default:
    return ID;
  }
}

state Gallery::handleDefault(event e) noexcept {
  switch (e) {
  case event::A_BUTTON_UP:
    current = gallery_state::MENU;
    return ID;
  case event::B_BUTTON_UP:
    return state::START;
  default:
    return ID;
  }
}

} // namespace MATSE::MCT