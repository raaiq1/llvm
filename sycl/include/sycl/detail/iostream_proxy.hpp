#pragma once
#include "defines_elementary.hpp"
#include "export.hpp"
#include <istream>
#include <ostream>

namespace sycl {
__SYCL_INLINE_VER_NAMESPACE(_V1) {
namespace detail {
__SYCL_EXPORT extern std::ostream &cout;
__SYCL_EXPORT extern std::ostream &clog;
__SYCL_EXPORT extern std::ostream &cerr;
__SYCL_EXPORT extern std::istream &cin;
} // namespace detail
} // __SYCL_INLINE_VER_NAMESPACE(_V1)
} // namespace sycl
