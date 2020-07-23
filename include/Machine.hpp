#ifndef MATSE_MCT_MACHINE_HPP
#define MATSE_MCT_MACHINE_HPP

#include <type_traits>
#include <variant>

#include "Debouncer.hpp"
#include "DrawInterface.hpp"
#include "Events.hpp"
#include "Menu.hpp"
#include "Model.hpp"

namespace MATSE::MCT {

template <typename StateVariant> struct CompositeState {
  StateVariant currentState;
  uGUIDrawer _drawer{};

  CompositeState(StateVariant &&s) : currentState{s} {}

  template <typename Event> void on(Event e) noexcept {
    std::visit(
        [&](auto &state) {
          _drawer.printDebug("State ");
          _drawer.printDebug(state.name);
          _drawer.printDebug(" is handling the event.\n");
          state.on(e);
        },
        currentState);
  }

  template <typename S,
            typename std::enable_if<std::is_constructible<StateVariant, S>{},
                                    int>::type = 0>
  void transition(S s) noexcept {
    if (!std::holds_alternative<S>(currentState)) {
      this->exitSubState();
      currentState = s;
      _drawer.printDebug(s.name);
      _drawer.printDebug("\n");
      this->enterSubState();
    }
  }

  template <typename S,
            typename std::enable_if<!std::is_constructible<StateVariant, S>{},
                                    int>::type = 0>
  void transition(S s) noexcept {
    subStateTransition(s);
  }

  void entry() noexcept {
    enterCompositeState();
    enterSubState();
  }

  void exit() noexcept {
    exitSubState();
    exitCompositeState();
  }

  void enterSubState() noexcept {
    std::visit([&](auto &state) { state.entry(); }, currentState);
  }

  void exitSubState() noexcept {
    std::visit([&](auto &state) { state.exit(); }, currentState);
  }

  template <typename S> void subStateTransition(S s) noexcept {
    std::visit([&](auto &state) { state.transition(s); }, currentState);
  }

  virtual void enterCompositeState() noexcept {}
  virtual void exitCompositeState() noexcept {}
};

struct LeafState {
  template <typename S> void transition(S &&) noexcept {}
};

struct Machine;

struct DrawMenu : public LeafState {
  Machine *base;

  DrawMenu(Machine *base) : base{base} {}

  template <typename Event> void on(Event) {}

  void entry() noexcept;
  void exit() noexcept;

  void on(a_button_up) noexcept;
  void on(b_button_up) noexcept;
  void on(joystick_up) noexcept;
  void on(joystick_down) noexcept;

  enum class menu_state { BACK, CLEAR, SAVE, PLOT, EXIT, NUM_ITEMS };
  Menu<menu_state, menu_state::BACK> menu{
      {"Back", "Clear", "Save", "Plot", "Exit"}};

  static constexpr const char *name = "DrawMenu";
};

struct DrawDefault : public LeafState {
  Machine *base;

  DrawDefault(Machine *base) : base{base} {}

  template <typename Event> void on(Event) {}

  void on(a_button_up) noexcept;
  void on(b_button_up) noexcept;
  void on(JoystickSample) noexcept;

  void entry() noexcept;
  void exit() noexcept;

  static constexpr const char *name = "DrawDefault";
};

using DrawState = std::variant<DrawDefault, DrawMenu>;

struct Draw : public CompositeState<DrawState> {
  using super_t = CompositeState<DrawState>;
  Machine *base;

  Draw(Machine *base);

  // template <typename Event> void on(Event e) noexcept {
  //   std::visit([&](auto &state) { state.on(e); }, currentState);
  // }

  void enterCompositeState() noexcept override;
  void exitCompositeState() noexcept override;

  static constexpr const char *name = "Draw";
};

struct Start : public LeafState {
  Machine *base;

  Start(Machine *base) : base{base} {}

  void entry() noexcept;
  void exit() noexcept;

  void on(a_button_up) noexcept;
  void on(joystick_up) noexcept;
  void on(joystick_down) noexcept;

  template <typename Event> void on(Event) noexcept {}

  enum class menu_state { GALLERY, DRAW, NUM_ITEMS };
  Menu<menu_state, menu_state::GALLERY> menu{{"Gallery", "Draw"}};

  static constexpr const char *name = "Start";
};

struct PlotPlotting : public LeafState {
  Machine *base;
  Point lastModelPoint;

  PlotPlotting(Machine *base) : base{base} {}

  template <typename Event> void on(Event) {}

  void on(a_button_up) noexcept;
  // void on(b_button_up) noexcept;
  void on(timestep) noexcept;

  void entry() noexcept;
  void exit() noexcept;

  static constexpr const char *name = "PlotPlotting";
};

struct PlotPaused : public LeafState {
  Machine *base;

  PlotPaused(Machine *base) : base{base} {}

  template <typename Event> void on(Event) {}

  void on(a_button_up) noexcept;
  void on(b_button_up) noexcept;

  void entry() noexcept;
  void exit() noexcept;

  static constexpr const char *name = "PlotPaused";
};

using PlotState = std::variant<PlotPaused, PlotPlotting>;

struct Plot : public CompositeState<PlotState> {
  using super_t = CompositeState<PlotState>;
  Machine *base;

  Plot(Machine *base);

  void enterCompositeState() noexcept override;
  void exitCompositeState() noexcept override;

  static constexpr const char *name = "Plot";
};

struct GalleryMenu : public LeafState {
  Machine *base;

  GalleryMenu(Machine *base) : base{base} {}

  template <typename Event> void on(Event) {}

  void entry() noexcept;
  void exit() noexcept;

  void on(a_button_up) noexcept;
  void on(b_button_up) noexcept;
  void on(joystick_up) noexcept;
  void on(joystick_down) noexcept;

  enum class menu_state { BACK, DELETE, PLOT, EDIT, EXIT, NUM_ITEMS };
  Menu<menu_state, menu_state::BACK> menu{
      {"Back", "Delete", "Plot", "Edit", "Exit"}};

  static constexpr const char *name = "GalleryMenu";
};

struct GalleryDefault : public LeafState {
  Machine *base;

  GalleryDefault(Machine *base) : base{base} {}

  template <typename Event> void on(Event) {}

  void on(a_button_up) noexcept;
  void on(b_button_up) noexcept;

  void on(joystick_left) noexcept;
  void on(joystick_right) noexcept;
  void on(joystick_up) noexcept;
  void on(joystick_down) noexcept;

  void entry() noexcept;
  void exit() noexcept;

  static constexpr const char *name = "GalleryDefault";

private:
  void drawBorders() noexcept;
};

using GalleryState = std::variant<GalleryDefault, GalleryMenu>;

struct Gallery : public CompositeState<GalleryState> {
  using super_t = CompositeState<GalleryState>;
  Machine *base;

  Gallery(Machine *base);

  void enterCompositeState() noexcept override;
  void exitCompositeState() noexcept override;

  static constexpr const char *name = "Gallery";
};

using State = std::variant<Start, Draw, Plot, Gallery>;
struct Machine : public CompositeState<State> {
  using super_t = CompositeState<State>;
  Machine(Model *model);
  void start() noexcept;

  Model *model;
  uGUIDrawer drawer{};

  static constexpr const char *name = "Machine";
};

} // namespace MATSE::MCT

#endif