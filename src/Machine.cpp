#include "Machine.hpp"

namespace MATSE::MCT {

Machine::Machine(Model *model) : super_t{Start{this}}, model{model} {}

void Machine::start() noexcept { entry(); }

} // namespace MATSE::MCT
