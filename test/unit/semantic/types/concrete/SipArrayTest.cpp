#include "TipArray.h"
#include "TipInt.h"
#include "TipRef.h"
#include "TipBool.h"

#include <catch2/catch_test_macros.hpp>

#include <iostream>
#include <sstream>

TEST_CASE("TipArray: Test getters", "[TipArray]") {
    auto type = std::make_shared<TipInt>();
    TipArray tipArray(type);
    REQUIRE(tipArray.getAddressOfField() == type);
}

TEST_CASE("Tip Array: Test equality", "[TipArray]") {
    auto type = std::make_shared<TipInt>();
    TipArray tipArray1(type);
    SECTION("Equal when fields are of same type") {
        auto type = std::make_shared<TipInt>();
        TipArray tipArray2(type);
        REQUIRE(tipArray1 == tipArray2);
    }
    SECTION("Not equal when fields are of different type") {
        auto type = std::make_shared<TipBool>();
        TipArray tipArray3(type);
        REQUIRE(tipArray1 != tipArray3);
    }
}

TEST_CASE("Tip Array: Test output stream", "[TipArray]") {
    SECTION("Field is an int") {
        auto type = std::make_shared<TipInt>();
        TipArray tipArray1(type);
        std::stringstream stream1;
        stream1 << tipArray1;
        REQUIRE(stream1.str() == "array<int>");
    }
    SECTION("Field is a bool") {
        auto type = std::make_shared<TipBool>();
        TipArray tipArray2(type);
        std::stringstream stream2;
        stream2 << tipArray2;
        REQUIRE(stream2.str() == "array<bool>");
    }
}