#include "Data.hpp"
#include "Machine.hpp"

namespace MATSE::MCT {

Gallery::Gallery(Machine *base) : super_t{GalleryDefault{base}}, base{base} {}

void Gallery::enterCompositeState() noexcept {}
void Gallery::exitCompositeState() noexcept { GalleryData::reset(); }

} // namespace MATSE::MCT
