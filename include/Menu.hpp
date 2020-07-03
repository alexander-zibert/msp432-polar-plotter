#ifndef MATSE_MCT_MENU_HPP
#define MATSE_MCT_MENU_HPP

#include <array>

namespace MATSE::MCT {

/**
 * Small class to implement a wrap-around datastructure of strings to model a
 * menu.
 */
template <typename EnumClass, EnumClass START_INDEX> class Menu {
  static_assert(static_cast<int>(EnumClass::NUM_ITEMS) > 1);
  static_assert(START_INDEX < EnumClass::NUM_ITEMS);

public:
  Menu(
      std::array<const char *, static_cast<size_t>(EnumClass::NUM_ITEMS)> items)
      : items(items), current(START_INDEX) {}
  void up() noexcept {
    auto newValue = static_cast<int>(current) - 1;
    if (newValue < 0) {
      current = static_cast<EnumClass>(NUM_ITEMS - 1);
    } else {
      current = static_cast<EnumClass>(newValue);
    }
  };
  void down() noexcept {
    current =
        static_cast<EnumClass>((static_cast<int>(current) + 1) % NUM_ITEMS);
  };
  void reset() noexcept { current = START_INDEX; }
  [[nodiscard]] EnumClass getCurrent() const noexcept { return current; }
  [[nodiscard]] auto getItems() const noexcept { return items; }

private:
  static constexpr int NUM_ITEMS = static_cast<int>(EnumClass::NUM_ITEMS);
  std::array<const char *, static_cast<size_t>(EnumClass::NUM_ITEMS)> items;
  EnumClass current;
};

}; // namespace MATSE::MCT

#endif