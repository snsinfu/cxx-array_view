// Copyright snsinfu 2018.
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <array>
#include <vector>

#include "catch.hpp"
#include "../include/cxx/array_view.hpp"


TEST_CASE("data - observes raw array pointer")
{
    int arr[10];
    CHECK(cxx::array_view_detail::data(arr) == arr);
}

TEST_CASE("data - observes std::array pointer")
{
    std::array<int, 10> arr;
    CHECK(cxx::array_view_detail::data(arr) == arr.data());
}

TEST_CASE("data - observes std::vector pointer")
{
    std::vector<int> vec(10);
    CHECK(cxx::array_view_detail::data(vec) == vec.data());
}

TEST_CASE("size - observes raw array length")
{
    int arr[10];
    CHECK(cxx::array_view_detail::size(arr) == 10);
}

TEST_CASE("data - observes std::array length")
{
    std::array<int, 10> arr;
    CHECK(cxx::array_view_detail::size(arr) == arr.size());
}

TEST_CASE("size - observes std::vector length")
{
    std::vector<int> vec(10);
    CHECK(cxx::array_view_detail::size(vec) == vec.size());
}

TEST_CASE("size - observes std::initializer_list")
{
    std::initializer_list<int> list = {1, 2, 3, 4};
    CHECK(cxx::array_view_detail::size(list) == 4);
}
