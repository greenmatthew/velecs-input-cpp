/// @file    InputStatus.cpp
/// @author  Matthew Green
/// @date    2025-06-25 16:57:04
/// 
/// @section LICENSE
/// 
/// Copyright (c) 2025 Matthew Green - All rights reserved
/// Unauthorized copying of this file, via any medium is strictly prohibited
/// Proprietary and confidential

#include "velecs/input/InputStatus.hpp"

namespace velecs::input {

InputStatus operator|(const InputStatus a, const InputStatus b) {
    return static_cast<InputStatus>(
        static_cast<uint32_t>(a) | static_cast<uint32_t>(b)
    );
}

InputStatus& operator|=(InputStatus& a, const InputStatus b) {
    a = a | b;
    return a;
}

InputStatus operator&(const InputStatus a, const InputStatus b) {
    return static_cast<InputStatus>(
        static_cast<uint32_t>(a) & static_cast<uint32_t>(b)
    );
}

InputStatus& operator&=(InputStatus& a, const InputStatus b) {
    a = a & b;
    return a;
}

} // namespace velecs::input