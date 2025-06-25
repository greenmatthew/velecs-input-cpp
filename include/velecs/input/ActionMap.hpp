/// @file    ActionMap.hpp
/// @author  Matthew Green
/// @date    2025-05-26 14:59:01
/// 
/// @section LICENSE
/// 
/// Copyright (c) 2025 Matthew Green - All rights reserved
/// Unauthorized copying of this file, via any medium is strictly prohibited
/// Proprietary and confidential

#pragma once

#include "velecs/input/Action.hpp"

#include <velecs/common/NameUuidRegistry.hpp>

#include <string>
#include <memory>
#include <unordered_set>

namespace velecs::input {

class ActionProfile;

using ActionRegistry = velecs::common::NameUuidRegistry<std::unique_ptr<Action>>;
using Uuid = velecs::common::Uuid;

/// @class ActionMap
/// @brief A named collection of input actions that can be enabled or disabled as a group.
///
/// ActionMaps organize related input actions together within an ActionProfile and provide
/// both map-level and action-level enable/disable control. When a map is disabled, all
/// its actions are ignored during input processing regardless of their individual states.
/// When re-enabled, actions retain their previous enabled/disabled states.
///
/// @code
/// ActionMap playerMap(profile, "Player", ActionMap::ConstructorKey{});
/// playerMap.AddAction("Move", [](Action& action) {
///     // Configure move action
/// });
/// playerMap.Disable(); // Disables map processing, actions unchanged
/// playerMap.DisableAllActions(); // Disables each action individually
/// @endcode
class ActionMap {
public:
    // Enums

    // Public Fields

    // Constructors and Destructors

    /// @brief Constructor access key to restrict creation to authorized classes
    class ConstructorKey {
        friend class ActionProfile;
        ConstructorKey() = default;
    };

    /// @brief Constructs an ActionMap with the given profile, name, and access key
    /// @param profile Reference to the parent ActionProfile that owns this map
    /// @param name Unique name for this action map within its profile
    /// @param key Constructor access key (restricts creation to ActionProfile class)
    inline ActionMap(const ActionProfile& profile, const std::string& name, ConstructorKey)
        : _profile(profile), _name(name) {}

    /// @brief Default destructor
    ~ActionMap() = default;

    // Public Methods

    /// @brief Checks if this ActionMap is currently enabled for input processing
    /// @return true if the map is enabled, false otherwise
    /// @note This only indicates map-level enablement, not individual Action states
    /// @see Enable(), Disable()
    inline bool IsEnabled() const { return _enabled; }

    /// @brief Enables this map, making all its enabled Actions active for input processing
    /// @note Does not modify the Actions themselves, only affects processing
    /// @note Not to be confused with `EnableAllActions()` which modifies individual Action states
    /// @see IsEnabled(), DisableAllActions(), EnableAllActions()
    inline void Enable() { _enabled = true; }

    /// @brief Disables this map, causing all its Actions to be ignored during input processing
    /// @note Does not modify the Actions themselves, only affects processing
    /// @note When re-enabled, Actions retain their previous enabled/disabled states
    /// @note Not to be confused with `DisableAllActions()` which modifies individual Action states  
    /// @see IsEnabled(), EnableAllActions(), DisableAllActions()
    inline void Disable() { _enabled = false; }

    /// @brief Gets the parent ActionProfile that owns this ActionMap
    /// @return Const reference to the parent ActionProfile
    /// @note The returned reference remains valid for the lifetime of this ActionMap
    inline const ActionProfile& GetProfile() const { return _profile; }

    /// @brief Gets the name of this action map
    /// @return Const reference to the map name
    inline const std::string& GetName() const { return _name; }

    /// @brief Adds a new action to this map and configures it
    /// @param name Unique name for the action within this map
    /// @param configurator Function to configure the newly created action
    /// @throws std::runtime_error if action with same name already exists in this map
    void AddAction(const std::string& name, std::function<void(Action&)> configurator);

    /// @brief Attempts to retrieve an action by UUID
    /// @param uuid UUID of the action to retrieve
    /// @param outAction Reference to store pointer to the action if found
    /// @return true if action was found, false otherwise
    inline bool TryGetAction(const Uuid& uuid, Action*& outAction) const { return _actions.TryGetRef(uuid, outAction); }

    /// @brief Attempts to retrieve an action by name
    /// @param name Name of the action to retrieve
    /// @param outAction Reference to store pointer to the action if found
    /// @return true if action was found, false otherwise
    bool TryGetAction(const std::string& name, Action*& outAction) const { return _actions.TryGetRef(name, outAction); }

    /// @brief Enables all Actions within this map individually
    /// @note This modifies each Action's enabled state directly
    /// @note Map must also be enabled for Actions to be processed
    /// @note Not to be confused with `Enable()` which only affects map-level processing
    /// @see Enable(), DisableAllActions()
    void EnableAllActions();

    /// @brief Disables all Actions within this map individually  
    /// @note This modifies each Action's enabled state directly
    /// @note Actions remain disabled even if map is disabled then re-enabled
    /// @note Not to be confused with `Disable()` which only affects map-level processing
    /// @see Disable(), EnableAllActions()
    void DisableAllActions();

protected:
    // Protected Fields

    // Protected Methods

private:
    // Private Fields

    /// @brief Whether this map is currently enabled for input processing
    bool _enabled{true};

    /// @brief Reference to the parent ActionProfile that owns this map
    const ActionProfile& _profile;
    
    /// @brief The unique name of this action map within its profile
    const std::string _name;

    /// @brief Registry of actions belonging to this map
    ActionRegistry _actions;

    // Private Methods
};

} // namespace velecs::input
