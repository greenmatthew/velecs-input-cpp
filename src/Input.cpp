/// @file    Input.cpp
/// @author  Matthew Green
/// @date    2025-05-26 14:24:52
/// 
/// @section LICENSE
/// 
/// Copyright (c) 2025 Matthew Green - All rights reserved
/// Unauthorized copying of this file, via any medium is strictly prohibited
/// Proprietary and confidential

#include "velecs/input/Input.hpp"

#include "velecs/input/InputPollingState.hpp"
#include "velecs/input/ActionProfile.hpp"

using namespace velecs::common;

#include <iostream>

namespace velecs::input {

// Public Fields

// Constructors and Destructors

// Public Methods

void Input::ProcessEvent(const SDL_Event& event)
{
    switch (event.type)
    {
        case SDL_KEYDOWN:
        {
            SDL_Scancode scancode = event.key.keysym.scancode;
            _state.RegisterKey(scancode);
            break;
        }
        case SDL_KEYUP:
        {
            SDL_Scancode scancode = event.key.keysym.scancode;
            _state.UnregisterKey(scancode);
            break;
        }
    }
}

void Input::Update()
{
    for (auto [name, uuid, profile] : _profiles)
    {
        if (!profile.IsEnabled()) continue;

        profile.Process(_state);
    }

    _state.ShiftFrame();
}

bool Input::IsKeyStarted(const SDL_Scancode scancode)
{
    return _state.IsKeyStarted(scancode);
}

bool Input::IsKeyPerformed(const SDL_Scancode scancode)
{
    return _state.IsKeyPerformed(scancode);
}

bool Input::IsKeyCancelled(const SDL_Scancode scancode)
{
    return _state.IsKeyCancelled(scancode);
}

ActionProfile& Input::CreateProfile(const std::string& name)
{
    auto [profile, uuid] = _profiles.Emplace(name, name, ActionProfile::ConstructorKey{});
    return profile;
}

// Protected Fields

// Protected Methods

// Private Fields

InputPollingState Input::_state;

ActionProfileRegistry Input::_profiles;

// Private Methods

} // namespace velecs::input
