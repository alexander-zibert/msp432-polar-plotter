#ifndef MATSE_MCT_DATA_HPP
#define MATSE_MCT_DATA_HPP

#include <array>

#include "Debouncer.hpp"
#include "DrawInterface.hpp"

namespace MATSE::MCT {

struct TracePoint {
  uint8_t x;
  uint8_t y;
  bool pressed;
};

struct PlotData {
  std::array<TracePoint, 1000> data{};
  uint16_t dataIndex{0};

  void addPoint(TracePoint p) { data[dataIndex++] = p; }
};

struct DrawData {
  static inline Buffer buffer{};
  static inline Point cursor{64, 64};
  static inline bool pressed = false;
  static inline PlotData plotData{};
  static inline JoystickSample lastJoystickSample{false, false, false, false};

  static void reset() noexcept {
    buffer.reset();
    cursor = {64, 64};
    pressed = false;
    plotData = PlotData{};
    lastJoystickSample = JoystickSample{false, false, false, false};
  }
};

} // namespace MATSE::MCT

#endif