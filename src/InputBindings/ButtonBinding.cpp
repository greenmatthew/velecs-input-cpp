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

ButtonBinding::Status ButtonBinding::ProcessStatus(const InputPollingState& state, InputBindingContext& outContext) const
{
    const bool wasPressed = state.previous.IsKeyDown(_scancode);
    const bool isPressed = state.current.IsKeyDown(_scancode);
    
    Status status = Status::Idle;
    if (!wasPressed  &&  isPressed) status |= Status::Started;
    if (                 isPressed) status |= Status::Performed;
    if ( wasPressed  && !isPressed) status |= Status::Cancelled;

    outContext = InputBindingContext{};
    outContext.valueType = InputBindingContext::ValueType::Bool;
    outContext.boolVal = isPressed;
    outContext.activeScancodes = isPressed ? _scancode : SDL_SCANCODE_UNKNOWN;

    return status;
}

// Protected Fields

// Protected Methods

// Private Fields

// Private Methods

} // namespace velecs::input
