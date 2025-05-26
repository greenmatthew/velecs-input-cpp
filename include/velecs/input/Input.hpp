/// @file    Input.cpp
/// @author  Matthew Green
/// @date    2025-05-26 14:24:26
/// 
/// @section LICENSE
/// 
/// Copyright (c) 2025 Matthew Green - All rights reserved
/// Unauthorized copying of this file, via any medium is strictly prohibited
/// Proprietary and confidential

#pragma once

#include <SDL2/SDL.h>

namespace velecs::input {

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

protected:
    // Protected Fields

    // Protected Methods

private:
    // Private Fields

    // Private Methods
};

} // namespace velecs::input
