#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include "matrix.h"

TEST_CASE("math operations on matrices work", "[matrix]") {
    Mat3x3f a;
    Mat3x3f b;

    a[0] = {1,2,3};
    a[1] = {4,5,6};
    a[2] = {7,8,9};

    b[0] = {10, 3, -1};
    b[1] = {-5, 1, 0};
    b[2] = {-2, 3, 8};

    SECTION("equal comparision") {
        a = b;
        REQUIRE((a == b));
    }

    SECTION("addition") {
        Mat3x3f r;
        r[0] = {11,5,2};
        r[1] = {-1, 6, 6};
        r[2] = {5, 11, 17};
        REQUIRE(a + b == r);
    }

    SECTION("substraction") {
        Mat3x3f r;
        r[0] = {-9, -1, 4};
        r[1] = {9, 4, 6};
        r[2] = {9, 5, 1};
        REQUIRE(a - b == r);
    }

    SECTION("scalar multiplication") {
        Mat3x3f r;
        r[0] = {2,4,6};
        r[1] = {8,10,12};
        r[2] = {14,16,18};
        REQUIRE(a * 2 == r);
    }

    SECTION("matrix multiplication") {
        Mat3x3f r;
        r[0] = {-6, 14, 23};
        r[1] = {3, 35, 44};
        r[2] = {12, 56, 65};
        REQUIRE(a * b == r);
    }
}

TEST_CASE("other operations on matrices work", "[matrix]") {
    SECTION("identity matrix") {
        Mat4x4f m;
        m.identity();
        for(int i = 0; i < 4; i++)
            for(int j = 0; j < 4; j++)
                if(i == j)
                    REQUIRE(m[i][j] == 1);
                else
                    REQUIRE(m[i][j] == 0);
    }

    SECTION("set column") {
        Mat3x3f m;
        m.identity();
        m.set_column(0, {5,6,7});
        m.set_column(1, {2,3,4});

        Mat3x3f r;
        r[0] = {5,2,0};
        r[1] = {6,3,0};
        r[2] = {7,4,1};
        REQUIRE(m == r);
    }
}
