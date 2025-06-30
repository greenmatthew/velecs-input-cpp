/// @file    Vec2Binding.cpp
/// @author  Matthew Green
/// @date    2025-06-30 11:47:06
/// 
/// @section LICENSE
/// 
/// Copyright (c) 2025 Matthew Green - All rights reserved
/// Unauthorized copying of this file, via any medium is strictly prohibited
/// Proprietary and confidential

#include "velecs/input/InputBindings/Vec2Binding.hpp"

#include "velecs/input/InputPollingState.hpp"

using namespace velecs::math;

namespace velecs::input {

// Public Fields

// Constructors and Destructors

// Public Methods

Vec2Binding::Status Vec2Binding::ProcessStatus(const InputPollingState& state, InputBindingContext& outContext) const
{
    const Vec2 prev = CalculateVec2(state.previous);
    const Vec2 curr = CalculateVec2(state.current);

    const bool wasPastDeadzone = prev.LInfNorm() > _deadzone;
    const bool isPastDeadzone = curr.LInfNorm() > _deadzone;

    Status status = Status::Idle;
    if (!wasPastDeadzone  &&  isPastDeadzone) status |= Status::Started;
    if (                      isPastDeadzone) status |= Status::Performed;
    if ( wasPastDeadzone  && !isPastDeadzone) status |= Status::Cancelled;

    outContext = InputBindingContext{};
    outContext.valueType = InputBindingContext::ValueType::Vec2;
    outContext.vec2Val = curr;
    outContext.activeScancodes = isPastDeadzone ? (SDL_Scancode)(
        (state.current.IsKeyDown(_posXScancode) ?  _posXScancode : SDL_SCANCODE_UNKNOWN)
        | (state.current.IsKeyDown(_negXScancode) ? _negXScancode : SDL_SCANCODE_UNKNOWN)
        | (state.current.IsKeyDown(_posYScancode) ? _posYScancode : SDL_SCANCODE_UNKNOWN)
        | (state.current.IsKeyDown(_negYScancode) ? _negYScancode : SDL_SCANCODE_UNKNOWN))
        : SDL_SCANCODE_UNKNOWN;

    return status;
}

// Protected Fields

// Protected Methods

// Private Fields

// Private Methods

Vec2 Vec2Binding::CalculateVec2(const PollingData& data) const
{
    return Vec2{
          (data.IsKeyDown(_posXScancode) ?  1.0f : 0.0f)
        + (data.IsKeyDown(_negXScancode) ? -1.0f : 0.0f),

          (data.IsKeyDown(_posYScancode) ?  1.0f : 0.0f)
        + (data.IsKeyDown(_negYScancode) ? -1.0f : 0.0f)
    };
}

} // namespace velecs::input
