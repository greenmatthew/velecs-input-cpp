/// @file    InputStatus.hpp
/// @author  Matthew Green
/// @date    2025-06-25 16:57:04
/// 
/// @section LICENSE
/// 
/// Copyright (c) 2025 Matthew Green - All rights reserved
/// Unauthorized copying of this file, via any medium is strictly prohibited
/// Proprietary and confidential

#pragma once

#include <velecs/common/BitfieldEnum.hpp>

#include <cstdint>

namespace velecs::input {

/// @enum InputStatus
/// @brief Status flags indicating the state of input processing for bindings and actions
///
/// These flags can be combined using bitwise operators to represent multiple states
/// simultaneously. For example, an input can be both Started and Performed in the same frame.
enum class InputStatus : uint32_t {
    Idle      = 0,        ///< No input activity
    Started   = 1 << 0,   ///< Input just became active this frame (bit 0)
    Performed = 1 << 1,   ///< Input is currently active (bit 1)
    Cancelled = 1 << 2,   ///< Input just became inactive this frame (bit 2)
};

} // namespace velecs::input

namespace velecs::common {

/// @brief Template specialization to enable bitfield operations for ModifierKey
template<>
struct EnableBitfieldEnum<velecs::input::InputStatus> : std::true_type {};

} // namespace velecs::common
