#include "Machine.hpp"

namespace MATSE::MCT {

state Plot::handle(a_button_up) noexcept {
  isPaused = !isPaused;
  return ID;
}

state Plot::handle(b_button_up) noexcept {
  if (isPaused) {
    return state::START;
  }
  return ID;
}

} // namespace MATSE::MCT