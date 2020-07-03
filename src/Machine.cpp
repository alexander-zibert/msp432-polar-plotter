#include "Machine.hpp"

namespace MATSE::MCT {

state Machine::handle(event e) noexcept {
  switch (currentState) {
  case state::START:
    currentState = start.handle(e);
    break;
  case state::DRAW:
    currentState = draw.handle(e);
    break;
  case state::GALLERY:
    currentState = gallery.handle(e);
    break;
  case state::PLOT:
    currentState = plot.handle(e);
    break;
  }
  return currentState;
}

state Machine::handle(Joystick rawEvent) noexcept {
  if (currentState == state::DRAW) {
    return draw.handle(rawEvent);
  }
  return currentState;
}

[[nodiscard]] state Machine::getCurrentState() const noexcept {
  return currentState;
}

} // namespace MATSE::MCT