#include "Data.hpp"
#include "Machine.hpp"

namespace MATSE::MCT {

double transform(double min1, double max1, double min2, double max2,
                 double x1) {
  return (x1 - min1) / (max1 - min1) * (max2 - min2) + min2;
}

struct Point2D {
  double x;
  double y;
};

constexpr double margin = 70;
constexpr double x_max = 527 - 29;
constexpr double y_max = 470;

Point2D transformToModel(Point2D p) {
  return {transform(0, 127, margin, x_max, p.x),
          transform(0, 127, margin, y_max, p.y)};
}

Point transformToLCD(Point2D p) {
  return {(uint8_t)transform(margin, x_max, 0, 127, p.x),
          (uint8_t)transform(margin, y_max, 0, 127, p.y)};
}

void PlotPlotting::entry() noexcept {
  base->drawer.printDebug("plot.plotting.entry\n");
  PlotData::isPlotting = true;
  lastModelPoint =
      transformToLCD({base->model->getCurrentX(), base->model->getCurrentY()});
  // for (int i = 0; i < PlotData::plotData.dataIndex - 1; i += 1) {
  //   auto p1 = PlotData::plotData.data[i];
  //   auto p2 = PlotData::plotData.data[i + 1];
  //   if (!p1.pressed) {
  //     continue;
  //   }
  //   base->drawer.gui->DrawLine(p1.x, p1.y, p2.x, p2.y, C_BLACK);
  // }
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
  if (PlotData::plotData.data[std::max((int)PlotData::plotIndex - 1, 0)]
          .pressed) {
    base->drawer.gui->DrawLine(lastModelPoint.x, lastModelPoint.y,
                               newModelPoint.x, newModelPoint.y, C_BLACK);
  } else {
    base->drawer.gui->DrawLine(lastModelPoint.x, lastModelPoint.y,
                               newModelPoint.x, newModelPoint.y, C_GRAY);
  }
  lastModelPoint = newModelPoint;

  if (!model->hasReachedTarget()) {
    return;
  }
  if (PlotData::plotIndex == PlotData::plotData.dataIndex) {
    return;
  }
  base->drawer.printPlotProgress(PlotData::plotIndex,
                                 PlotData::plotData.dataIndex - 1);
  const auto point = PlotData::plotData.data[PlotData::plotIndex++];
  // base->drawer.debugPlot(curPoint, point);
  // base->drawer.debugModel(*model);
  // base->drawer.debugTransform(
  //     point.x, point.y, transform(0, 127, model->margin, model->x_max,
  //     point.x), transform(0, 127, model->margin, model->y_max, point.y));
  model->move(transform(0, 127, model->margin, model->x_max, point.x),
              transform(0, 127, model->margin, model->y_max, point.y));
  // if (curPoint.pressed) {
  //   base->drawer.gui->DrawLine(curPoint.x, curPoint.y, point.x, point.y,
  //                              C_BLACK);
  // }
}

} // namespace MATSE::MCT
