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
    previous = std::move(current);
}

void InputPollingState::RegisterKey(SDL_Scancode scancode)
{
    // Add key to current frame's pressed keys set
    current.downKeys.emplace(scancode);
}

void InputPollingState::UnregisterKey(SDL_Scancode scancode)
{
    // Remove key from current frame's pressed keys set
    current.downKeys.erase(scancode);
}

bool InputPollingState::IsKeyStarted(SDL_Scancode scancode) const
{
    // Key just started: wasn't pressed last frame, is pressed this frame
    bool wasPressed = previous.downKeys.find(scancode) != previous.downKeys.end();
    bool isPressed = current.downKeys.find(scancode) != current.downKeys.end();
    return !wasPressed && isPressed;
}

bool InputPollingState::IsKeyPerformed(SDL_Scancode scancode) const
{
    // Key is being performed: currently pressed this frame
    bool isPressed = current.downKeys.find(scancode) != current.downKeys.end();
    return isPressed;
}

bool InputPollingState::IsKeyCancelled(SDL_Scancode scancode) const
{
    // Key was cancelled: was pressed last frame, not pressed this frame
    bool wasPressed = previous.downKeys.find(scancode) != previous.downKeys.end();
    bool isPressed = current.downKeys.find(scancode) != current.downKeys.end();
    return wasPressed && !isPressed;
}

// Protected Fields

// Protected Methods

// Private Fields

// Private Methods

} // namespace velecs::input
