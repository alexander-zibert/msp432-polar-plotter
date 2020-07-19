#ifndef MATSE_MCT_DATA_HPP
#define MATSE_MCT_DATA_HPP

#include <algorithm>
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
  static constexpr uint8_t NUM_PAGES = 3;
  static constexpr uint8_t ITEMS_PER_PAGE = 4;
  static constexpr uint8_t NUM_ITEMS = NUM_PAGES * ITEMS_PER_PAGE;
  static inline std::array<PlotPoints, NUM_ITEMS> images{};
  static inline Buffer buffer{};
  static inline uint8_t currentSaveTarget = 0;
  static inline uint8_t currentIndex = 0;

  static uint8_t getCurrentIndex() { return currentIndex; }

  static void addImage(const PlotPoints &points) noexcept {
    images[currentSaveTarget] = points;
    currentSaveTarget = (currentSaveTarget + 1) % NUM_ITEMS;
  }

  static void reset() noexcept {
    buffer.reset();
    currentIndex = 0;
  }

  static uint8_t getStartIndex() {
    return (getCurrentIndex() / ITEMS_PER_PAGE) * ITEMS_PER_PAGE;
  }

  static uint8_t getEndIndex() {
    return std::min(static_cast<uint8_t>(getStartIndex() + ITEMS_PER_PAGE),
                    currentSaveTarget);
  }

  static uint8_t getCurrentPage() {
    return getCurrentIndex() / ITEMS_PER_PAGE + 1;
  }

  static uint8_t getNumPages() {
    return currentSaveTarget / ITEMS_PER_PAGE + 1;
  }

  static void left() {
    if (currentIndex - 1 >= 0) {
      currentIndex -= 1;
    }
  }
  static void right() {
    if (currentIndex + 1 <= currentSaveTarget - 1) {
      currentIndex += 1;
    }
  }
  static void up() {
    if (currentIndex - 2 >= 0) {
      currentIndex -= 2;
    }
  }
  static void down() {
    if (currentIndex + 2 <= currentSaveTarget - 1) {
      currentIndex += 2;
    }
  }
};

} // namespace MATSE::MCT

#endif