#include "Machine.hpp"

namespace MATSE::MCT {

[[nodiscard]] state Machine::getCurrentState() const noexcept {
  return currentState;
}

} // namespace MATSE::MCT