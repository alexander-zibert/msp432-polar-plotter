#include "Data.hpp"
#include "Machine.hpp"

namespace MATSE::MCT {

Plot::Plot(Machine *base) : super_t{PlotPaused{base}}, base{base} {}

void Plot::enterCompositeState() noexcept {
  base->drawer.print(PlotData::buffer, C_GRAY, C_WHITE);
  PlotData::curPoint = PlotData::plotData.data[0];
}
void Plot::exitCompositeState() noexcept { PlotData::reset(); }

} // namespace MATSE::MCT
