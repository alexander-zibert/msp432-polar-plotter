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

  PlotPoints() {
    const std::array points{
        TracePoint{5, 37, 1},   TracePoint{124, 37, 1}, TracePoint{124, 88, 1},
        TracePoint{5, 88, 1},   TracePoint{5, 37, 0},   TracePoint{11, 61, 1},
        TracePoint{18, 44, 1},  TracePoint{24, 61, 0},  TracePoint{13, 56, 1},
        TracePoint{22, 56, 0},  TracePoint{29, 61, 1},  TracePoint{29, 44, 0},
        TracePoint{42, 58, 1},  TracePoint{40, 61, 1},  TracePoint{36, 61, 1},
        TracePoint{33, 58, 1},  TracePoint{33, 52, 1},  TracePoint{36, 49, 1},
        TracePoint{40, 49, 1},  TracePoint{42, 52, 1},  TracePoint{42, 55, 1},
        TracePoint{33, 55, 0},  TracePoint{46, 61, 1},  TracePoint{54, 49, 0},
        TracePoint{46, 49, 1},  TracePoint{54, 61, 0},  TracePoint{59, 52, 1},
        TracePoint{61, 49, 1},  TracePoint{65, 49, 1},  TracePoint{67, 51, 1},
        TracePoint{67, 61, 0},  TracePoint{67, 58, 1},  TracePoint{63, 61, 1},
        TracePoint{60, 61, 1},  TracePoint{58, 59, 1},  TracePoint{58, 57, 1},
        TracePoint{61, 54, 1},  TracePoint{67, 54, 0},  TracePoint{72, 49, 1},
        TracePoint{72, 61, 0},  TracePoint{72, 52, 1},  TracePoint{75, 49, 1},
        TracePoint{78, 49, 1},  TracePoint{80, 51, 1},  TracePoint{80, 61, 0},
        TracePoint{94, 52, 1},  TracePoint{90, 49, 1},  TracePoint{87, 49, 1},
        TracePoint{84, 52, 1},  TracePoint{84, 57, 1},  TracePoint{87, 61, 1},
        TracePoint{90, 61, 1},  TracePoint{94, 58, 0},  TracePoint{94, 61, 1},
        TracePoint{94, 44, 0},  TracePoint{107, 58, 1}, TracePoint{105, 61, 1},
        TracePoint{101, 61, 1}, TracePoint{98, 58, 1},  TracePoint{98, 52, 1},
        TracePoint{101, 49, 1}, TracePoint{105, 49, 1}, TracePoint{107, 52, 1},
        TracePoint{107, 55, 1}, TracePoint{98, 55, 0},  TracePoint{112, 49, 1},
        TracePoint{112, 61, 0}, TracePoint{112, 52, 1}, TracePoint{116, 49, 1},
        TracePoint{118, 49, 0}, TracePoint{34, 67, 1},  TracePoint{45, 67, 1},
        TracePoint{33, 84, 1},  TracePoint{45, 84, 0},  TracePoint{49, 84, 1},
        TracePoint{49, 72, 0},  TracePoint{49, 69, 1},  TracePoint{48, 68, 1},
        TracePoint{49, 67, 1},  TracePoint{50, 68, 1},  TracePoint{49, 69, 0},
        TracePoint{54, 75, 1},  TracePoint{58, 72, 1},  TracePoint{61, 72, 1},
        TracePoint{64, 75, 1},  TracePoint{64, 80, 1},  TracePoint{61, 84, 1},
        TracePoint{58, 84, 1},  TracePoint{54, 81, 0},  TracePoint{54, 84, 1},
        TracePoint{54, 67, 0},  TracePoint{76, 81, 1},  TracePoint{74, 84, 1},
        TracePoint{70, 84, 1},  TracePoint{67, 81, 1},  TracePoint{67, 75, 1},
        TracePoint{70, 72, 1},  TracePoint{74, 72, 1},  TracePoint{76, 75, 1},
        TracePoint{76, 78, 1},  TracePoint{67, 78, 0},  TracePoint{81, 72, 1},
        TracePoint{81, 84, 0},  TracePoint{81, 75, 1},  TracePoint{85, 72, 1},
        TracePoint{87, 72, 0},  TracePoint{93, 69, 1},  TracePoint{93, 83, 1},
        TracePoint{94, 84, 1},  TracePoint{96, 84, 1},  TracePoint{97, 83, 0},
        TracePoint{90, 72, 1},  TracePoint{96, 72, 0}};
    for (const auto &point : points) {
      addPoint(point);
    }
  }
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
  static inline TracePoint curPoint{};
  static inline bool isPlotting{false};

  static void reset() noexcept {
    buffer.reset();
    plotData = PlotPoints();
    plotIndex = 0;
    curPoint = TracePoint{};
    isPlotting = false;
  }
};

} // namespace MATSE::MCT

#endif