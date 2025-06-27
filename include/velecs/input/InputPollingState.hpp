/// @file    InputPollingState.hpp
/// @author  Matthew Green
/// @date    2025-06-27 16:35:34
/// 
/// @section LICENSE
/// 
/// Copyright (c) 2025 Matthew Green - All rights reserved
/// Unauthorized copying of this file, via any medium is strictly prohibited
/// Proprietary and confidential

#pragma once

#include "velecs/input/PollingData.hpp"

namespace velecs::input {

/// @struct InputPollingState
/// @brief Contains current and previous frame polling data for input state transitions
///
/// This structure manages the complete input state across two consecutive frames,
/// enabling detection of input state changes such as key presses, releases, and holds.
/// The previous frame data is used to determine when inputs start or stop.
/// 
/// Key tracking works by:
/// - Adding keys to current on SDL_KEYDOWN events
/// - Removing keys from current on SDL_KEYUP events  
/// - Copying current to previous at frame boundaries
/// - Maintaining persistent key state in current between frames
struct InputPollingState {
public:
    // Enums

    // Public Fields

    /// @brief Polling data from the previous frame
    /// @note Used for detecting input state transitions (started/cancelled events)
    PollingData previous;

    /// @brief Polling data from the current frame
    /// @note Contains the most recent input state, persists held keys between frames
    PollingData current;

    // Constructors and Destructors

    /// @brief Default constructor - creates empty polling state
    InputPollingState() = default;

    /// @brief Copy constructor is deleted to prevent accidental copying
    /// @note InputPollingState is intended to be a singleton-like state holder
    InputPollingState(const InputPollingState&) = delete;

    /// @brief Copy assignment is deleted to prevent accidental copying
    /// @note InputPollingState is intended to be a singleton-like state holder
    InputPollingState& operator=(const InputPollingState&) = delete;

    /// @brief Move constructor
    InputPollingState(InputPollingState&&) = default;

    /// @brief Move assignment operator
    InputPollingState& operator=(InputPollingState&&) = default;

    /// @brief Default destructor
    ~InputPollingState() = default;

    // Public Methods

    /// @brief Shifts to the next frame by copying current data to previous
    /// @note Should be called once per frame after processing all input events
    /// @note Current frame data is preserved to maintain persistent key states
    /// @note Use RegisterKey/UnregisterKey to modify current state based on SDL events
    void ShiftFrame();

    /// @brief Registers a key as currently pressed
    /// @param scancode The SDL scancode to register as pressed
    /// @note Should be called in response to SDL_KEYDOWN events
    /// @see UnregisterKey()
    void RegisterKey(SDL_Scancode scancode);

    /// @brief Unregisters a key as no longer pressed  
    /// @param scancode The SDL scancode to unregister
    /// @note Should be called in response to SDL_KEYUP events
    /// @see RegisterKey()
    void UnregisterKey(SDL_Scancode scancode);

    /// @brief Checks if a scancode was just pressed this frame (not pressed last frame, pressed this frame)
    /// @param scancode The SDL scancode to check
    /// @return true if the key was just pressed, false otherwise
    /// @note Detects the "started" input event - transition from released to pressed
    /// @see IsKeyPerformed(), IsKeyCancelled()
    bool IsKeyStarted(SDL_Scancode scancode) const;

    /// @brief Checks if a scancode is currently held down this frame
    /// @param scancode The SDL scancode to check
    /// @return true if the key is currently pressed, false otherwise
    /// @note Detects the "performed" input event - key is actively held down
    /// @see IsKeyStarted(), IsKeyCancelled()
    bool IsKeyPerformed(SDL_Scancode scancode) const;

    /// @brief Checks if a scancode was just released this frame (pressed last frame, not pressed this frame)
    /// @param scancode The SDL scancode to check
    /// @return true if the key was just released, false otherwise
    /// @note Detects the "cancelled" input event - transition from pressed to released
    /// @see IsKeyStarted(), IsKeyPerformed()
    bool IsKeyCancelled(SDL_Scancode scancode) const;

protected:
    // Protected Fields

    // Protected Methods

private:
    // Private Fields

    // Private Methods
};

} // namespace velecs::input
