/// @file    ButtonBinding.cpp
/// @author  Matthew Green
/// @date    2025-06-25 17:07:13
/// 
/// @section LICENSE
/// 
/// Copyright (c) 2025 Matthew Green - All rights reserved
/// Unauthorized copying of this file, via any medium is strictly prohibited
/// Proprietary and confidential

#include "velecs/input/InputBindings/ButtonBinding.hpp"

#include "velecs/input/InputStatus.hpp"

#include <stdexcept>

namespace velecs::input {

// Public Fields

// Constructors and Destructors

// Public Methods

void ButtonBinding::Reset()
{
    throw std::runtime_error("Function not implemented.");
}

ButtonBinding::Status ButtonBinding::ProcessStatus(const std::set<SDL_Scancode>& prevDownKeys, const std::set<SDL_Scancode>& currDownKeys)
{
    auto prevIt = prevDownKeys.find(_code);
    bool prevFlag = prevIt != prevDownKeys.end();

    auto currIt = currDownKeys.find(_code);
    bool currFlag = currIt != currDownKeys.end();

    Status status = Status::Idle;
    if (!prevFlag &&  currFlag) status |= Status::Started;
    if (              currFlag) status |= Status::Performed;
    if (prevFlag  && !currFlag) status |= Status::Cancelled;

    return status;
}

// Protected Fields

// Protected Methods

// Private Fields

// Private Methods

} // namespace velecs::input
