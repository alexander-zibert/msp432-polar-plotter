#ifndef MATSE_MCT_DATA_HPP
#define MATSE_MCT_DATA_HPP

#include <array>
#include <bitset>

#include "Debouncer.hpp"

namespace MATSE::MCT {

struct Point {
  uint8_t x;
  uint8_t y;

  bool operator==(const Point &p2) { return x == p2.x && y == p2.y; }
};

using Buffer = std::bitset<128 * 128>;

struct TracePoint {
  uint8_t x;
  uint8_t y;
  bool pressed;
};

struct PlotPoints {
  std::array<TracePoint, 1000> data{};
  uint16_t dataIndex{0};

  void addPoint(TracePoint p) { data[dataIndex++] = p; }
};

struct DrawData {
  static inline Buffer buffer{};
  static inline Point cursor{64, 64};
  static inline bool pressed = false;
  static inline PlotPoints plotData{};
  static inline JoystickSample lastJoystickSample{false, false, false, false};

  static void reset() noexcept {
    buffer.reset();
    cursor = {64, 64};
    pressed = false;
    plotData = PlotPoints{};
    lastJoystickSample = JoystickSample{false, false, false, false};
  }
};

struct PlotData {
  static inline Buffer buffer{};
  static inline PlotPoints plotData{};
  static inline uint16_t plotIndex{0};
  static inline bool isPlotting{false};

  static void reset() noexcept {
    buffer.reset();
    plotData = PlotPoints();
    plotIndex = 0;
    isPlotting = false;
  }
};

struct GalleryData {
  static constexpr uint8_t NUM_PAGES = 2;
  static constexpr uint8_t ITEMS_PER_PAGE = 4;
  static inline std::array<PlotPoints, NUM_PAGES * ITEMS_PER_PAGE> images{};
  static inline Buffer buffer{};
  static inline uint8_t currentSaveTarget = 0;
};

} // namespace MATSE::MCT

#endif