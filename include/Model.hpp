#ifndef MATSE_MCT_MODEL_HPP
#define MATSE_MCT_MODEL_HPP

#include <algorithm>
#include <cmath>
#include <cstdio>

namespace MATSE::MCT {
class Model {
public:
  void move(double x, double y) {
    target_x = x;
    target_y = y;

    const auto current_x = getCurrentX();
    const auto current_y = getCurrentY();
    const auto length = std::sqrt(std::pow(target_x - current_x, 2) +
                                  std::pow(target_y - current_y, 2));
    if (length <= 2 * step_length) {
      return;
    }
    const auto numIntervals = std::ceil(length / max_draw_length);
    x = current_x + (target_x - current_x) / numIntervals;
    y = current_y + (target_y - current_y) / numIntervals;

    const auto new_l1 = std::sqrt(x * x + y * y);
    const auto new_l2 = std::sqrt(std::pow(L - x, 2) + y * y);
    const auto steps_l1 = (new_l1 - getL1()) / step_length;
    const auto steps_l2 = (new_l2 - getL2()) / step_length;
    const auto steps1 = static_cast<int>(std::round(std::abs(steps_l1)));
    const auto steps2 = static_cast<int>(std::round(std::abs(steps_l2)));
    dir_1 = steps_l1 >= 0 ? true : false;
    dir_2 = steps_l2 >= 0 ? true : false;
    should_step_1 = false;
    should_step_2 = false;
    i_1 = 0;
    i_2 = 0;
    if (steps1 == 0) {
      time_step = 1;
      steps_needed = steps2;
      time_step_1 = steps_needed * 2;
      time_step_2 = 1;
      motor1 = 0;
      motor2 = 2 * time_step;
      return;
    }
    if (steps2 == 0) {
      time_step = 1;
      steps_needed = steps1;
      time_step_1 = 1;
      time_step_2 = steps_needed * 2;
      motor1 = 2 * time_step;
      motor2 = 0;
      return;
    }

    time_step = std::min(steps1, steps2);
    steps_needed = std::max(steps1, steps2);
    time_step_1 = steps2 * 10;
    time_step_2 = steps1 * 10;
    motor1 = 2 * time_step;
    motor2 = 2 * time_step;
    if (steps1 <= steps2) {
      motor1 += time_step_1;
    } else {
      motor2 += time_step_2;
    }
  }

  bool hasReachedTarget() const noexcept {
    return (i_1 >= steps_needed || i_2 >= steps_needed);
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
    if (hasReachedTarget()) {
      should_step_1 = false;
      should_step_2 = false;
      return;
    }

    auto new_i_1 = motor1 / (2 * time_step_1);
    should_step_1 = new_i_1 > i_1;
    i_1 = new_i_1;

    auto new_i_2 = motor2 / (2 * time_step_2);
    should_step_2 = new_i_2 > i_2;
    i_2 = new_i_2;

    if (should_step_1) {
      currentStep1 += dir_1 ? 1 : -1;
    }
    if (should_step_2) {
      currentStep2 += dir_2 ? 1 : -1;
    }

    motor1 += time_step;
    motor2 += time_step;

    if (hasReachedTarget()) {
      should_step_1 = false;
      should_step_2 = false;
      // recalc
      move(target_x, target_y);
      return;
    }
  }

  bool getMotor1Step() const noexcept { return should_step_1; }
  bool getMotor1Dir() const noexcept { return dir_1; }
  bool getMotor2Step() const noexcept { return should_step_2; }
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
  double target_x{};
  double target_y{};

  int currentStep1 = 0;
  int currentStep2 = 0;

  bool dir_1 = false;
  bool dir_2 = false;
  bool penPressed = false;

  int i_1{};
  int i_2{};
  int time_step{};
  int steps_needed{};
  int time_step_1{};
  int time_step_2{};
  int motor1{};
  int motor2{};
  bool should_step_1{false};
  bool should_step_2{false};

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
  static constexpr double max_draw_length = 10;
};

} // namespace MATSE::MCT
#endif