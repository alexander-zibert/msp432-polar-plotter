#include "Machine.hpp"

namespace MATSE::MCT {
state Draw::handle(event e) noexcept {
  switch (current) {
  case draw_state::DEFAULT:
    return handleDefault(e);
  case draw_state::MENU:
    return handleMenu(e);
  }
}
state Draw::handle(Joystick rawEvent) noexcept {
  if (current == draw_state::DEFAULT) {
    return handleDefault(rawEvent);
  }
  return ID;
}

state Draw::handleMenu(event e) noexcept {
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
      current = draw_state::DEFAULT;
      return ID;
    case menu_items::PLOT:
      return state::PLOT;
    case menu_items::SAVE:
      // save
      current = draw_state::DEFAULT;
      return ID;
    case menu_items::EXIT:
      return state::START;
    default:
      break;
    }
    menu.reset();
    return ID;
  }
  case event::B_BUTTON_UP: {
    current = draw_state::DEFAULT;
    // revert to prev display state
    return ID;
  }
  default:
    return ID;
  }
}
state Draw::handleDefault(event e) noexcept {
  switch (e) {
  case event::A_BUTTON_UP: {
    isPressed = !isPressed;
    return ID;
  }
  case event::B_BUTTON_UP: {
    current = draw_state::MENU;
    // draw menu
    return ID;
  }
  default:
    return ID;
  }
}

state Draw::handleDefault(Joystick rawEvent) noexcept { return ID; }
} // namespace MATSE::MCT