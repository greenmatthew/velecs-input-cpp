/// @file    InputPollingState.cpp
/// @author  Matthew Green
/// @date    2025-06-27 16:51:15
/// 
/// @section LICENSE
/// 
/// Copyright (c) 2025 Matthew Green - All rights reserved
/// Unauthorized copying of this file, via any medium is strictly prohibited
/// Proprietary and confidential

#include "velecs/input/InputPollingState.hpp"

namespace velecs::input {

// Public Fields

// Constructors and Destructors

// Public Methods

void InputPollingState::ShiftFrame()
{
    // Copy current state to previous (preserves current for persistent key tracking)
    previous = current;
}

bool InputPollingState::IsKeyStarted(const SDL_Scancode scancode) const
{
    // Key just started: wasn't pressed last frame, is pressed this frame
    bool wasPressed = previous.IsKeyDown(scancode);
    bool isPressed = current.IsKeyDown(scancode);
    return !wasPressed && isPressed;
}

bool InputPollingState::IsKeyPerformed(const SDL_Scancode scancode) const
{
    // Key is being performed: currently pressed this frame
    bool isPressed = current.IsKeyDown(scancode);
    return isPressed;
}

bool InputPollingState::IsKeyCancelled(const SDL_Scancode scancode) const
{
    // Key was cancelled: was pressed last frame, not pressed this frame
    bool wasPressed = previous.IsKeyDown(scancode);
    bool isPressed = current.IsKeyDown(scancode);
    return wasPressed && !isPressed;
}

// Protected Fields

// Protected Methods

// Private Fields

// Private Methods

} // namespace velecs::input
