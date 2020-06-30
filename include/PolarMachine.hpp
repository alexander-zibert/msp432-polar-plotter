#ifndef MATSE_MCT_POLAR_MACHINE_HPP
#define MATSE_MCT_POLAR_MACHINE_HPP

#include <boost/sml.hpp>

namespace sml = boost::sml;

namespace MATSE::MCT {
/**
 * EVENTS
 */
struct ButtonA {
  bool pressed = true;
};
struct ButtonB {
  bool pressed = true;
};
struct Joystick {
  double x;
  double y;
};
/**
 * STATES
 */
struct Start {};

/**
 * GUARDS
 */

/**
 * ACTIONS
 */

/**
 * MACHINE
 */
struct PolarMachine {
  auto operator()() const noexcept {
    using namespace sml;

    return make_transition_table();
  }
};
} // namespace MATSE::MCT

#endif