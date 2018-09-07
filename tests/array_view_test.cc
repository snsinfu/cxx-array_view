// Copyright snsinfu 2018.
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <array>
#include <cstddef>
#include <iterator>
#include <stdexcept>
#include <type_traits>
#include <vector>

#include "catch.hpp"
#include "../include/array_view.hpp"


TEST_CASE("array_view::value_type - is not qualified")
{
    CHECK(std::is_same<cxx::array_view<int>::value_type, int>::value);
    CHECK(std::is_same<cxx::array_view<int const>::value_type, int>::value);
}

TEST_CASE("array_view::pointer - is qualified")
{
    CHECK(std::is_same<cxx::array_view<int>::pointer, int*>::value);
    CHECK(std::is_same<cxx::array_view<int const>::pointer, int const*>::value);
}

TEST_CASE("array_view::reference - is qualified")
{
    CHECK(std::is_same<cxx::array_view<int>::reference, int&>::value);
    CHECK(std::is_same<cxx::array_view<int const>::reference, int const&>::value);
}

TEST_CASE("array_view::size_type - is size_t")
{
    CHECK(std::is_same<cxx::array_view<int>::size_type, std::size_t>::value);
}

TEST_CASE("array_view::iterator - is random access iterator")
{
    CHECK(
        std::is_same<
            std::iterator_traits<cxx::array_view<int>::iterator>::iterator_category,
            std::random_access_iterator_tag
        >::value
    );
}

TEST_CASE("array_view::reverse_iterator - is std::reverse_iterator")
{
    CHECK(
        std::is_same<
            cxx::array_view<int>::reverse_iterator,
            std::reverse_iterator<cxx::array_view<int>::iterator>
        >::value
    );
}

TEST_CASE("array_view::const_array_view - adds const to element type")
{
    CHECK(
        std::is_same<
            cxx::array_view<int>::const_array_view,
            cxx::array_view<int const>
        >::value
    );
    CHECK(
        std::is_same<
            cxx::array_view<int const>::const_array_view,
            cxx::array_view<int const>
        >::value
    );
}

TEST_CASE("array_view - is default constructible")
{
    cxx::array_view<int> view;
    CHECK(view.empty());
    CHECK(view.data() == nullptr);
    CHECK(view.size() == 0);
}

TEST_CASE("array_view - is constructible from raw pointer-size pair")
{
    int array[5];
    int* const ptr = &array[0];
    std::size_t const size = 5;

    cxx::array_view<int> view{ptr, size};
    CHECK_FALSE(view.empty());
    CHECK(view.data() == ptr);
    CHECK(view.size() == size);
}

TEST_CASE("array_view - is constructible from nullptr-zero pair")
{
    cxx::array_view<int> view{nullptr, 0};
    CHECK(view.empty());
    CHECK(view.data() == nullptr);
    CHECK(view.size() == 0);
}

TEST_CASE("array_view - is copy constructible")
{
    int array[5];
    cxx::array_view<int> view{array, 5};

    cxx::array_view<int> copy_1{view};
    CHECK(copy_1.data() == view.data());
    CHECK(copy_1.size() == view.size());

    cxx::array_view<int> copy_2{const_cast<cxx::array_view<int> const&>(view)};
    CHECK(copy_2.data() == view.data());
    CHECK(copy_2.size() == view.size());
}

TEST_CASE("array_view - is implicitly convertible from raw array")
{
    int array[5];
    cxx::array_view<int> view = array;
    CHECK(view.data() == &array[0]);
    CHECK(view.size() == 5);
}

TEST_CASE("array_view - is implicitly convertible from std::array")
{
    std::array<int, 5> array;
    cxx::array_view<int> view = array;
    CHECK(view.data() == array.data());
    CHECK(view.size() == array.size());
}

TEST_CASE("array_view - is implicitly convertible from std::vector")
{
    std::vector<int> vector(10);
    cxx::array_view<int> view = vector;
    CHECK(view.data() == vector.data());
    CHECK(view.size() == vector.size());
}

TEST_CASE("array_view - is implicitly convertible from string literal")
{
    cxx::array_view<char const> view = "Lorem ipsum dolor sit amet";
    CHECK(view.size() == 27);
    CHECK(view.front() == 'L');
    CHECK(view.back() == '\0');
}

TEST_CASE("array_view - is implicitly convertible to const_array_view")
{
    int array[3];
    cxx::array_view<int> view = array;
    cxx::array_view<int const> const_view = view;
    CHECK(const_view.data() == view.data());
    CHECK(const_view.size() == view.size());
}

