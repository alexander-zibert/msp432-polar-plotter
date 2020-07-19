#include "Data.hpp"
#include "Machine.hpp"

namespace MATSE::MCT {

void GalleryMenu::entry() noexcept {
  base->drawer.printDebug("gallery.menu.entry");
  base->drawer.printMenu(menu);
}

void GalleryMenu::exit() noexcept {
  base->drawer.printDebug("gallery.menu.exit");
}

void GalleryMenu::on(a_button_up) noexcept {
  if (menu.getCurrent() == menu_state::BACK) {
    base->transition(GalleryDefault{base});
  }
  if (menu.getCurrent() == menu_state::EXIT) {
    base->transition(Start{base});
  }
}

void GalleryMenu::on(b_button_up) noexcept {
  base->transition(GalleryDefault{base});
}

void GalleryMenu::on(joystick_up) noexcept {
  menu.up();
  base->drawer.print(menu);
}

void GalleryMenu::on(joystick_down) noexcept {
  menu.down();
  base->drawer.print(menu);
}

} // namespace MATSE::MCT
