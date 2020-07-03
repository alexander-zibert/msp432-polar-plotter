#ifndef MATSE_MCT_MACHINE_HPP
#define MATSE_MCT_MACHINE_HPP

#include "Menu.hpp"

namespace MATSE::MCT {

struct Joystick {
  double x;
  double y;
};

enum class event {
  A_BUTTON_UP,
  A_BUTTON_DOWN,
  B_BUTTON_UP,
  B_BUTTON_DOWN,
  JOYSTICK_LEFT,
  JOYSTICK_RIGHT,
  JOYSTICK_UP,
  JOYSTICK_DOWN
};

enum class state { START, DRAW, GALLERY, PLOT };

class Gallery {
public:
  state handle(event e) noexcept;

private:
  state handleMenu(event e) noexcept;
  state handleDefault(event e) noexcept;

  static constexpr state ID{state::GALLERY};

  enum class gallery_state { DEFAULT, MENU };
  gallery_state current{gallery_state::DEFAULT};

  enum class menu_items { BACK, PLOT, EDIT, NUM_ITEMS };
  Menu<menu_items, menu_items::BACK> menu{
      {"Back", "Plot selected", "Edit selected"}};
};

class Draw {
public:
  state handle(event e) noexcept;
  state handle(Joystick rawEvent) noexcept;

private:
  state handleMenu(event e) noexcept;
  state handleDefault(event e) noexcept;
  state handleDefault(Joystick rawEvent) noexcept;

  static constexpr state ID{state::DRAW};
  enum class draw_state { DEFAULT, MENU };
  draw_state current{draw_state::DEFAULT};

  enum class menu_items { BACK, PLOT, SAVE, EXIT, NUM_ITEMS };
  Menu<menu_items, menu_items::BACK> menu{
      {"Back to drawing", "Plot current drawing", "Save current drawing",
       "Exit without saving"}};

  bool isPressed = false;
  double x = 0.0;
  double y = 0.0;
};

class Start {
public:
  state handle(event e) noexcept;

private:
  void cleanup() noexcept;
  static constexpr state ID{state::START};
  enum class menu_items { DRAW, PLOT, NUM_ITEMS };
  Menu<menu_items, menu_items::DRAW> menu{
      {"Create new drawing", "Plot existing drawing"}};
};

class Plot {
public:
  state handle(event e) noexcept;

private:
  static constexpr state ID{state::PLOT};
  bool isPaused = true;
};

class Machine {
public:
  state handle(event e) noexcept;
  state handle(Joystick rawEvent) noexcept;
  [[nodiscard]] state getCurrentState() const noexcept;

private:
  state currentState = state::START;
  Draw draw{};
  Gallery gallery{};
  Start start{};
  Plot plot{};
};

} // namespace MATSE::MCT

#endif