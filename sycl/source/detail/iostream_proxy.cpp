#include <iostream>
#include <sycl/detail/iostream_proxy.hpp>

namespace sycl {
__SYCL_INLINE_VER_NAMESPACE(_V1) {
namespace detail {
std::ostream &cout = std::cout;
std::ostream &clog = std::clog;
std::ostream &cerr = std::cerr;
std::istream &cin = std::cin;
} // namespace detail
} // __SYCL_INLINE_VER_NAMESPACE(_V1)
} // namespace sycl