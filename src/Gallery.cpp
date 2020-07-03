#include "Machine.hpp"

namespace MATSE::MCT {

state Gallery::handle(joystick_left) noexcept {
  if (current == gallery_state::DEFAULT) {
    return ID;
  }
  if (current == gallery_state::MENU) {
    return ID;
  }
  return ID;
}
state Gallery::handle(joystick_right) noexcept {
  if (current == gallery_state::DEFAULT) {
    return ID;
  }
  if (current == gallery_state::MENU) {
    return ID;
  }
  return ID;
}

state Gallery::handle(joystick_up) noexcept {
  if (current == gallery_state::DEFAULT) {
    return ID;
  }
  if (current == gallery_state::MENU) {
    menu.up();
    drawer->print(menu.getCurrentItem());
    drawer->print("\n");
    return ID;
  }
  return ID;
}
state Gallery::handle(joystick_down) noexcept {
  if (current == gallery_state::DEFAULT) {
    return ID;
  }
  if (current == gallery_state::MENU) {
    menu.down();
    drawer->print(menu.getCurrentItem());
    drawer->print("\n");
    return ID;
  }
  return ID;
}
state Gallery::handle(a_button_up) noexcept {
  if (current == gallery_state::DEFAULT) {
    current = gallery_state::MENU;
    drawer->print(menu.getCurrentItem());
    drawer->print("\n");
    return ID;
  }
  if (current == gallery_state::MENU) {
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
      return ID;
    }
  }
  return ID;
}
state Gallery::handle(b_button_up) noexcept {
  if (current == gallery_state::DEFAULT) {
    return state::START;
  }
  if (current == gallery_state::MENU) {
    current = gallery_state::DEFAULT;
    return ID;
  }
  return ID;
}

} // namespace MATSE::MCT