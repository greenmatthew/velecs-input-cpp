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

#include <SDL2/SDL.h>

#include <set>

namespace velecs::input {

/// @class ButtonBinding
/// @brief Brief description.
///
/// Rest of description.
class ButtonBinding : public InputBinding {
public:
    // Enums

    // Public Fields

    // Constructors and Destructors

    inline ButtonBinding(SDL_Scancode code) : _code(code) {}

    /// @brief Default constructor.
    ButtonBinding() = default;

    /// @brief Default deconstructor.
    ~ButtonBinding() override = default;

    // Public Methods

    void Reset() override;

    Status ProcessStatus(const InputPollingState& state) const override;

protected:
    // Protected Fields

    // Protected Methods

private:
    // Private Fields

    const SDL_Scancode _code;

    // Private Methods
};

} // namespace velecs::input
