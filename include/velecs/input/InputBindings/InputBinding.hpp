/// @file    InputBinding.hpp
/// @author  Matthew Green
/// @date    2025-06-25 15:24:42
/// 
/// @section LICENSE
/// 
/// Copyright (c) 2025 Matthew Green - All rights reserved
/// Unauthorized copying of this file, via any medium is strictly prohibited
/// Proprietary and confidential

#pragma once

#include "velecs/input/InputStatus.hpp"
#include "velecs/input/InputBindings/InputBindingContext.hpp"

#include <SDL2/SDL_scancode.h>

namespace velecs::input {

struct InputPollingState;
struct PollingData;

/// @class InputBinding
/// @brief Brief description.
///
/// Rest of description.
class InputBinding {
public:
    using Status = InputStatus;

    // Enums

    // Public Fields

    // Constructors and Destructors

    /// @brief Default constructor.
    InputBinding() = default;

    /// @brief Default deconstructor.
    virtual ~InputBinding() = default;

    // Public Methods

    virtual Status ProcessStatus(const InputPollingState& state, InputBindingContext& outContext) const = 0;

protected:
    // Protected Fields

    // Protected Methods

private:
    // Private Fields

    // Private Methods
};

} // namespace velecs::input
