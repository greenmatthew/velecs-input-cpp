/// @file    InputBindingContext.hpp
/// @author  Matthew Green
/// @date    2025-06-30 12:11:35
/// 
/// @section LICENSE
/// 
/// Copyright (c) 2025 Matthew Green - All rights reserved
/// Unauthorized copying of this file, via any medium is strictly prohibited
/// Proprietary and confidential

#pragma once

#include <velecs/math/Vec2.hpp>

#include <SDL3/SDL_scancode.h>
#include <SDL3/SDL_keycode.h>

namespace velecs::input {

/// @struct InputBindingContext
/// @brief Context data passed with input binding events containing processed values and metadata
///
/// Contains the processed output from input bindings along with contextual information like
/// active modifier keys and scancodes. Different binding types populate different value fields:
/// - ButtonBinding sets boolVal and valueType to Bool
/// - Vec2Binding sets vec2Val and valueType to Vec2  
/// - Future AnalogBinding would set floatVal and valueType to Float
///
/// @code
/// action.performed += [](const InputBindingContext& ctx) {
///     if (ctx.IsVec2()) {
///         Vec2 movement = ctx.GetVec2();
///         if (ctx.activeModifiers & ModifierKey::Shift) {
///             movement *= 2.0f; // Sprint multiplier
///         }
///         player.Move(movement);
///     }
/// };
/// @endcode
struct InputBindingContext {

using Vec2 = velecs::math::Vec2;

public:
    // Enums
    
    /// @enum ValueType
    /// @brief Indicates which value field contains meaningful data from the binding
    enum class ValueType
    {
        None,   ///< No meaningful value (default/uninitialized state)
        Bool,   ///< boolVal contains meaningful data (from ButtonBinding)
        Float,  ///< floatVal contains meaningful data (reserved for future AnalogBinding)
        Vec2,   ///< vec2Val contains meaningful data (from Vec2Binding)
    };

    // Public Fields

    /// @brief Boolean value from ButtonBinding (true when button is pressed)
    /// @note Only meaningful when valueType == ValueType::Bool
    bool boolVal{false};

    /// @brief Analog value from future AnalogBinding (0.0 to 1.0 range typically)
    /// @note Only meaningful when valueType == ValueType::Float
    /// @note Reserved for future trigger/slider input support
    float floatVal{0.0f};

    /// @brief Vector2 value from Vec2Binding (normalized direction vector)
    /// @note Only meaningful when valueType == ValueType::Vec2
    /// @note Represents combined input from WASD keys, gamepad stick, etc.
    Vec2 vec2Val{Vec2::ZERO};

    /// @brief Indicates which value field contains the meaningful data from this binding
    ValueType valueType{ValueType::None};

    /// @brief The primary scancode(s) that triggered this binding event
    /// @note For ButtonBinding: the single key pressed
    /// @note For Vec2Binding: combined/representative scancode (implementation detail)
    /// @note May be SDL_SCANCODE_UNKNOWN for complex multi-key bindings
    SDL_Scancode activePrimaryScancode{SDL_SCANCODE_UNKNOWN};

    SDL_Scancode activeSecondaryScancode{SDL_SCANCODE_UNKNOWN};

    SDL_Keymod activeKeymods{SDL_KMOD_NONE};

    // Constructors and Destructors

    /// @brief Default constructor creates context with no meaningful value
    /// @note All value fields initialized to zero/false, valueType set to None
    InputBindingContext() = default;

    /// @brief Copy constructor
    InputBindingContext(const InputBindingContext&) = default;

    /// @brief Move constructor
    InputBindingContext(InputBindingContext&&) = default;

    /// @brief Copy assignment operator
    InputBindingContext& operator=(const InputBindingContext&) = default;

    /// @brief Move assignment operator
    InputBindingContext& operator=(InputBindingContext&&) = default;

    /// @brief Default destructor
    ~InputBindingContext() = default;

    // Public Methods

    /// @brief Gets the boolean value from this context
    /// @return The boolean value from a ButtonBinding
    /// @note Should only be called when IsBool() returns true
    /// @warning No bounds checking - caller should verify valueType first
    inline bool GetBool() const { return boolVal; }

    /// @brief Gets the float value from this context
    /// @return The analog value from a future AnalogBinding
    /// @note Should only be called when IsFloat() returns true
    /// @warning No bounds checking - caller should verify valueType first
    inline float GetFloat() const { return floatVal; }

    /// @brief Gets the Vec2 value from this context
    /// @return The vector value from a Vec2Binding (movement, look direction, etc.)
    /// @note Should only be called when IsVec2() returns true
    /// @warning No bounds checking - caller should verify valueType first
    inline Vec2 GetVec2() const { return vec2Val; }

    /// @brief Checks if this context contains no meaningful value
    /// @return true if valueType is None (uninitialized or invalid state)
    inline bool IsNone() const { return valueType == ValueType::None; }

    /// @brief Checks if this context contains a boolean value
    /// @return true if this context was populated by a ButtonBinding
    inline bool IsBool() const { return valueType == ValueType::Bool; }

    /// @brief Checks if this context contains a float value
    /// @return true if this context was populated by an AnalogBinding (future)
    inline bool IsFloat() const { return valueType == ValueType::Float; }

    /// @brief Checks if this context contains a Vec2 value
    /// @return true if this context was populated by a Vec2Binding
    inline bool IsVec2() const { return valueType == ValueType::Vec2; }

    /// @brief Checks if any modifier keys are currently active
    /// @return true if any modifier keys (Ctrl, Shift, Alt, etc.) are active
    /// @note Convenience method to check if activeKeymods is not KMOD_NONE
    /// @see HasAnyModifiers(SDL_Keymod), HasAllModifiers()
    inline bool HasAnyModifiers() const
    { 
        return activeKeymods != SDL_KMOD_NONE; 
    }

    /// @brief Checks if any of the specified modifier keys are currently active
    /// @param mods The SDL_Keymod flags to test for (can be combined with | operator)
    /// @return true if any of the specified modifiers are active, false otherwise
    /// @note Uses bitwise AND to test for modifier presence
    /// @see HasAnyModifiers(), HasAllModifiers()
    /// @code
    /// if (ctx.HasAnyModifiers(KMOD_CTRL | KMOD_SHIFT)) {
    ///     // Either Ctrl OR Shift (or both) was active when binding triggered
    /// }
    /// @endcode
    inline bool HasAnyModifiers(const SDL_Keymod mods) const
    { 
        return (activeKeymods & mods) != 0; 
    }

    /// @brief Checks if all of the specified modifier keys are currently active
    /// @param mods The SDL_Keymod flags that must all be active
    /// @return true if all specified modifiers are active, false otherwise
    /// @note Uses bitwise AND to verify all modifiers are present
    /// @see HasAnyModifiers(), HasAnyModifiers(SDL_Keymod)
    /// @code
    /// if (ctx.HasAllModifiers(KMOD_CTRL | KMOD_SHIFT)) {
    ///     // Both Ctrl AND Shift were active when binding triggered
    /// }
    /// @endcode
    inline bool HasAllModifiers(const SDL_Keymod mods) const
    { 
        return (activeKeymods & mods) == mods; 
    }

protected:
    // Protected Fields

    // Protected Methods

private:
    // Private Fields

    // Private Methods
};

} // namespace velecs::input
