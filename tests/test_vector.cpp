#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include "math_vector.h"

TEST_CASE("math operations on vectors work", "[math_vector]") {
    Vector3f a(1.0f, 2.0f, 3.0f);
    Vector3f b(5.0f, 4.0f, 9.0f);

    SECTION("equal comparision") {
        a = b;
        REQUIRE((a == b));
    }

    SECTION("addition") {
        Vector3f r(6.0f, 6.0f, 12.0f);
        REQUIRE(a + b == r);
    }

    SECTION("substraction") {
        Vector3f r(-4.0f, -2.0f, -6.0f);
        REQUIRE(a - b == r);
    }

    SECTION("scalar multiplication") {
        Vector3f r(2.0f, 4.0f, 6.0f);
        Vector3f r2(0.5f, 1.0f, 1.5f);
        REQUIRE(a * 2 == r);
        REQUIRE(a * (1/2.) == r2);
    }

    SECTION("vector multiplication (dot product)") {
        REQUIRE(a * b == 40.0f);
    }

    SECTION("cross product") {
        Vector3f r(6.0f, 6.0f, -6.0f);
        Vector3f r2(-6.0f, -6.0f, 6.0f);
        REQUIRE(a.cross(b) == r);
        REQUIRE(b.cross(a) == r2);
    }

    SECTION("length and normalization") {
        double r = std::sqrt(14);
        REQUIRE(a.length() == r);

        Vector3f nr(1.0f/r, 2.0f/r, 3.0f/r);
        REQUIRE(a.normalize() == nr);
        REQUIRE(a == nr);
    }
}

