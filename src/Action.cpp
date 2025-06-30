/// @file    Action.cpp
/// @author  Matthew Green
/// @date    2025-06-25 15:36:39
/// 
/// @section LICENSE
/// 
/// Copyright (c) 2025 Matthew Green - All rights reserved
/// Unauthorized copying of this file, via any medium is strictly prohibited
/// Proprietary and confidential

#include "velecs/input/Action.hpp"

namespace velecs::input {

// Public Fields

// Constructors and Destructors

// Public Methods

void Action::Process(const InputPollingState& state)
{
    if (!IsEnabled()) return;

    Status status = Status::Idle;
    for (auto [uuid, name, binding] : _bindings)
    {
        status |= binding.ProcessStatus(state);
    }

    if (HasAnyFlag(status, InputStatus::Started)) started.Invoke();
    if (HasAnyFlag(status, InputStatus::Performed)) performed.Invoke();
    if (HasAnyFlag(status, InputStatus::Cancelled)) cancelled.Invoke();
}

// Protected Fields

// Protected Methods

// Private Fields

// Private Methods

} // namespace velecs::input
