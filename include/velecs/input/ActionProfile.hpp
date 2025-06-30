/// @file    ActionProfile.hpp
/// @author  Matthew Green
/// @date    2025-05-26 14:58:39
/// 
/// @section LICENSE
/// 
/// Copyright (c) 2025 Matthew Green - All rights reserved
/// Unauthorized copying of this file, via any medium is strictly prohibited
/// Proprietary and confidential

#pragma once

#include <velecs/common/NameUuidRegistry.hpp>

#include <string>
#include <unordered_map>
#include <memory>
#include <functional>

namespace velecs::input {

struct InputPollingState;
class ActionMap;
class Action;

using ActionMapRegistry = velecs::common::NameUuidRegistry<ActionMap>;
using Uuid = velecs::common::Uuid;

/// @class ActionProfile
/// @brief A named collection of action maps that can be enabled or disabled as a group.
///
/// ActionProfiles allow organizing related input actions together and controlling their 
/// active state collectively. When disabled, all ActionMaps within this profile are 
/// ignored during input processing without modifying the Actions themselves.
class ActionProfile {
public:
    // Enums

    // Public Fields

    // Constructors and Destructors

    /// @brief Constructor access key to restrict creation to authorized classes
    class ConstructorKey {
        friend class Input;
        ConstructorKey() = default;
    };

    /// @brief Constructs an ActionProfile with the given name
    /// @param name Unique name for this profile
    /// @param key Constructor access key (restricts creation to Input class)
    ActionProfile(const std::string& name, ConstructorKey);

    /// @brief Copy constructor is deleted to prevent accidental copying
    /// @note ActionProfiles contain unique_ptr registries that cannot be safely copied.
    ///       Use references to pass ActionProfiles around instead of copying.
    ActionProfile(const ActionProfile&) = delete;
    
    /// @brief Copy assignment is deleted to prevent accidental copying
    /// @note ActionProfiles contain unique_ptr registries that cannot be safely copied.
    ///       Use references to pass ActionProfiles around instead of copying.
    ActionProfile& operator=(const ActionProfile&) = delete;
    
    /// @brief Move constructor is deleted to enforce reference-only usage
    /// @note ActionProfiles are intended to be managed by the Input system and accessed
    ///       via references. Moving could invalidate references held by other systems.
    ActionProfile(ActionProfile&&) = delete;
    
    /// @brief Move assignment is deleted to enforce reference-only usage
    /// @note ActionProfiles are intended to be managed by the Input system and accessed
    ///       via references. Moving could invalidate references held by other systems.
    ActionProfile& operator=(ActionProfile&&) = delete;

    /// @brief Destructor
    /// @note Defined in implementation file to allow forward declaration of ActionMap.
    ///       This enables the use of incomplete types with std::unique_ptr in the registry.
    ~ActionProfile();

    // Public Methods

    /// @brief Checks if this ActionProfile is currently enabled for input processing
    /// @return true if the profile is enabled, false otherwise
    /// @note Both the profile and its ActionMaps must be enabled for actions to be processed
    /// @see Enable(), Disable()
    inline bool IsEnabled() const { return _enabled; }

    /// @brief Enables this profile, making all its enabled ActionMaps active for input processing
    /// @note Does not modify the ActionMaps or Actions themselves, only affects processing
    /// @see IsEnabled(), Disable()
    inline void Enable() { _enabled = true; }
    
    /// @brief Disables this profile, causing all its ActionMaps to be ignored during input processing
    /// @note Does not modify the ActionMaps or Actions themselves, only affects processing
    /// @see IsEnabled(), Enable()
    inline void Disable() { _enabled = false; }

    /// @brief Gets the name of this action profile
    /// @return Const reference to the profile name
    inline const std::string& GetName() const { return _name; }

    /// @brief Adds a new action map to this profile and configures it
    /// @param name Unique name for the action map within this profile
    /// @param configurator Function to configure the newly created map
    /// @return Reference to this ActionProfile for method chaining
    /// @throws std::runtime_error if map with same name already exists in this profile
    ActionProfile& AddMap(const std::string& name, std::function<void(ActionMap&)> configurator);

    /// @brief Attempts to retrieve an action map by UUID
    /// @param uuid UUID of the action map to retrieve
    /// @param outMap Reference to store pointer to the action map if found
    /// @return true if action map was found, false otherwise
    inline bool TryGetMap(const Uuid& uuid, ActionMap*& outMap) const { return _maps.TryGetRef(uuid, outMap); }

    /// @brief Attempts to retrieve an action map by name
    /// @param name Name of the action map to retrieve
    /// @param outMap Reference to store pointer to the action map if found
    /// @return true if action map was found, false otherwise
    inline bool TryGetMap(const std::string& name, ActionMap*& outMap) const { return _maps.TryGetRef(name, outMap); }

    void Process(const InputPollingState& state);

protected:
    // Protected Fields

    // Protected Methods

private:
    // Private Fields

    /// @brief Whether this profile is currently enabled for input processing
    bool _enabled{true};
    
    /// @brief The unique name of this action profile
    const std::string _name;

    /// @brief Registry of action maps belonging to this profile
    ActionMapRegistry _maps;

    // Private Methods
};

} // namespace velecs::input
