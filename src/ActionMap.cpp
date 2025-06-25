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

void ActionMap::AddAction(const std::string& name, std::function<void(Action&)> configurator)
{
    auto action = std::make_unique<Action>(*this, name, Action::ConstructorKey{});
    Action* actionPtr = action.get(); // Get raw pointer before moving
    auto uuid = _actions.Add(name, std::move(action)); // Move into registry
    configurator(*actionPtr); // Use raw pointer (safe because registry owns it)
}

// Protected Fields

// Protected Methods

// Private Fields

// Private Methods

} // namespace velecs::input
