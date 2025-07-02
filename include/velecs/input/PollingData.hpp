/// @file    PollingData.hpp
/// @author  Matthew Green
/// @date    2025-06-27 16:32:48
/// 
/// @section LICENSE
/// 
/// Copyright (c) 2025 Matthew Green - All rights reserved
/// Unauthorized copying of this file, via any medium is strictly prohibited
/// Proprietary and confidential

#pragma once

#include <SDL3/SDL_scancode.h>
#include <SDL3/SDL_keycode.h>

#include <set>

namespace velecs::input {

/// @struct PollingData
/// @brief Contains all raw input polling data for a single frame
///
/// This structure holds the complete state of all input devices at a specific point in time.
/// It includes keyboard state and can be extended to include mouse, controller, and other
/// input device states as needed.
struct PollingData {
public:
    // Enums

    // Public Fields

    /// @brief Set of currently pressed keyboard scancodes
    /// @note Uses SDL_Scancode for hardware-independent key identification
    /// @note Updated via RegisterKey/UnregisterKey in response to SDL_KEYDOWN/SDL_KEYUP events
    /// @note Persists across frames until explicitly unregistered
    std::set<SDL_Scancode> downKeys;

    /// @brief Current modifier key states from SDL
    /// @note Includes both physical modifier keys (Ctrl, Shift, Alt) and toggle states (Caps Lock, Num Lock)
    /// @note Should be updated once per frame using SDL_GetModState() to capture toggle key states
    /// @note Combines KMOD_* flags using bitwise OR operations
    SDL_Keymod keymods{SDL_KMOD_NONE};

    // Future addition examples:
    // Vec2 mousePos{Vec2::ZERO};
    // float mouseWheel{0};
    // bool windowHasFocus{true};

    // Constructors and Destructors

    /// @brief Default constructor - creates empty polling data
    PollingData() = default;

    /// @brief Copy constructor
    PollingData(const PollingData&) = default;

    /// @brief Move constructor
    PollingData(PollingData&&) = default;

    /// @brief Copy assignment operator
    PollingData& operator=(const PollingData&) = default;

    /// @brief Move assignment operator
    PollingData& operator=(PollingData&&) = default;

    /// @brief Default destructor
    ~PollingData() = default;

    // Public Methods

    // @brief Checks if a specific key scancode is currently pressed
    /// @param scancode The SDL scancode to check
    /// @return true if the key is currently pressed down, false otherwise
    /// @note Only checks physical key press state, not modifier combinations
    /// @see IsKeyUp(), RegisterKey(), UnregisterKey()
    inline bool IsKeyDown(const SDL_Scancode scancode) const
    { 
        return downKeys.find(scancode) != downKeys.end();
    }

    /// @brief Checks if a specific key scancode is not currently pressed
    /// @param scancode The SDL scancode to check
    /// @return true if the key is not currently pressed down, false otherwise
    /// @note Convenience method equivalent to !IsKeyDown(scancode)
    /// @see IsKeyDown(), RegisterKey(), UnregisterKey()
    inline bool IsKeyUp(const SDL_Scancode scancode) const
    {
        return downKeys.find(scancode) == downKeys.end(); 
    }

    /// @brief Registers a key as currently pressed
    /// @param scancode The SDL scancode to register as pressed
    /// @note Should be called in response to SDL_KEYDOWN events
    /// @note Key will remain registered until explicitly unregistered
    /// @note Safe to call multiple times for the same key (set semantics)
    /// @see UnregisterKey(), IsKeyDown()
    inline void RegisterKey(const SDL_Scancode scancode)
    {
        // Add key to current frame's pressed keys set
        downKeys.emplace(scancode);
    }

    /// @brief Unregisters a key as no longer pressed
    /// @param scancode The SDL scancode to unregister
    /// @note Should be called in response to SDL_KEYUP events
    /// @note Safe to call even if key was not previously registered (set semantics)
    /// @see RegisterKey(), IsKeyUp()
    inline void UnregisterKey(const SDL_Scancode scancode)
    {
        // Remove key from current frame's pressed keys set
        downKeys.erase(scancode);
    }

    /// @brief Checks if any modifier keys are currently active
    /// @return true if any modifier keys (Ctrl, Shift, Alt, etc.) are active
    /// @note Convenience method to check if keymods is not SDL_KMOD_NONE
    /// @see HasAnyModifier(SDL_Keymod), HasAllModifiers()
    inline bool HasAnyModifier() const
    {
        return keymods != SDL_KMOD_NONE;
    }

    /// @brief Checks if any of the specified modifier keys are currently active
    /// @param mods The SDL_Keymod flags to test for (can be combined with | operator)
    /// @return true if any of the specified modifiers are active, false otherwise
    /// @note Uses bitwise AND to test for modifier presence
    /// @see HasAnyModifier(SDL_Keymod), HasAllModifiers()
    /// @code
    /// if (data.HasAnyModifier(KMOD_CTRL | KMOD_SHIFT)) {
    ///     // Either Ctrl OR Shift (or both) is pressed
    /// }
    /// @endcode
    inline bool HasAnyModifier(const SDL_Keymod mods) const
    {
        return (keymods & mods) != 0;
    }

    /// @brief Checks if all of the specified modifier keys are currently active
    /// @param mods The SDL_Keymod flags that must all be active
    /// @return true if all specified modifiers are active, false otherwise
    /// @note Uses bitwise AND to verify all modifiers are present
    /// @see HasAnyModifier(), HasAnyModifier(SDL_Keymod)
    /// @code
    /// if (data.HasAllModifiers(KMOD_CTRL | KMOD_SHIFT)) {
    ///     // Both Ctrl AND Shift are pressed
    /// }
    /// @endcode
    inline bool HasAllModifiers(const SDL_Keymod mods) const
    {
        return (keymods & mods) == mods;
    }

protected:
    // Protected Fields

    // Protected Methods

private:
    // Private Fields

    // Private Methods
};

} // namespace velecs::input
