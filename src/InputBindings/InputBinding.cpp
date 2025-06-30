/// @file    InputBinding.cpp
/// @author  Matthew Green
/// @date    2025-06-30 13:37:33
/// 
/// @section LICENSE
/// 
/// Copyright (c) 2025 Matthew Green - All rights reserved
/// Unauthorized copying of this file, via any medium is strictly prohibited
/// Proprietary and confidential

#include "velecs/input/InputBindings/InputBinding.hpp"

#include "velecs/input/PollingData.hpp"

namespace velecs::input {

// Public Fields

// Constructors and Destructors

// Public Methods

// ModifierKey InputBinding::CheckActiveModifiers(const PollingData& data) const
// {
//     ModifierKey modifiers = ModifierKey::None;

//     ModifierKey test = ModifierKey::None | ModifierKey::CapsLock;

//     if (data.IsKeyDown(SDL_SCANCODE_LCTRL)) modifiers |= ModifierKey::Ctrl | ModifierKey::LeftCtrl;
//     if (data.IsKeyDown(SDL_SCANCODE_RCTRL)) modifiers |= ModifierKey::Ctrl | ModifierKey::RightCtrl;

//     if (data.IsKeyDown(SDL_SCANCODE_LSHIFT)) modifiers |= ModifierKey::Shift | ModifierKey::LeftShift;
//     if (data.IsKeyDown(SDL_SCANCODE_RSHIFT)) modifiers |= ModifierKey::Shift | ModifierKey::RightShift;
    
//     if (data.IsKeyDown(SDL_SCANCODE_LALT)) modifiers |= ModifierKey::Alt | ModifierKey::LeftAlt;
//     if (data.IsKeyDown(SDL_SCANCODE_RALT)) modifiers |= ModifierKey::Alt | ModifierKey::RightAlt;

//     // determine if caps lock is enabled (NOT DOWN there is a distinct difference)

//     return modifiers;
// }

// Protected Fields

// Protected Methods

// Private Fields

// Private Methods

} // namespace velecs::input
