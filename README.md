array\_view - non-owning range view of array
============================================

![C++11][cxx-badge]
[![Build Status][travis-badge]][travis-url]
[![Boost License][license-badge]][license-url]

This repository contains a single-file, header-only library of `array_view` class template. It is
a non-owning view of an array similar to [GSL's span][gsl-span] but uses `size_t` for indexing.

```c++
#include <vector>
#include <array_view.hpp>

int main()
{
    std::vector<int> vector(100);
    cxx::array_view<int> view = vector;
    view[0] = 42;
}
```

[cxx-badge]: https://img.shields.io/badge/C%2B%2B-11-orange.svg
[license-badge]: https://img.shields.io/badge/license-Boost-blue.svg
[license-url]: https://raw.githubusercontent.com/snsinfu/cxx-array_view/master/LICENSE.txt
[travis-badge]: https://travis-ci.org/snsinfu/cxx-array_view.svg?branch=master
[travis-url]: https://travis-ci.org/snsinfu/cxx-array_view
[gsl-span]: https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#gslview-views

- [Installation](#installation)
- [Reference](#reference)
- [Index type](#index-type)
- [Testing](#testing)
- [License](#license)


## Installation

This library has no dependency and single header-only. Just download [array\_view.hpp][header] into
your include directory and `#include` it.

```console
curl -LO https://raw.githubusercontent.com/snsinfu/cxx-array_view/master/include/array_view.hpp
```

[header]: https://raw.githubusercontent.com/snsinfu/cxx-array_view/master/include/array_view.hpp

## Reference

`cxx::array_view<T>` constructors:

```c++
array_view() noexcept;
array_view(array_view& other) noexcept;
array_view(array_view const& other) noexcept;
array_view(T* data, size_t size);
array_view(Container& container) noexcept;
```

`cxx::array_view<T>` member functions:

```c++
bool             empty() const noexcept;
size_t           size() const noexcept;
T*               data() const noexcept;

T&               front() const;
T&               back() const;
T&               operator[](size_t index) const;
T&               at(size_t index) const;

iterator         begin() const noexcept;
iterator         end() const noexcept;
reverse_iterator rbegin() const noexcept;
reverse_iterator rend() const noexcept;

const_array_view as_const() const noexcept
void             swap(array_view& other) noexcept;

array_view       subview(size_t start, size_t size) const;
array_view       first(size_t size) const;
array_view       last(size_t size) const;
```

## Index type

`array_view` uses `size_t` for indexing. This is for better compatibility with existing libraries.
I'm actually happy with signed index in languages like Go, but in C++ there are too many existing
code that use `size_t` for indexing. So I stick with unsigned index until the situation changes.

See:

- [ES.107: Don’t use unsigned for subscripts, prefer gsl::index](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#es107-dont-use-unsigned-for-subscripts-prefer-gslindex)
- [GSL #171: size\_type should be unsigned](https://github.com/Microsoft/GSL/issues/171)
- (PDF) [P1089: Sizes Should Only span Unsigned](https://wg21.link/P1089)


## Testing

```console
git clone https://github.com/snsinfu/cxx-array_view
cd cxx-array_view/tests
make
```

## License

Boost Software License, Version 1.0.
