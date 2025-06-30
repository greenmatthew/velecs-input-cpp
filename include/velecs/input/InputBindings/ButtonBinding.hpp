/// @file    ButtonBinding.hpp
/// @author  Matthew Green
/// @date    2025-06-25 16:27:32
/// 
/// @section LICENSE
/// 
/// Copyright (c) 2025 Matthew Green - All rights reserved
/// Unauthorized copying of this file, via any medium is strictly prohibited
/// Proprietary and confidential

#pragma once

#include "velecs/input/InputBindings/InputBinding.hpp"

namespace velecs::input {

/// @class ButtonBinding
/// @brief Input binding for single button/key press detection
///
/// Monitors a specific SDL scancode and reports Started/Performed/Cancelled states
/// based on key press and release events. Essential building block for button-based
/// input actions like jump, fire, interact, etc.
class ButtonBinding : public InputBinding {
public:
    // Enums

    // Public Fields

    // Constructors and Destructors

    /// @brief Constructs a ButtonBinding for the specified scancode
    /// @param scancode SDL scancode to monitor for input events
    inline explicit ButtonBinding(SDL_Scancode scancode) : _scancode(scancode) {}

    /// @brief Default constructor is deleted - ButtonBinding requires params
    ButtonBinding() = delete;

    /// @brief Virtual destructor
    ~ButtonBinding() override = default;

    // Public Methods

    Status ProcessStatus(const InputPollingState& state, InputBindingContext& outContext) const override;

    /// @brief Gets the SDL scancode this binding monitors
    /// @return The scancode this binding is configured for
    SDL_Scancode GetScancode() const { return _scancode; }

protected:
    // Protected Fields

    // Protected Methods

private:
    // Private Fields

    /// @brief The SDL scancode this binding monitors for input
    const SDL_Scancode _scancode;

    // Private Methods
};

} // namespace velecs::input
