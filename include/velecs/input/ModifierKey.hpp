/// @file    ModifierKey.hpp
/// @author  Matthew Green
/// @date    2025-06-07 14:14:45
/// 
/// @section LICENSE
/// 
/// Copyright (c) 2025 Matthew Green - All rights reserved
/// Unauthorized copying of this file, via any medium is strictly prohibited
/// Proprietary and confidential

#pragma once

#include "velecs/common/BitfieldEnum.hpp"

#include <cstdint>

namespace velecs::input {

/// @enum ModifierKey
/// @brief Bitfield enumeration for keyboard modifier keys that can be combined using bitwise operators.
///
/// @code
/// // Example usage:
/// ModifierKey combo = ModifierKey::Ctrl | ModifierKey::Shift;
/// 
/// // Check if Alt is pressed using helper function
/// if (HasAnyFlag(currentModifiers, ModifierKey::Alt)) {
///     // Alt key is currently pressed (either left or right)
/// }
/// 
/// // Check for specific left shift
/// if (HasAnyFlag(currentModifiers, ModifierKey::LeftShift)) {
///     // Specifically left shift is pressed
/// }
/// 
/// // Combine multiple modifiers
/// ModifierKey requirements = ModifierKey::Ctrl | ModifierKey::Alt;
/// if (HasAllFlags(currentModifiers, requirements)) {
///     // Both Ctrl and Alt are pressed
/// }
/// 
/// // Toggle caps lock state
/// modifiers ^= ModifierKey::CapsLock;
/// @endcode
enum class ModifierKey : uint32_t {
    None        = 0,            /// @brief No modifier keys pressed
    LeftShift   = 1 << 0,       /// @brief Left Shift key
    RightShift  = 1 << 1,       /// @brief Right Shift key
    Shift       = LeftShift | RightShift,  /// @brief Either Shift key (convenience combination)

    LeftCtrl    = 1 << 2,       /// @brief Left Control key
    RightCtrl   = 1 << 3,       /// @brief Right Control key
    Ctrl        = LeftCtrl | RightCtrl,    /// @brief Either Control key (convenience combination)

    LeftAlt     = 1 << 4,       /// @brief Left Alt key
    RightAlt    = 1 << 5,       /// @brief Right Alt key
    Alt         = LeftAlt | RightAlt,      /// @brief Either Alt key (convenience combination)

    CapsLock    = 1 << 6,       /// @brief Caps Lock toggled on
};

} // namespace velecs::input

namespace velecs::common {

/// @brief Template specialization to enable bitfield operations for ModifierKey
template<>
struct EnableBitfieldEnum<velecs::input::ModifierKey> : std::true_type {};

} // namespace velecs::common