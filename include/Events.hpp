#ifndef MATSE_MCT_EVENTS_HPP
#define MATSE_MCT_EVENTS_HPP

namespace MATSE::MCT {
struct ButtonA {
  const bool pressed = true;
};
struct ButtonB {
  const bool pressed = true;
};
struct Joystick {
  const double x;
  const double y;
};
struct a_button_up {};
struct b_button_up {};
struct joystick_left {};
struct joystick_right {};
struct joystick_up {};
struct joystick_down {};
struct timestep {};

} // namespace MATSE::MCT

#endif