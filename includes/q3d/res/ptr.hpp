#pragma once

#include <memory>
#include <vector>
#include <cstdint>

namespace q3d {

/// @brief `std::shared_ptr`
/// @tparam _Tp typename to store
template<typename _Tp>
using ptr = std::shared_ptr<_Tp>;

/// @brief `std::unique_ptr`
/// @tparam _Tp typename to store
template<typename _Tp>
using uptr = std::unique_ptr<_Tp>;

using bytes = std::vector<uint8_t>;

} // namespace q3d
