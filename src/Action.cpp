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

#include "velecs/input/InputPollingState.hpp"

namespace velecs::input {

// Public Fields

// Constructors and Destructors

// Public Methods

void Action::Process(const InputPollingState& state)
{
    if (!IsEnabled()) return;

    for (auto [uuid, name, binding] : _bindings)
    {
        InputBindingContext context{};
        context.activeKeymods = state.current.keymods;
        Status status = binding.ProcessStatus(state, context);
        if (HasAnyFlag(status, InputStatus::Started)) started.Invoke(context);
        if (HasAnyFlag(status, InputStatus::Performed)) performed.Invoke(context);
        if (HasAnyFlag(status, InputStatus::Cancelled)) cancelled.Invoke(context);
        if (status != Status::Idle) break;
    }
}

// Protected Fields

// Protected Methods

// Private Fields

// Private Methods

} // namespace velecs::input
