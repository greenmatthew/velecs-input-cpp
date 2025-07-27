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
#include "velecs/input/ActionMap.hpp"
#include "velecs/input/Action.hpp"
#include "velecs/input/InputBindings/Common.hpp"

using namespace velecs::common;

#include <iostream>

namespace velecs::input {

// Public Fields

// Constructors and Destructors

// Public Methods

void Input::ProcessEvent(const SDL_Event* const event)
{
    switch (event->type)
    {
        // Keyboard Events
        case SDL_EVENT_KEY_DOWN:
        {
            SDL_KeyboardID keyboardId = event->key.which;
            SDL_Scancode scancode = event->key.scancode;
            _state.current.RegisterKey(scancode);
            // _state.current.RegisterKey(keyboardId, scancode);
            break;
        }
        case SDL_EVENT_KEY_UP:
        {
            
            SDL_KeyboardID keyboardId = event->key.which;
            SDL_Scancode scancode = event->key.scancode;
            _state.current.UnregisterKey(scancode);
            // _state.current.UnregisterKey(keyboardId, scancode);
            break;
        }

        case SDL_EVENT_KEYBOARD_ADDED:
        {
            SDL_KeyboardID keyboardId = event->kdevice.which;
            // _state.current.RegistryKeyboard(keyboardId);
            break;
        }
        case SDL_EVENT_KEYBOARD_REMOVED:
        {
            SDL_KeyboardID keyboardId = event->kdevice.which;
            // _state.current.UnregisterKeyboard(keyboardId);
            break;
        }

        // Gamepad Events
        case SDL_EVENT_GAMEPAD_AXIS_MOTION:
        {
            SDL_JoystickID gamepadId = event->gaxis.which;
            SDL_GamepadAxis axis = (SDL_GamepadAxis)event->gaxis.axis;
            // Normalize to -1.0 to 1.0 (or 0.0 to 1.0 if a trigger or similar)
            float normalizedValue = std::clamp(event->gaxis.value / 32767.0f, -1.0f, 1.0f);
            // _state.current.RegisterGamepadAxis(gamepadId, axis, normalizedValue);
            break;
        }
        case SDL_EVENT_GAMEPAD_BUTTON_DOWN:
        {
            SDL_JoystickID gamepadId = event->gbutton.which;
            SDL_GamepadButton gamepadButton = (SDL_GamepadButton)event->gbutton.button;
            // _state.current.RegisterGamepadButton(gamepadId, gamepadButton);
            break;
        }
        case SDL_EVENT_GAMEPAD_BUTTON_UP:
        {
            SDL_JoystickID gamepadId = event->gbutton.which;
            SDL_GamepadButton gamepadButton = (SDL_GamepadButton)event->gbutton.button;
            // _state.current.UnregisterGamepadButton(gamepadId, gamepadButton);
            break;
        }
        case SDL_EVENT_GAMEPAD_ADDED:
        {
            SDL_JoystickID gamepadId = event->gdevice.which;
            // _state.current.RegisterGamepad(gamepadId);
            break;
        }
        case SDL_EVENT_GAMEPAD_REMOVED:
        {
            SDL_JoystickID gamepadId = event->gdevice.which;
            // _state.current.UnregisterGamepad(gamepadId);
            break;
        }
        case SDL_EVENT_GAMEPAD_REMAPPED:             /**< The gamepad mapping was updated */
        case SDL_EVENT_GAMEPAD_TOUCHPAD_DOWN:        /**< Gamepad touchpad was touched */
        case SDL_EVENT_GAMEPAD_TOUCHPAD_MOTION:      /**< Gamepad touchpad finger was moved */
        case SDL_EVENT_GAMEPAD_TOUCHPAD_UP:          /**< Gamepad touchpad finger was lifted */
        case SDL_EVENT_GAMEPAD_SENSOR_UPDATE:        /**< Gamepad sensor was updated */
        case SDL_EVENT_GAMEPAD_UPDATE_COMPLETE:      /**< Gamepad update is complete */
        case SDL_EVENT_GAMEPAD_STEAM_HANDLE_UPDATED: /**< Gamepad Steam handle has changed */
            break;
    }
}

void Input::Update()
{
    _state.current.keymods = SDL_GetModState();

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

void Input::CreateDefaultProfile()
{
    std::cout << "Creating profile..." << std::endl;
    auto& defaultProfile = Input::CreateProfile("DefaultProfile")
        .AddMap("Player", [](ActionMap& map){
            std::cout << map.GetName() << std::endl;
            map.AddAction("Jump", [](Action& action){
                action.AddBinding<ButtonBinding>("PC Jump", SDL_SCANCODE_SPACE);
                action.started += [](InputBindingContext ctx) { std::cout << "Pressed jump button." << std::endl; };
                action.cancelled += [](InputBindingContext ctx) { std::cout << "Released jump button." << std::endl; };
            })
            .AddAction("Move", [](Action& action){
                std::cout << action.GetName() << std::endl;
                action.AddBinding<Vec2Binding>("WASD Move", SDL_SCANCODE_D, SDL_SCANCODE_A, SDL_SCANCODE_W, SDL_SCANCODE_S, 0.1f)
                    .AddBinding<Vec2Binding>("Arrow Keys Move", SDL_SCANCODE_RIGHT, SDL_SCANCODE_LEFT, SDL_SCANCODE_UP, SDL_SCANCODE_DOWN, 0.1f);

                action.performed += [](InputBindingContext ctx)
                {
                    bool isWalking = (ctx.activeKeymods & SDL_KMOD_LSHIFT) == SDL_KMOD_NONE;
                    if (isWalking)
                        std::cout << "Walked in direction: " << ctx.GetVec2() << std::endl;
                    else
                        std::cout << "Sprinted in direction: " << ctx.GetVec2() << std::endl;
                };
            });
        })
        .AddMap("UI", [](ActionMap& map){
            std::cout << map.GetName() << std::endl;
        })
        ;
    std::cout << "Finished creating profile." << std::endl;
}

// Protected Fields

// Protected Methods

// Private Fields

InputPollingState Input::_state;

ActionProfileRegistry Input::_profiles;

// Private Methods

} // namespace velecs::input
