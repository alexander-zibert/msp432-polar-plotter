#include "Machine.hpp"

namespace MATSE::MCT {

state Plot::handle(a_button_up) noexcept {
  isPaused = !isPaused;
  if (!isPaused) {
    /*
      for (pos in positions) {
        if (!model.canReach(pos)) {
          // missing fail state
          break;
        }
        if (pos.isPenDown) {
          model.penDown();
        } else {
          model.penUp();
        }
        model.move(pos.x, pos.y);
        while (!model.hasReached(pos) && !isPaused) {

        }
      }
    */
  }
  return ID;
}

state Plot::handle(b_button_up) noexcept {
  if (isPaused) {
    return state::START;
  }
  return ID;
}

} // namespace MATSE::MCT