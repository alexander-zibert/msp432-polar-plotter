#include "Machine.hpp"

namespace MATSE::MCT {
state Plot::handle(event e) noexcept {
  if (isPaused) {
    if (e == event::B_BUTTON_UP) {
      return state::START;
    }
    if (e == event::A_BUTTON_UP) {
      isPaused = false;
      // start drawing, change legend
      return ID;
    }
  } else {
    if (e == event::A_BUTTON_UP) {
      isPaused = true;
      // stop drawing, change legend
      return ID;
    }
  }
  return ID;
};
} // namespace MATSE::MCT