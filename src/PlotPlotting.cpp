#include "Data.hpp"
#include "Machine.hpp"
#include "Model.hpp"
#include "util.hpp"

namespace MATSE::MCT {

struct Point2D {
  double x;
  double y;
};

constexpr double margin = Model::margin + 1;
constexpr double x_max = Model::x_max;
constexpr double y_max = Model::y_max;

Point2D transformToModel(Point2D p) {
  return {transform(0, 127, margin, x_max - margin, p.x),
          transform(0, 127, margin, y_max - margin, p.y)};
}

Point transformToLCD(Point2D p) {
  return {(uint8_t)transform(margin, x_max - margin, 0, 127, p.x),
          (uint8_t)transform(margin, y_max - margin, 0, 127, p.y)};
}

void PlotPlotting::entry() noexcept {
  base->drawer.printDebug("plot.plotting.entry\n");
  PlotData::plotData.addPoint({150, 150, false});
  PlotData::isPlotting = true;
  lastModelPoint =
      transformToLCD({base->model->getCurrentX(), base->model->getCurrentY()});
}

void PlotPlotting::exit() noexcept {
  PlotData::isPlotting = false;
  base->drawer.printDebug("plot.plotting.exit\n");
}

void PlotPlotting::on(a_button_up) noexcept {
  base->transition(PlotPaused{base});
}

void PlotPlotting::on(timestep) noexcept {
  auto model = base->model;
  const auto newModelPoint =
      transformToLCD({base->model->getCurrentX(), base->model->getCurrentY()});
  if (PlotData::plotData.data[std::max((int)PlotData::plotIndex - 2, 0)]
          .pressed) {
    base->drawer.gui->DrawLine(lastModelPoint.x, lastModelPoint.y,
                               newModelPoint.x, newModelPoint.y, C_BLACK);
    model->penDown();
  } else {
    model->penUp();
  }
  lastModelPoint = newModelPoint;

  if (!model->hasReachedTarget()) {
    return;
  }
  if (PlotData::plotIndex == PlotData::plotData.dataIndex) {
    return;
  }
  const auto point = PlotData::plotData.data[PlotData::plotIndex];
  const auto modelPoint = transformToModel({(double)point.x, (double)point.y});
  model->move(modelPoint.x, modelPoint.y);
  PlotData::plotIndex += 1;
}

} // namespace MATSE::MCT
