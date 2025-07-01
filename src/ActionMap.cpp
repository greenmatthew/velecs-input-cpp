/// @file    ActionMap.cpp
/// @author  Matthew Green
/// @date    2025-06-07 15:31:57
/// 
/// @section LICENSE
/// 
/// Copyright (c) 2025 Matthew Green - All rights reserved
/// Unauthorized copying of this file, via any medium is strictly prohibited
/// Proprietary and confidential

#include "velecs/input/ActionMap.hpp"

namespace velecs::input {

// Public Fields

// Constructors and Destructors

// Public Methods

ActionMap& ActionMap::AddAction(const std::string& name, std::function<void(Action&)> configurator)
{
    auto [action, uuid] = _actions.Emplace(name, *this, name, Action::ConstructorKey{});
    configurator(action);
    return *this;
}

void ActionMap::EnableAllActions()
{
    for (auto [uuid, name, action] : _actions)
    {
        action.Enable();
    }
}

void ActionMap::DisableAllActions()
{
    for (auto [uuid, name, action] : _actions)
    {
        action.Disable();
    }
}

void ActionMap::Process(const InputPollingState& state)
{
    if (!IsEnabled()) return;

    for (auto [uuid, name, action] : _actions)
    {
        if (!action.IsEnabled()) continue;

        action.Process(state);
    }
}


// Protected Fields

// Protected Methods

// Private Fields

// Private Methods

} // namespace velecs::input
