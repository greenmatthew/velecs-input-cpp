/// @file    Vec2Binding.hpp
/// @author  Matthew Green
/// @date    2025-06-30 11:35:54
/// 
/// @section LICENSE
/// 
/// Copyright (c) 2025 Matthew Green - All rights reserved
/// Unauthorized copying of this file, via any medium is strictly prohibited
/// Proprietary and confidential

#pragma once

#include "velecs/input/InputBindings/InputBinding.hpp"

#include <velecs/math/Vec2.hpp>

namespace velecs::input {

/// @class Vec2Binding
/// @brief Brief description.
///
/// Rest of description.
class Vec2Binding : public InputBinding {
public:
    // Enums

    // Public Fields

    // Constructors and Destructors

    inline explicit Vec2Binding(SDL_Scancode posX, SDL_Scancode negX, SDL_Scancode posY, SDL_Scancode negY, float deadzone)
        : _posXScancode(posX), _negXScancode(negX), _posYScancode(posY), _negYScancode(negY), _deadzone(deadzone) {}

    /// @brief Default constructor is deleted - ButtonBinding requires params
    Vec2Binding() = delete;

    /// @brief Virtual destructor
    ~Vec2Binding() override = default;

    // Public Methods

    Status ProcessStatus(const InputPollingState& state, InputBindingContext& outContext) const override;

protected:
    // Protected Fields

    // Protected Methods

private:
    // Private Fields

    SDL_Scancode _posXScancode;
    SDL_Scancode _negXScancode;
    SDL_Scancode _posYScancode;
    SDL_Scancode _negYScancode;
    float _deadzone;

    // Private Methods

    velecs::math::Vec2 CalculateVec2(const PollingData& data) const;
};

} // namespace velecs::input
