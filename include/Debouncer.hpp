#ifndef MATSE_MCT_DEBOUNCER_HPP
#define MATSE_MCT_DEBOUNCER_HPP

#include "Events.hpp"
#include <etl/debounce.h>

namespace MATSE::MCT {
constexpr int VALID_COUNT_BUTTON = 3;
constexpr int REPEAT_COUNT_BUTTON = 500;
constexpr int VALID_COUNT_JOYSTICK = 3;
constexpr int REPEAT_COUNT_JOYSTICK = 3;

template <int VALID_COUNT = VALID_COUNT_BUTTON,
          int REPEAT_COUNT = REPEAT_COUNT_BUTTON>
class ButtonDebouncer {
  static_assert(VALID_COUNT > 0);
  static_assert(REPEAT_COUNT >= 0);

public:
  void add(const ButtonA &sample) noexcept { debouncer.add(sample.pressed); }
  void add(const ButtonB &sample) noexcept { debouncer.add(sample.pressed); }
  void reset() noexcept {
    debouncer = etl::debounce<VALID_COUNT, 0, REPEAT_COUNT>{};
  }
  [[nodiscard]] bool isKeyDown() const noexcept {
    return debouncer.has_changed() && debouncer.is_set();
  }
  [[nodiscard]] bool isKeyUp() const noexcept {
    return debouncer.has_changed() && !debouncer.is_set();
  }

private:
  etl::debounce<VALID_COUNT, 0, REPEAT_COUNT> debouncer{};
};

struct JoystickSample {
  bool left;
  bool right;
  bool up;
  bool down;

  bool operator==(const JoystickSample &sample2) const noexcept {
    return left == sample2.left && right == sample2.right && up == sample2.up &&
           down == sample2.down;
  }

  bool operator!=(const JoystickSample &sample2) const noexcept {
    return !((*this) == sample2);
  }

  bool isNoop() const noexcept {
    return (*this) == JoystickSample{false, false, false, false};
  }
};

template <int VALID_COUNT = VALID_COUNT_JOYSTICK,
          int REPEAT_COUNT = REPEAT_COUNT_JOYSTICK>
class JoystickDebouncer {
  static_assert(VALID_COUNT > 0);
  static_assert(REPEAT_COUNT >= 0);

public:
  void add(const JoystickSample &sample) noexcept {
    debounceLeft.add(sample.left);
    debounceRight.add(sample.right);
    debounceUp.add(sample.up);
    debounceDown.add(sample.down);
  }
  void reset() noexcept {
    debounceLeft = etl::debounce<VALID_COUNT, REPEAT_COUNT, REPEAT_COUNT>{};
    debounceRight = etl::debounce<VALID_COUNT, REPEAT_COUNT, REPEAT_COUNT>{};
    debounceUp = etl::debounce<VALID_COUNT, REPEAT_COUNT, REPEAT_COUNT>{};
    debounceDown = etl::debounce<VALID_COUNT, REPEAT_COUNT, REPEAT_COUNT>{};
  }
  [[nodiscard]] bool isLeftPress() const noexcept {
    return debounceLeft.has_changed() && debounceLeft.is_set();
  }
  [[nodiscard]] bool wasLeftPress() const noexcept {
    return debounceLeft.has_changed() && !debounceLeft.is_set();
  }
  [[nodiscard]] bool isRightPress() const noexcept {
    return debounceRight.has_changed() && debounceRight.is_set();
  }
  [[nodiscard]] bool wasRightPress() const noexcept {
    return debounceRight.has_changed() && !debounceRight.is_set();
  }
  [[nodiscard]] bool isUpPress() const noexcept {
    return debounceUp.has_changed() && debounceUp.is_set();
  }
  [[nodiscard]] bool wasUpPress() const noexcept {
    return debounceUp.has_changed() && !debounceUp.is_set();
  }
  [[nodiscard]] bool isDownPress() const noexcept {
    return debounceDown.has_changed() && debounceDown.is_set();
  }
  [[nodiscard]] bool wasDownPress() const noexcept {
    return debounceDown.has_changed() && !debounceDown.is_set();
  }

private:
  etl::debounce<VALID_COUNT, REPEAT_COUNT, REPEAT_COUNT> debounceLeft{};
  etl::debounce<VALID_COUNT, REPEAT_COUNT, REPEAT_COUNT> debounceRight{};
  etl::debounce<VALID_COUNT, REPEAT_COUNT, REPEAT_COUNT> debounceUp{};
  etl::debounce<VALID_COUNT, REPEAT_COUNT, REPEAT_COUNT> debounceDown{};
};
} // namespace MATSE::MCT

#endif