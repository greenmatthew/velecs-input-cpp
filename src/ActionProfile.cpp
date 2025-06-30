/// @file    ActionProfile.cpp
/// @author  Matthew Green
/// @date    2025-06-07 14:35:25
/// 
/// @section LICENSE
/// 
/// Copyright (c) 2025 Matthew Green - All rights reserved
/// Unauthorized copying of this file, via any medium is strictly prohibited
/// Proprietary and confidential

#include "velecs/input/ActionProfile.hpp"

#include "velecs/input/InputPollingState.hpp"
#include "velecs/input/ActionMap.hpp"
#include "velecs/input/Action.hpp"

#include <stdexcept>

namespace velecs::input {

// Public Fields

// Constructors and Destructors

ActionProfile::ActionProfile(const std::string& name, ConstructorKey)
    : _name(name) {}

ActionProfile::~ActionProfile() = default;

// Public Methods

ActionProfile& ActionProfile::AddMap(const std::string& name, std::function<void(ActionMap&)> configurator)
{
    auto [map, uuid] = _maps.Emplace(name, *this, name, ActionMap::ConstructorKey{});
    configurator(map);
    return *this;
}

void ActionProfile::Process(const InputPollingState& state)
{
    if (!IsEnabled()) return;

    for (auto [uuid, name, map] : _maps)
    {
        if (!map.IsEnabled()) continue;

        map.Process(state);
    }
}

// Protected Fields

// Protected Methods

// Private Fields

// Private Methods

} // namespace velecs::input
