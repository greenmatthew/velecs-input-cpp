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
            _currDownKeys.emplace(scancode);
            break;
        }
        case SDL_KEYUP:
        {
            SDL_Scancode scancode = event.key.keysym.scancode;
            _currDownKeys.erase(scancode);
            break;
        }
    }
}

void Input::Update()
{
    _prevDownKeys = _currDownKeys;
}

bool Input::IsStarted(const SDL_Scancode keycode)
{
    auto prevIt = _prevDownKeys.find(keycode);
    bool prevFlag = prevIt != _prevDownKeys.end();

    auto currIt = _currDownKeys.find(keycode);
    bool currFlag = currIt != _currDownKeys.end();

    return !prevFlag && currFlag;
}

bool Input::IsPerformed(const SDL_Scancode keycode)
{
    auto currIt = _currDownKeys.find(keycode);
    bool currFlag = currIt != _currDownKeys.end();

    return currFlag;
}

bool Input::IsCancelled(const SDL_Scancode keycode)
{
    auto prevIt = _prevDownKeys.find(keycode);
    bool prevFlag = prevIt != _prevDownKeys.end();

    auto currIt = _currDownKeys.find(keycode);
    bool currFlag = currIt != _currDownKeys.end();

    return prevFlag && !currFlag;
}

ActionProfile& Input::CreateProfile(const std::string& name)
{
    auto profile = std::make_unique<ActionProfile>(name, ActionProfile::ConstructorKey{});
    ActionProfile& profileRef = *profile;
    auto uuid = _profiles.Add(name, std::move(profile));
    return profileRef;
}

// Protected Fields

// Protected Methods

// Private Fields

std::set<SDL_Scancode> Input::_prevDownKeys;
std::set<SDL_Scancode> Input::_currDownKeys;

ActionProfileRegistry Input::_profiles;

// Private Methods

} // namespace velecs::input
