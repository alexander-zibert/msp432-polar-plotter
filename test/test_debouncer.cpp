#include <catch2/catch.hpp>
#include <etl/debounce.h>

TEST_CASE("etl::debounce::is_set works as expected") {
  auto debouncer = etl::debounce<2, 2, 2>();
  REQUIRE(!debouncer.is_set());

  // 1 true samples, 1 false sample -> not set
  debouncer.add(true);
  REQUIRE(!debouncer.is_set());
  REQUIRE(!debouncer.has_changed());
  debouncer.add(false);
  REQUIRE(!debouncer.is_set());
  REQUIRE(!debouncer.has_changed());

  // 2 true samples -> set
  debouncer.add(true);
  REQUIRE(!debouncer.is_set());
  REQUIRE(!debouncer.has_changed());
  debouncer.add(true);
  REQUIRE(debouncer.is_set());
  REQUIRE(debouncer.has_changed());

  // 1 false samples, 1 true sample -> set
  debouncer.add(false);
  REQUIRE(debouncer.is_set());
  REQUIRE(!debouncer.has_changed());
  debouncer.add(true);
  REQUIRE(debouncer.is_set());
  REQUIRE(!debouncer.has_changed());

  // 2 false samples -> not set
  debouncer.add(false);
  REQUIRE(debouncer.is_set());
  REQUIRE(!debouncer.has_changed());
  debouncer.add(false);
  REQUIRE(!debouncer.is_set());
  REQUIRE(debouncer.has_changed());
}

TEST_CASE("etl::debounce::is_hold works as expected") {
  auto debouncer = etl::debounce<3, 2, 2>();
  debouncer.add(true);
  debouncer.add(true);
  debouncer.add(true);
  REQUIRE(debouncer.is_set());

  // 1 true, 1 false sample -> not held
  debouncer.add(true);
  REQUIRE(!debouncer.is_held());
  REQUIRE(!debouncer.has_changed());
  debouncer.add(false);
  REQUIRE(!debouncer.is_held());
  REQUIRE(!debouncer.has_changed());

  // HOLD_COUNT = 2 true samples -> held
  debouncer.add(true);
  REQUIRE(!debouncer.is_held());
  REQUIRE(!debouncer.has_changed());
  debouncer.add(true);
  REQUIRE(debouncer.is_held());
  REQUIRE(debouncer.has_changed());

  // VALID_COUNT = 3 false samples
  debouncer.add(false);
  REQUIRE(debouncer.is_held());
  REQUIRE(!debouncer.has_changed());
  debouncer.add(false);
  REQUIRE(debouncer.is_held());
  REQUIRE(!debouncer.has_changed());
  debouncer.add(false);
  REQUIRE(!debouncer.is_set());
  REQUIRE(!debouncer.is_held());
  REQUIRE(debouncer.has_changed());
}

TEST_CASE("etl::debounce::is_repeating works as expected") {
  auto debouncer = etl::debounce<4, 3, 2>();
  debouncer.add(true);
  debouncer.add(true);
  debouncer.add(true);
  debouncer.add(true);
  debouncer.add(true);
  debouncer.add(true);
  debouncer.add(true);
  REQUIRE(debouncer.is_set());
  REQUIRE(debouncer.is_held());

  // 1 true, 1 false sample -> not repeating
  debouncer.add(true);
  REQUIRE(!debouncer.is_repeating());
  REQUIRE(!debouncer.has_changed());
  debouncer.add(false);
  REQUIRE(!debouncer.is_repeating());
  REQUIRE(!debouncer.has_changed());

  // REPEAT_COUNT = 2 true samples -> repeating
  debouncer.add(true);
  REQUIRE(!debouncer.is_repeating());
  REQUIRE(!debouncer.has_changed());
  debouncer.add(true);
  REQUIRE(debouncer.is_repeating());
  REQUIRE(debouncer.has_changed());

  // REPEAT_COUNT = 2 true samples -> repeating
  debouncer.add(true);
  REQUIRE(debouncer.is_repeating());
  REQUIRE(!debouncer.has_changed());
  debouncer.add(true);
  REQUIRE(debouncer.is_repeating());
  REQUIRE(debouncer.has_changed());

  // 2 false, 2 true samples
  debouncer.add(false);
  REQUIRE(debouncer.is_repeating());
  REQUIRE(!debouncer.has_changed());
  debouncer.add(false);
  REQUIRE(debouncer.is_repeating());
  REQUIRE(!debouncer.has_changed());
  debouncer.add(true);
  REQUIRE(debouncer.is_repeating());
  REQUIRE(!debouncer.has_changed());
  debouncer.add(true);
  REQUIRE(debouncer.is_repeating());
  REQUIRE(debouncer.has_changed());

  // VALID_COUNT = 4 false samples
  debouncer.add(false);
  REQUIRE(debouncer.is_repeating());
  REQUIRE(!debouncer.has_changed());
  debouncer.add(false);
  REQUIRE(debouncer.is_repeating());
  REQUIRE(!debouncer.has_changed());
  debouncer.add(false);
  REQUIRE(debouncer.is_repeating());
  REQUIRE(!debouncer.has_changed());
  debouncer.add(false);
  REQUIRE(!debouncer.is_set());
  REQUIRE(!debouncer.is_held());
  REQUIRE(!debouncer.is_repeating());
  REQUIRE(debouncer.has_changed());
}