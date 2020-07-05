#ifndef MATSE_MCT_MACHINE_HPP
#define MATSE_MCT_MACHINE_HPP

#include <array>

#include "DrawInterface.hpp"
#include "Events.hpp"
#include "Menu.hpp"

namespace MATSE::MCT {

enum class state { START, DRAW, GALLERY, PLOT };

class State {
public:
  virtual state getStateId() const noexcept = 0;
  virtual state handle(a_button_up) noexcept { return getStateId(); };
  virtual state handle(b_button_up) noexcept { return getStateId(); };
  virtual state handle(joystick_left) noexcept { return getStateId(); };
  virtual state handle(joystick_right) noexcept { return getStateId(); };
  virtual state handle(joystick_up) noexcept { return getStateId(); };
  virtual state handle(joystick_down) noexcept { return getStateId(); };
  virtual state handle(Joystick) noexcept { return getStateId(); };
  virtual void onEntry() noexcept {};
  virtual void onExit() noexcept {};
};

class Gallery : public State {
public:
  Gallery(DrawInterface *drawer) : drawer{drawer} {}

  state handle(joystick_up) noexcept override;
  state handle(joystick_down) noexcept override;
  state handle(joystick_left) noexcept override;
  state handle(joystick_right) noexcept override;
  state handle(a_button_up) noexcept override;
  state handle(b_button_up) noexcept override;

  state getStateId() const noexcept override { return ID; }
  void onEntry() noexcept override { drawer->print("\ngallery.onEntry\n"); }
  void onExit() noexcept override { drawer->print("\ngallery.onExit\n"); }

private:
  static constexpr state ID{state::GALLERY};

  enum class gallery_state { DEFAULT, MENU };
  gallery_state current{gallery_state::DEFAULT};

  enum class menu_items { BACK, PLOT, EDIT, NUM_ITEMS };
  Menu<menu_items, menu_items::BACK> menu{
      {"Back", "Plot selected", "Edit selected"}};

  DrawInterface *drawer;
};

class Draw : public State {
public:
  Draw(DrawInterface *drawer) : drawer{drawer} {}

  state handle(Joystick) noexcept override;
  state handle(joystick_up) noexcept override;
  state handle(joystick_down) noexcept override;
  state handle(a_button_up) noexcept override;
  state handle(b_button_up) noexcept override;
  state getStateId() const noexcept override { return ID; }
  void onEntry() noexcept override { drawer->print("\ndraw.onEntry\n"); }
  void onExit() noexcept override { drawer->print("\ndraw.onExit\n"); }

private:
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
  DrawInterface *drawer;
};

class Start : public State {
public:
  Start(DrawInterface *drawer);

  state handle(joystick_up) noexcept override;
  state handle(joystick_down) noexcept override;
  state handle(a_button_up) noexcept override;

  state getStateId() const noexcept override { return ID; }
  void onEntry() noexcept override {
    drawer->print("\nstart.onEntry\n");
    drawer->print(menu.getCurrentItem());
    drawer->print("\n");
  }
  void onExit() noexcept override { drawer->print("\nstart.onExit\n"); }

private:
  void cleanup() noexcept;
  static constexpr state ID{state::START};
  enum class menu_items { DRAW, PLOT, NUM_ITEMS };
  Menu<menu_items, menu_items::DRAW> menu{
      {"Create new drawing", "Plot existing drawing"}};

  DrawInterface *drawer;
};

class Plot : public State {
public:
  Plot(DrawInterface *drawer) : drawer{drawer} {}
  state handle(a_button_up) noexcept override;
  state handle(b_button_up) noexcept override;
  state getStateId() const noexcept override { return ID; }
  void onEntry() noexcept override { drawer->print("\nplot.onEntry\n"); }
  void onExit() noexcept override { drawer->print("\nplot.onExit\n"); }

private:
  static constexpr state ID{state::PLOT};
  bool isPaused = true;
  DrawInterface *drawer;
};

class Machine {
public:
  Machine(DrawInterface *drawer)
      : drawer{drawer}, start{Start{drawer}}, draw{Draw{drawer}},
        gallery{Gallery{drawer}}, plot{Plot{drawer}} {
    // not using new saves 30kB!
    states[0] = &start;
    states[1] = &draw;
    states[2] = &gallery;
    states[3] = &plot;
    states[static_cast<int>(currentState)]->onEntry();
  }
  // Machine(DrawInterface *drawer);

  Machine(const Machine &) = delete;
  Machine &operator=(const Machine &) = delete;
  ~Machine() = default;
  Machine(const Machine &&) = delete;
  Machine &operator=(const Machine &&) = delete;

  state handle(auto e) noexcept {
    auto newState = states[static_cast<int>(currentState)]->handle(e);
    if (newState != currentState) {
      states[static_cast<int>(currentState)]->onExit();
      currentState = newState;
      states[static_cast<int>(currentState)]->onEntry();
    }
    return currentState;
  }
  [[nodiscard]] state getCurrentState() const noexcept;
  DrawInterface &getDrawer() const noexcept { return *drawer; }

private:
  DrawInterface *drawer;
  state currentState = state::START;
  std::array<State *, 4> states{};
  Start start;
  Draw draw;
  Gallery gallery;
  Plot plot;
};

} // namespace MATSE::MCT

#endif