#pragma once
//THIS CODE IS TAKEN FROM OUR CLASS WORK
#include "PongBoard.h"
#include "UserPongBoard.h"
#include "KeyboardEventListener.h"

class KeyboardManager
{
	enum { NUM_CHARS = 26, ESC }; // ESC hold the ascii of esc key.
	// an array of 'char' => list of kbListener
	std::list<KeyboardEventListener*> kbListeners[NUM_CHARS];

	// helper method - get index in array per a given char
	int getIndex(char c)const
	{
		int index = c - 'a';
		if (index < 0 || index >= NUM_CHARS)
			return -1;
		return index;
	}
public:
	void registerKbListener(KeyboardEventListener* pKbListener);
	bool handleKeyboard();
};