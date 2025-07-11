/// @file    Input.hpp
/// @author  Matthew Green
/// @date    2025-05-26 14:24:26
/// 
/// @section LICENSE
/// 
/// Copyright (c) 2025 Matthew Green - All rights reserved
/// Unauthorized copying of this file, via any medium is strictly prohibited
/// Proprietary and confidential

#pragma once

#include <velecs/common/NameUuidRegistry.hpp>

#include <SDL3/SDL.h>

#include <memory>
#include <unordered_map>
#include <set>
#include <string>

namespace velecs::input {

struct InputPollingState;

class ActionProfile;
using ActionProfileRegistry = velecs::common::NameUuidRegistry<ActionProfile>;

using Uuid = velecs::common::Uuid;

/// @class Input
/// @brief Brief description.
///
/// Rest of description.
class Input {
public:
    // Enums

    // Public Fields

    // Constructors and Destructors

    /// @brief Default constructor.
    Input() = default;

    /// @brief Default deconstructor.
    ~Input() = default;

    // Public Methods

    /// @brief Processes an SDL event and updates current frame input state
    /// @param event The SDL event to process (keyboard, mouse, controller, window focus, etc.)
    /// @note Called by velecs-engine for each event in the SDL event queue
    static void ProcessEvent(const SDL_Event& event);

    /// @brief Updates input state transitions and triggers action callbacks
    /// @note Call once per frame after all ProcessEvent calls to finalize input state.
    ///       Compares previous and current frame states to determine Started/Performed/Canceled transitions.
    ///       Must be called before accessing action states for the current frame.
    static void Update();

    static bool IsKeyStarted(const SDL_Scancode scancode);
    static bool IsKeyPerformed(const SDL_Scancode scancode);
    static bool IsKeyCancelled(const SDL_Scancode scancode);

    /// @brief Creates a new input profile
    /// @param name Unique name for the profile
    /// @throws std::runtime_error if profile with same name already exists
    static ActionProfile& CreateProfile(const std::string& name);

    /// @brief Attempts to retrieve an existing input profile by UUID
    /// @param uuid UUID of the profile to retrieve
    /// @param outProfile Reference to store the profile if found
    /// @return true if profile was found and outProfile was set, false otherwise
    inline static bool TryGetProfile(const Uuid& uuid, ActionProfile*& outProfile)
    {
        return _profiles.TryGetRef(uuid, outProfile);
    }

    /// @brief Attempts to retrieve an existing input profile by name
    /// @param name Name of the profile to retrieve
    /// @param outProfile Reference to store the profile if found
    /// @return true if profile was found and outProfile was set, false otherwise
    inline static bool TryGetProfile(const std::string& name, ActionProfile*& outProfile)
    {
        return _profiles.TryGetRef(name, outProfile);
    }

    static void CreateDefaultProfile();

protected:
    // Protected Fields

    // Protected Methods

private:
    // Private Fields

    static InputPollingState _state;

    static ActionProfileRegistry _profiles;

    // Private Methods
};

} // namespace velecs::input
