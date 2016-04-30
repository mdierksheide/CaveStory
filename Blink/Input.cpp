/* Input.cpp
 * Keeps track of all input to the game.
 */

#include "Input.h"

void Input::BeginNewFrame()
{
	_pressedKeys.clear();
	_releasedKeys.clear();
}

void Input::KeyUpEvent(const SDL_Event& event)
{
	_releasedKeys[event.key.keysym.scancode] = true;
	_heldKeys[event.key.keysym.scancode] = false;
}

void Input::KeyDownEvent(const SDL_Event& event)
{
	_pressedKeys[event.key.keysym.scancode] = true;
	_heldKeys[event.key.keysym.scancode] = true;
}

// Checks if a given key was pressed in the current frame
bool Input::WasKeyPressed(SDL_Scancode key)
{
	return _pressedKeys[key];
}

// Check if a given key was released in the current frame
bool Input::WasKeyReleased(SDL_Scancode key)
{
	return _releasedKeys[key];
}

// Check if a given key is being held during the current frame
bool Input::IsKeyHeld(SDL_Scancode key)
{
	return _heldKeys[key];
}