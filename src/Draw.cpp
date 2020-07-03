#include "Machine.hpp"

namespace MATSE::MCT {

state Draw::handle(Joystick rawEvent) noexcept {
  if (current == draw_state::DEFAULT) {
    return ID;
  }
  return ID;
}
state Draw::handle(joystick_down) noexcept {
  if (current == draw_state::DEFAULT) {
    return ID;
  }
  if (current == draw_state::MENU) {
    menu.down();
    drawer->print(menu.getCurrentItem());
    drawer->print("\n");
    return ID;
  }
  return ID;
}
state Draw::handle(joystick_up) noexcept {
  if (current == draw_state::DEFAULT) {
    return ID;
  }
  if (current == draw_state::MENU) {
    menu.up();
    drawer->print(menu.getCurrentItem());
    drawer->print("\n");
    return ID;
  }
  return ID;
}
state Draw::handle(a_button_up) noexcept {
  if (current == draw_state::DEFAULT) {
    isPressed = !isPressed;
    return ID;
  }
  if (current == draw_state::MENU) {
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
      return ID;
    }
  }
  return ID;
}
state Draw::handle(b_button_up) noexcept {
  if (current == draw_state::DEFAULT) {
    current = draw_state::MENU;
    drawer->print(menu.getCurrentItem());
    drawer->print("\n");
    return ID;
  }
  if (current == draw_state::MENU) {
    current = draw_state::DEFAULT;
    return ID;
  }
  return ID;
}

} // namespace MATSE::MCT