/// @file    Action.hpp
/// @author  Matthew Green
/// @date    2025-05-26 14:59:10
/// 
/// @section LICENSE
/// 
/// Copyright (c) 2025 Matthew Green - All rights reserved
/// Unauthorized copying of this file, via any medium is strictly prohibited
/// Proprietary and confidential

#pragma once

#include "velecs/input/InputBindings/InputBinding.hpp"

#include <velecs/common/Event.hpp>
#include <velecs/common/NameUuidRegistry.hpp>

#include <string>

namespace velecs::input {

class ActionMap;

using InputBindingRegistry = velecs::common::NameUuidRegistry<InputBinding>;
using Uuid = velecs::common::Uuid;

/// @class Action
/// @brief Represents an individual input action that can be triggered by user input.
///
/// Actions are the fundamental building blocks of the input system, representing
/// discrete user interactions like "Jump", "Fire", or "Move". Each Action belongs
/// to an ActionMap and can be individually enabled or disabled. Actions emit events
/// when they are started, performed, or cancelled based on input processing.
///
/// @code
/// Action jumpAction(actionMap, "Jump", Action::ConstructorKey{});
/// jumpAction.started.Subscribe([](){ /* Handle jump start */ });
/// jumpAction.performed.Subscribe([](){ /* Handle jump performed */ });
/// jumpAction.Disable(); // Temporarily disable this action
/// @endcode
class Action {
public:
    using Status = InputStatus;

    // Enums

    // Public Fields

    /// @brief Event triggered when the action starts (e.g., button press begins)
    velecs::common::Event<InputBindingContext> started;
    
    /// @brief Event triggered when the action is performed (e.g., button press completes)
    velecs::common::Event<InputBindingContext> performed;
    
    /// @brief Event triggered when the action is cancelled (e.g., button release before completion)
    velecs::common::Event<InputBindingContext> cancelled;

    // Constructors and Destructors

    /// @brief Constructor access key to restrict creation to authorized classes
    class ConstructorKey {
        friend class ActionMap;
        ConstructorKey() = default;
    };

    /// @brief Constructs an Action with the given ActionMap and name
    /// @param map Reference to the parent ActionMap that owns this action
    /// @param name Unique name for this action within its map
    /// @param key Constructor access key (restricts creation to ActionMap class)
    inline Action(const ActionMap& map, const std::string& name, ConstructorKey)
        : _map(map), _name(name) {}

    /// @brief Default constructor
    Action() = default;

    /// @brief Default destructor
    ~Action() = default;

    // Public Methods

    /// @brief Checks if this Action is currently enabled for input processing
    /// @return true if the action is enabled, false otherwise
    /// @note Both the action and its parent ActionMap must be enabled for processing
    /// @see Enable(), Disable()
    inline bool IsEnabled() const { return _enabled; }

    /// @brief Enables this Action for input processing
    /// @note The parent ActionMap must also be enabled for this action to be processed
    /// @see Disable(), IsEnabled()
    inline void Enable() { _enabled = true; }
    
    /// @brief Disables this Action, preventing it from being processed during input handling
    /// @note The action will remain disabled even if the parent ActionMap is disabled and re-enabled
    /// @see Enable(), IsEnabled()
    inline void Disable() { _enabled = false; }

    /// @brief Gets the parent ActionMap that owns this Action
    /// @return Const reference to the parent ActionMap
    /// @note The returned reference remains valid for the lifetime of this Action
    inline const ActionMap& GetMap() const { return _map; }

    /// @brief Gets the name of this Action
    /// @return Const reference to the action name
    inline const std::string& GetName() const { return _name; }

    template<typename T, typename... Args>
    void AddBinding(const std::string& name, Args&&... args)
    {
        auto [binding, uuid] = _bindings.EmplaceAs<T>(name, std::forward<Args>(args)...);
    }

    void Process(const InputPollingState& state);

protected:
    // Protected Fields

    // Protected Methods

private:
    // Private Fields

    /// @brief Whether this action is currently enabled for input processing
    bool _enabled{true};
    
    /// @brief Reference to the parent ActionMap that owns this action
    const ActionMap& _map;
    
    /// @brief The unique name of this action within its map
    const std::string _name;

    InputBindingRegistry _bindings;

    // Private Methods
};

} // namespace velecs::input