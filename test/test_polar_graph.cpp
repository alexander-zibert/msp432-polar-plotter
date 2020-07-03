#include "DrawInterface.hpp"
#include "Machine.hpp"
#include <catch2/catch.hpp>
#include <iostream>

class TestDrawer : public MATSE::MCT::DrawInterface {
public:
  void print(const char *) override {}
};

TestDrawer drawer{};

TEST_CASE("start") {
  using namespace MATSE::MCT;
  Machine m{&drawer};
  REQUIRE(m.getCurrentState() == state::START);
  m.handle(joystick_down{});
  REQUIRE(m.getCurrentState() == state::START);
  m.handle(joystick_left{});
  REQUIRE(m.getCurrentState() == state::START);
  m.handle(joystick_right{});
  REQUIRE(m.getCurrentState() == state::START);
  m.handle(joystick_up{});
  REQUIRE(m.getCurrentState() == state::START);
}

TEST_CASE("start->draw") {
  using namespace MATSE::MCT;
  Machine m{&drawer};
  REQUIRE(m.getCurrentState() == state::START);
  m.handle(a_button_up{});
  REQUIRE(m.getCurrentState() == state::DRAW);
}

TEST_CASE("start->gallery->menu.back->start") {
  using namespace MATSE::MCT;
  Machine m{&drawer};
  REQUIRE(m.getCurrentState() == state::START);
  m.handle(joystick_down{});
  REQUIRE(m.getCurrentState() == state::START);
  m.handle(a_button_up{});
  REQUIRE(m.getCurrentState() == state::GALLERY);
  m.handle(a_button_up{});
  REQUIRE(m.getCurrentState() == state::GALLERY);
  m.handle(b_button_up{});
  REQUIRE(m.getCurrentState() == state::GALLERY);
  m.handle(b_button_up{});
  REQUIRE(m.getCurrentState() == state::START);
}

TEST_CASE("start->draw->menu.back->draw") {
  using namespace MATSE::MCT;
  Machine m{&drawer};
  REQUIRE(m.getCurrentState() == state::START);
  m.handle(a_button_up{});
  REQUIRE(m.getCurrentState() == state::DRAW);
  m.handle(b_button_up{});
  REQUIRE(m.getCurrentState() == state::DRAW);
  m.handle(a_button_up{});
  REQUIRE(m.getCurrentState() == state::DRAW);
}

TEST_CASE("start->draw->menu->B->draw") {
  using namespace MATSE::MCT;
  Machine m{&drawer};
  REQUIRE(m.getCurrentState() == state::START);
  m.handle(a_button_up{});
  REQUIRE(m.getCurrentState() == state::DRAW);
  m.handle(b_button_up{});
  REQUIRE(m.getCurrentState() == state::DRAW);
  m.handle(b_button_up{});
  REQUIRE(m.getCurrentState() == state::DRAW);
}

TEST_CASE("start->draw->menu.plot->plot") {
  using namespace MATSE::MCT;
  Machine m{&drawer};
  REQUIRE(m.getCurrentState() == state::START);
  m.handle(a_button_up{});
  REQUIRE(m.getCurrentState() == state::DRAW);
  m.handle(b_button_up{});
  REQUIRE(m.getCurrentState() == state::DRAW);
  m.handle(joystick_down{});
  REQUIRE(m.getCurrentState() == state::DRAW);
  m.handle(a_button_up{});
  REQUIRE(m.getCurrentState() == state::PLOT);
}

TEST_CASE("start->draw->menu.save->draw") {
  using namespace MATSE::MCT;
  Machine m{&drawer};
  REQUIRE(m.getCurrentState() == state::START);
  m.handle(a_button_up{});
  REQUIRE(m.getCurrentState() == state::DRAW);
  m.handle(b_button_up{});
  REQUIRE(m.getCurrentState() == state::DRAW);
  m.handle(joystick_down{});
  REQUIRE(m.getCurrentState() == state::DRAW);
  m.handle(joystick_down{});
  REQUIRE(m.getCurrentState() == state::DRAW);
  m.handle(a_button_up{});
  REQUIRE(m.getCurrentState() == state::DRAW);
}

TEST_CASE("start->draw->menu.exit->start") {
  using namespace MATSE::MCT;
  Machine m{&drawer};
  REQUIRE(m.getCurrentState() == state::START);
  m.handle(a_button_up{});
  REQUIRE(m.getCurrentState() == state::DRAW);
  m.handle(b_button_up{});
  REQUIRE(m.getCurrentState() == state::DRAW);
  m.handle(joystick_down{});
  REQUIRE(m.getCurrentState() == state::DRAW);
  m.handle(joystick_down{});
  REQUIRE(m.getCurrentState() == state::DRAW);
  m.handle(joystick_down{});
  REQUIRE(m.getCurrentState() == state::DRAW);
  m.handle(a_button_up{});
  REQUIRE(m.getCurrentState() == state::START);
}