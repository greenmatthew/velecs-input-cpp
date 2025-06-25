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

#include <cstdint>

namespace velecs::input {

/// @enum ModifierKey
/// @brief Brief description.
///
/// Rest of description.
enum class ModifierKey {
    None        = 0,
    LeftShift   = 1 << 0,
    RightShift  = 1 << 1,
    Shift = LeftShift | RightShift,

    LeftCtrl    = 1 << 2,
    RightCtrl   = 1 << 3,
    Ctrl  = LeftCtrl | RightCtrl,

    LeftAlt     = 1 << 4,
    RightAlt    = 1 << 5,
    Alt   = LeftAlt | RightAlt,

    CapsLock    = 1 << 6,
};

inline ModifierKey operator|(ModifierKey a, ModifierKey b) {
    return static_cast<ModifierKey>(static_cast<uint32_t>(a) | static_cast<uint32_t>(b));
}

inline bool operator&(ModifierKey a, ModifierKey b) {
    return static_cast<uint32_t>(a) & static_cast<uint32_t>(b);
}

} // namespace velecs::input
