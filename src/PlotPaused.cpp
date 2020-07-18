#include "Machine.hpp"

namespace MATSE::MCT {

void PlotPaused::entry() noexcept {
  base->drawer.printDebug("plot.paused.entry\n");
}

void PlotPaused::exit() noexcept {
  base->drawer.printDebug("plot.paused.exit\n");
}

void PlotPaused::on(a_button_up) noexcept {
  base->transition(PlotPlotting{base});
}

void PlotPaused::on(b_button_up) noexcept { base->transition(Start{base}); }

} // namespace MATSE::MCT
