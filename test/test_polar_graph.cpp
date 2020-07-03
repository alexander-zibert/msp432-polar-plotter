#include "Machine.hpp"
#include <catch2/catch.hpp>
#include <iostream>

TEST_CASE("start") {
  using namespace MATSE::MCT;
  auto m = Machine{};
  REQUIRE(m.getCurrentState() == state::START);
  m.handle(event::JOYSTICK_DOWN);
  REQUIRE(m.getCurrentState() == state::START);
  m.handle(event::JOYSTICK_LEFT);
  REQUIRE(m.getCurrentState() == state::START);
  m.handle(event::JOYSTICK_RIGHT);
  REQUIRE(m.getCurrentState() == state::START);
  m.handle(event::JOYSTICK_UP);
  REQUIRE(m.getCurrentState() == state::START);
}

TEST_CASE("start->draw") {
  using namespace MATSE::MCT;
  auto m = Machine{};
  REQUIRE(m.getCurrentState() == state::START);
  m.handle(event::A_BUTTON_UP);
  REQUIRE(m.getCurrentState() == state::DRAW);
}

TEST_CASE("start->gallery->menu.back->start") {
  using namespace MATSE::MCT;
  auto m = Machine{};
  REQUIRE(m.getCurrentState() == state::START);
  m.handle(event::JOYSTICK_DOWN);
  REQUIRE(m.getCurrentState() == state::START);
  m.handle(event::A_BUTTON_UP);
  REQUIRE(m.getCurrentState() == state::GALLERY);
  m.handle(event::A_BUTTON_UP);
  REQUIRE(m.getCurrentState() == state::GALLERY);
  m.handle(event::B_BUTTON_UP);
  REQUIRE(m.getCurrentState() == state::GALLERY);
  m.handle(event::B_BUTTON_UP);
  REQUIRE(m.getCurrentState() == state::START);
}

TEST_CASE("start->draw->menu.back->draw") {
  using namespace MATSE::MCT;
  auto m = Machine{};
  REQUIRE(m.getCurrentState() == state::START);
  m.handle(event::A_BUTTON_UP);
  REQUIRE(m.getCurrentState() == state::DRAW);
  m.handle(event::B_BUTTON_UP);
  REQUIRE(m.getCurrentState() == state::DRAW);
  m.handle(event::A_BUTTON_UP);
  REQUIRE(m.getCurrentState() == state::DRAW);
}

TEST_CASE("start->draw->menu->B->draw") {
  using namespace MATSE::MCT;
  auto m = Machine{};
  REQUIRE(m.getCurrentState() == state::START);
  m.handle(event::A_BUTTON_UP);
  REQUIRE(m.getCurrentState() == state::DRAW);
  m.handle(event::B_BUTTON_UP);
  REQUIRE(m.getCurrentState() == state::DRAW);
  m.handle(event::B_BUTTON_UP);
  REQUIRE(m.getCurrentState() == state::DRAW);
}

TEST_CASE("start->draw->menu.plot->plot") {
  using namespace MATSE::MCT;
  auto m = Machine{};
  REQUIRE(m.getCurrentState() == state::START);
  m.handle(event::A_BUTTON_UP);
  REQUIRE(m.getCurrentState() == state::DRAW);
  m.handle(event::B_BUTTON_UP);
  REQUIRE(m.getCurrentState() == state::DRAW);
  m.handle(event::JOYSTICK_DOWN);
  REQUIRE(m.getCurrentState() == state::DRAW);
  m.handle(event::A_BUTTON_UP);
  REQUIRE(m.getCurrentState() == state::PLOT);
}

TEST_CASE("start->draw->menu.save->draw") {
  using namespace MATSE::MCT;
  auto m = Machine{};
  REQUIRE(m.getCurrentState() == state::START);
  m.handle(event::A_BUTTON_UP);
  REQUIRE(m.getCurrentState() == state::DRAW);
  m.handle(event::B_BUTTON_UP);
  REQUIRE(m.getCurrentState() == state::DRAW);
  m.handle(event::JOYSTICK_DOWN);
  REQUIRE(m.getCurrentState() == state::DRAW);
  m.handle(event::JOYSTICK_DOWN);
  REQUIRE(m.getCurrentState() == state::DRAW);
  m.handle(event::A_BUTTON_UP);
  REQUIRE(m.getCurrentState() == state::DRAW);
}

TEST_CASE("start->draw->menu.exit->start") {
  using namespace MATSE::MCT;
  auto m = Machine{};
  REQUIRE(m.getCurrentState() == state::START);
  m.handle(event::A_BUTTON_UP);
  REQUIRE(m.getCurrentState() == state::DRAW);
  m.handle(event::B_BUTTON_UP);
  REQUIRE(m.getCurrentState() == state::DRAW);
  m.handle(event::JOYSTICK_DOWN);
  REQUIRE(m.getCurrentState() == state::DRAW);
  m.handle(event::JOYSTICK_DOWN);
  REQUIRE(m.getCurrentState() == state::DRAW);
  m.handle(event::JOYSTICK_DOWN);
  REQUIRE(m.getCurrentState() == state::DRAW);
  m.handle(event::A_BUTTON_UP);
  REQUIRE(m.getCurrentState() == state::START);
}