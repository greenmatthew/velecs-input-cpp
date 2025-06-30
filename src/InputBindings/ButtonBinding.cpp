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

#include "velecs/input/InputPollingState.hpp"

#include <stdexcept>

namespace velecs::input {

// Public Fields

// Constructors and Destructors

// Public Methods

void ButtonBinding::Reset()
{
    throw std::runtime_error("Function not implemented.");
}

ButtonBinding::Status ButtonBinding::ProcessStatus(const InputPollingState& state) const
{
    const bool wasPressed = state.previous.downKeys.find(_code) != state.previous.downKeys.end();
    const bool isPressed = state.current.downKeys.find(_code) != state.current.downKeys.end();

    Status status = Status::Idle;
    if (!wasPressed  &&  isPressed) status |= Status::Started;
    if (                 isPressed) status |= Status::Performed;
    if ( wasPressed  && !isPressed) status |= Status::Cancelled;

    return status;
}

// Protected Fields

// Protected Methods

// Private Fields

// Private Methods

} // namespace velecs::input
