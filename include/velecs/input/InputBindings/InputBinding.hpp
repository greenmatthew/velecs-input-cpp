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

namespace velecs::input {

struct InputPollingState;

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

    virtual void Reset() = 0;

    virtual Status ProcessStatus(const InputPollingState& state) const = 0;

protected:
    // Protected Fields

    // Protected Methods

private:
    // Private Fields

    // Private Methods
};

} // namespace velecs::input