TEST_CASE("array_view - prevents illegal array upcasting")
{
    class expression {};
    class unary_expression : public expression {};
    CHECK(std::is_convertible<expression(&)[5], cxx::array_view<expression>>::value);
    CHECK_FALSE(std::is_convertible<unary_expression(&)[5], cxx::array_view<expression>>::value);
}

TEST_CASE("array_view - prevents const removal")
{
    CHECK(std::is_convertible<int(&)[5], cxx::array_view<int>>::value);
    CHECK(std::is_convertible<int const(&)[5], cxx::array_view<int const>>::value);
    CHECK_FALSE(std::is_convertible<int const(&)[5], cxx::array_view<int>>::value);
}

TEST_CASE("array_view::front - returns a reference to the first element")
{
    int array[5] {};
    cxx::array_view<int> view = array;
    int& ref = view.front();
    ref = 10;
    CHECK(array[0] == 10);
}

TEST_CASE("array_view::back - returns a reference to the last element")
{
    int array[5] {};
    cxx::array_view<int> view = array;
    int& ref = view.back();
    ref = 10;
    CHECK(array[4] == 10);
}

TEST_CASE("array_view::operator[] - returns a reference to the element at given position")
{
    int array[5] {};
    cxx::array_view<int> view = array;
    int& ref = view[3];
    ref = 10;
    CHECK(array[3] == 10);
}

TEST_CASE("array_view::at - returns a reference to the element at given position")
{
    int array[5] {};
    cxx::array_view<int> view = array;
    int& ref = view.at(3);
    ref = 10;
    CHECK(array[3] == 10);
}

TEST_CASE("array_view::at - throws std::out_of_range on access to invalid position")
{
    int array[5] {};
    cxx::array_view<int> view = array;
    CHECK_THROWS_AS(view.at(5), std::out_of_range);
}

TEST_CASE("array_view - supports range-based for loop")
{
    int array[3] {};
    cxx::array_view<int> view = array;
    for (int& element : view) {
        element = 42;
    }
    CHECK(array[0] == 42);
    CHECK(array[1] == 42);
    CHECK(array[2] == 42);
}

TEST_CASE("array_view::begin/end - return random access iterator")
{
    int array[3] = {1, 2, 3};
    cxx::array_view<int> view = array;
    cxx::array_view<int>::iterator iter = view.begin();
    CHECK(*iter == 1);
    CHECK(iter[1] == 2);
    CHECK(*(iter + 2) == 3);
    CHECK(view.end() == iter + 3);
    CHECK(view.end() - view.begin() == 3);
}

TEST_CASE("array_view::rbegin/rend - return reverse iterator")
{
    int array[3] = {1, 2, 3};
    cxx::array_view<int> view = array;
    auto iter = view.rbegin();
    CHECK(*iter == 3);
    iter++;
    CHECK(*iter == 2);
    iter++;
    CHECK(*iter == 1);
    iter++;
    CHECK(iter == view.rend());
}

TEST_CASE("array_view::as_const - returns an array_view with const element access")
{
    int array[3];
    cxx::array_view<int> view = array;
    auto const_view = view.as_const();
    cxx::array_view<int const>& const_view_ref = const_view;
    CHECK(const_view_ref.data() == view.data());
    CHECK(const_view_ref.size() == view.size());
}

TEST_CASE("array_view::swap - swaps viewed array")
{
    int array_1[3] = {1, 2, 3};
    int array_2[5] = {5, 6, 7, 8, 9};
    cxx::array_view<int> view_1 = array_1;
    cxx::array_view<int> view_2 = array_2;
    view_1.swap(view_2);
    CHECK(view_1.data() == &array_2[0]);
    CHECK(view_1.size() == 5);
    CHECK(view_2.data() == &array_1[0]);
    CHECK(view_2.size() == 3);
}

TEST_CASE("array_view::subview - returns a view of subarray")
{
    int array[5];
    cxx::array_view<int> view = array;
    cxx::array_view<int> subview = view.subview(1, 3);
    CHECK(subview.data() == &array[1]);
    CHECK(subview.size() == 3);
}

TEST_CASE("array_view::first - returns a view of leading subarray")
{
    int array[5];
    cxx::array_view<int> view = array;
    cxx::array_view<int> first = view.first(3);
    CHECK(first.data() == &array[0]);
    CHECK(first.size() == 3);
}

TEST_CASE("array_view::last - returns a view of trailing subarray")
{
    int array[5];
    cxx::array_view<int> view = array;
    cxx::array_view<int> first = view.last(3);
    CHECK(first.data() == &array[2]);
    CHECK(first.size() == 3);
}
