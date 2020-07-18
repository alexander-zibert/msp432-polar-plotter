#include "Machine.hpp"

namespace MATSE::MCT {

Machine::Machine() : super_t{Start{this}} {}

void Machine::start() noexcept { entry(); }

} // namespace MATSE::MCT
