#ifndef MATSE_MCT_MODEL_HPP
#define MATSE_MCT_MODEL_HPP

#include <algorithm>
#include <cmath>
#include <cstdio>

namespace MATSE::MCT {
class Model {
public:
  Model() {
    targetX = getCurrentX();
    targetY = getCurrentY();
  }

  void move(double x, double y) {
    targetX = x;
    targetY = y;
    startX = getCurrentX();
    startY = getCurrentY();
    const auto length = std::sqrt(std::pow(targetX - startX, 2) +
                                  std::pow(targetY - startY, 2));
    numIntervals = std::ceil(length / max_draw_length);
    currentInterval = 1;
    doMoveStep();
  }

  void doMoveStep() {
    if (hasReachedTarget()) {
      return;
    }

    const auto x = startX + currentInterval / numIntervals * (targetX - startX);
    const auto y = startY + currentInterval / numIntervals * (targetY - startY);
    // const auto y = currentY + (targetY - currentY) / numIntervals;
    const auto new_l1 = std::sqrt(x * x + y * y);
    const auto new_l2 = std::sqrt(std::pow(L - x, 2) + y * y);
    const auto steps_l1 = (new_l1 - getL1()) / step_length;
    const auto steps_l2 = (new_l2 - getL2()) / step_length;
    to_go_1 = static_cast<int>(std::round(std::abs(steps_l1)) * 2);
    to_go_2 = static_cast<int>(std::round(std::abs(steps_l2)) * 2);
    dir_1 = steps_l1 >= 0 ? true : false;
    dir_2 = steps_l2 >= 0 ? true : false;
    // printf("length: %f, numIntervals: %f\n", length, numIntervals);
    currentInterval += 1;
  }

  bool hasReachedTarget() const noexcept {
    const auto length = std::sqrt(std::pow(targetX - getCurrentX(), 2) +
                                  std::pow(targetY - getCurrentY(), 2));
    if (length <= 5 * step_length) {
      return true;
    }
    return false;
  }

  double getL1() const noexcept {
    return l1_start + currentStep1 * step_length;
  }
  double getL2() const noexcept {
    return l2_start + currentStep2 * step_length;
  }

  void penUp() { penPressed = false; }
  void penDown() { penPressed = true; }

  void timeStep() {
    if (to_go_1 > 0 && to_go_1 % 2 == 0) {
      if (dir_1) {
        currentStep1 += 1;
      } else {
        currentStep1 -= 1;
      }
    }
    if (to_go_2 > 0 && to_go_2 % 2 == 0) {
      if (dir_2) {
        currentStep2 += 1;
      } else {
        currentStep2 -= 1;
      }
    }
    to_go_1 = std::max(0, to_go_1 - 1);
    to_go_2 = std::max(0, to_go_2 - 1);
    if (to_go_1 == 0 && to_go_2 == 0) {
      doMoveStep();
    }
  }

  bool getMotor1Step() const noexcept {
    if (!isInDrawingArea()) {
      return false;
    }
    if (to_go_1 == 0) {
      return false;
    }
    return to_go_1 % 2 == 0;
  }
  bool getMotor1Dir() const noexcept { return dir_1; }
  bool getMotor2Step() const noexcept {
    if (!isInDrawingArea()) {
      return false;
    }
    if (to_go_2 == 0) {
      return false;
    }
    return to_go_2 % 2 == 0;
  }
  bool getMotor2Dir() const noexcept { return dir_2; }
  bool servoPosition() const noexcept { return penPressed; }

  bool isInDrawingArea() const noexcept {
    if (!(getCurrentX() > margin && getCurrentX() < x_max - margin)) {
      return false;
    }
    if (!(getCurrentY() > margin && getCurrentY() < y_max - margin)) {
      return false;
    }
    return true;
  }

  double getCurrentX() const noexcept {
    return (L * L + std::pow(getL1(), 2) - std::pow(getL2(), 2)) / (2 * L);
  }

  double getCurrentY() const noexcept {
    return std::sqrt(std::pow(getL1(), 2) - std::pow(getCurrentX(), 2));
  }

public:
  double targetX;
  double targetY;
  double startX{};
  double startY{};
  double numIntervals{};
  double currentInterval{};

  int currentStep1 = 0;
  int currentStep2 = 0;

  int to_go_1 = 0;
  int to_go_2 = 0;
  bool dir_1 = false;
  bool dir_2 = false;
  bool penPressed = false;

  static constexpr double L = 527 - 29;
  static constexpr int steps_per_revolution = 200;
  static constexpr int microstep_factor = 1;
  static constexpr double revolution_length = 50;
  static constexpr double step_length =
      revolution_length / (steps_per_revolution * microstep_factor);
  static constexpr double l1_start = 400;
  static constexpr double l2_start = 400;
  static constexpr double x_max = L;
  static constexpr double y_max = 470;
  static constexpr double margin = 120;
  static constexpr double max_draw_length = 4;
};

} // namespace MATSE::MCT
#endif