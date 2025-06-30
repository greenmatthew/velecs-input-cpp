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

#include <stdint.h>

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

/// @brief Bitwise OR operator for combining InputStatus flags
/// @param a First status flag
/// @param b Second status flag  
/// @return Combined status flags
InputStatus operator|(const InputStatus a, const InputStatus b);

/// @brief Bitwise OR assignment operator for combining InputStatus flags
/// @param a Status flag to modify (non-const reference)
/// @param b Status flag to combine with a
/// @return Reference to modified a
InputStatus& operator|=(InputStatus& a, const InputStatus b);

/// @brief Bitwise AND operator for testing InputStatus flags
/// @param a First status flag
/// @param b Second status flag
/// @return Intersection of status flags
InputStatus operator&(const InputStatus a, const InputStatus b);

/// @brief Bitwise AND assignment operator for masking InputStatus flags
/// @param a Status flag to modify (non-const reference)
/// @param b Status flag to mask with
/// @return Reference to modified a
InputStatus& operator&=(InputStatus& a, const InputStatus b);

/// @brief Check if a status contains any of the specified flags
/// @param status The status to check
/// @param flags The flags to test for
/// @return true if status contains any of the specified flags
inline bool HasAnyFlag(const InputStatus status, const InputStatus flags)
{
    return (status & flags) != InputStatus::Idle;
}

/// @brief Check if a status contains all of the specified flags
/// @param status The status to check
/// @param flags The flags to test for
/// @return true if status contains all of the specified flags
inline bool HasAllFlags(const InputStatus status, const InputStatus flags)
{
    return (status & flags) == flags;
}

} // namespace velecs::input
