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

#include <SDL2/SDL_scancode.h>

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
    std::set<SDL_Scancode> downKeys;

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

    inline bool IsKeyDown(SDL_Scancode scancode) const { return downKeys.find(scancode) != downKeys.end(); }
    inline bool IsKeyUp(SDL_Scancode scancode) const { return downKeys.find(scancode) == downKeys.end(); }

protected:
    // Protected Fields

    // Protected Methods

private:
    // Private Fields

    // Private Methods
};

} // namespace velecs::input
