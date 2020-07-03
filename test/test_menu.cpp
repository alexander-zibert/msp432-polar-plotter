#include "Menu.hpp"
#include <catch2/catch.hpp>
#include <string>

TEST_CASE("wrap-around works") {
  enum class test { TEST_1, TEST_2, TEST_3, NUM_ITEMS };
  MATSE::MCT::Menu<test, test::TEST_1> m{{"foo", "bar", "baz"}};
  REQUIRE(m.getCurrent() == test::TEST_1);
  m.down();
  REQUIRE(m.getCurrent() == test::TEST_2);
  m.down();
  REQUIRE(m.getCurrent() == test::TEST_3);
  m.down();
  REQUIRE(m.getCurrent() == test::TEST_1);
  m.up();
  REQUIRE(m.getCurrent() == test::TEST_3);
  m.up();
  REQUIRE(m.getCurrent() == test::TEST_2);
  m.up();
  REQUIRE(m.getCurrent() == test::TEST_1);
}

TEST_CASE("items can be retrieved") {
  enum class test { TEST_1, TEST_2, NUM_ITEMS };
  MATSE::MCT::Menu<test, test::TEST_1> m{{"foo", "bar"}};
  auto items = m.getItems();
  REQUIRE(items.size() == 2);
  REQUIRE(std::string{items[0]} == "foo");
  REQUIRE(std::string{items[1]} == "bar");
}
