#include "Data.hpp"
#include "Machine.hpp"

namespace MATSE::MCT {

Draw::Draw(Machine *base) : super_t{DrawDefault{base}}, base{base} {}

void Draw::enterCompositeState() noexcept {}
void Draw::exitCompositeState() noexcept { DrawData::reset(); }

} // namespace MATSE::MCT
