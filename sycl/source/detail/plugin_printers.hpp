//==--------- plugin_printers.hpp - Printers for the Plugin Interface ------==//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

// Print functions used for the Plguin Interface tracing.

#pragma once

#include <sycl/detail/pi.hpp>

#include <type_traits>

namespace sycl {
__SYCL_INLINE_VER_NAMESPACE(_V1) {
namespace detail {
namespace pi {

template <typename T>
inline typename std::enable_if<!std::is_pointer<T>::value, void>::type
print(T val) {
  sycl::detail::cout << "<unknown> : " << val << std::endl;
}

template <typename T>
inline typename std::enable_if<std::is_pointer<T>::value, void>::type
print(T val) {
  sycl::detail::cout << "<unknown> : " << reinterpret_cast<const void *>(val)
                     << std::endl;
}

template <> inline void print<>(PiPlatform val) {
  sycl::detail::cout << "pi_platform : " << val << std::endl;
}

template <> inline void print<>(PiEvent val) {
  sycl::detail::cout << "pi_event : " << val << std::endl;
}

template <> inline void print<>(PiMem val) {
  sycl::detail::cout << "pi_mem : " << val << std::endl;
}

template <> inline void print<>(PiEvent *val) {
  sycl::detail::cout << "pi_event * : " << val;
  if (val)
    sycl::detail::cout << "[ " << *val << " ... ]";
  else
    sycl::detail::cout << "[ nullptr ]";
  sycl::detail::cout << std::endl;
}

template <> inline void print<>(const PiEvent *val) {
  sycl::detail::cout << "const pi_event * : " << val;
  if (val)
    sycl::detail::cout << "[ " << *val << " ... ]";
  else
    sycl::detail::cout << "[ nullptr ]";
  sycl::detail::cout << std::endl;
}

template <> inline void print<>(pi_buffer_region rgn) {
  sycl::detail::cout << "pi_buffer_region origin/size : " << rgn->origin << "/"
                     << rgn->size << std::endl;
}

template <> inline void print<>(pi_buff_rect_region rgn) {
  sycl::detail::cout << "pi_buff_rect_region width_bytes/height/depth : "
                     << rgn->width_bytes << "/" << rgn->height_scalar << "/"
                     << rgn->depth_scalar << std::endl;
}

template <> inline void print<>(pi_buff_rect_offset off) {
  sycl::detail::cout << "pi_buff_rect_offset x_bytes/y/z : " << off->x_bytes
                     << "/" << off->y_scalar << "/" << off->z_scalar
                     << std::endl;
}

template <> inline void print<>(pi_image_region rgn) {
  sycl::detail::cout << "pi_image_region width/height/depth : " << rgn->width
                     << "/" << rgn->height << "/" << rgn->depth << std::endl;
}

template <> inline void print<>(pi_image_offset off) {
  sycl::detail::cout << "pi_image_offset x/y/z : " << off->x << "/" << off->y
                     << "/" << off->z << std::endl;
}

template <> inline void print<>(const pi_image_desc *desc) {
  sycl::detail::cout << "image_desc w/h/d : " << desc->image_width << " / "
                     << desc->image_height << " / " << desc->image_depth
                     << "  --  arrSz/row/slice : " << desc->image_array_size
                     << " / " << desc->image_row_pitch << " / "
                     << desc->image_slice_pitch
                     << "  --  num_mip_lvls/num_smpls/image_type : "
                     << desc->num_mip_levels << " / " << desc->num_samples
                     << " / " << desc->image_type << std::endl;
}

template <> inline void print<>(PiResult val) {
  sycl::detail::cout << "pi_result : ";
  if (val == PI_SUCCESS)
    sycl::detail::cout << "PI_SUCCESS" << std::endl;
  else
    sycl::detail::cout << val << std::endl;
}

// cout does not resolve a nullptr.
template <> inline void print<>(std::nullptr_t) {
  sycl::detail::cout << "<nullptr>" << std::endl;
}

template <> inline void print<>(char *val) {
  sycl::detail::cout << "<char * > : " << static_cast<void *>(val) << std::endl;
}

template <> inline void print<>(const char *val) {
  sycl::detail::cout << "<const char *>: " << val << std::endl;
}

inline void printArgs(void) {}
template <typename Arg0, typename... Args>
void printArgs(Arg0 arg0, Args... args) {
  sycl::detail::cout << "\t";
  print(arg0);
  pi::printArgs(std::forward<Args>(args)...);
}

template <typename T> struct printOut {
  printOut(T) {}
}; // Do nothing

template <> struct printOut<PiEvent *> {
  printOut(PiEvent *val) {
    sycl::detail::cout << "\t[out]pi_event * : " << val;
    if (val)
      sycl::detail::cout << "[ " << *val << " ... ]";
    else
      sycl::detail::cout << "[ nullptr ]";
    sycl::detail::cout << std::endl;
  }
};

template <> struct printOut<PiMem *> {
  printOut(PiMem *val) {
    sycl::detail::cout << "\t[out]pi_mem * : " << val;
    if (val)
      sycl::detail::cout << "[ " << *val << " ... ]";
    else
      sycl::detail::cout << "[ nullptr ]";
    sycl::detail::cout << std::endl;
  }
};

template <> struct printOut<void *> {
  printOut(void *val) {
    sycl::detail::cout << "\t[out]void * : " << val << std::endl;
  }
};

template <typename T> struct printOut<T **> {
  printOut(T **val) {
    sycl::detail::cout << "\t[out]<unknown> ** : " << val;
    if (val)
      sycl::detail::cout << "[ " << *val << " ... ]";
    else
      sycl::detail::cout << "[ nullptr ]";
    sycl::detail::cout << std::endl;
  }
};

inline void printOuts(void) {}
template <typename Arg0, typename... Args>
void printOuts(Arg0 arg0, Args... args) {
  using T = decltype(arg0);
  printOut<T> a(arg0);
  printOuts(std::forward<Args>(args)...);
}

} // namespace pi
} // namespace detail
} // __SYCL_INLINE_VER_NAMESPACE(_V1)
} // namespace sycl
