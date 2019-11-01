#include <conio.h>
#include "KeyboardManager.h"


// KeyboardManager::registerKbListener gets a pongBoard by ref and register it in the appropriate list by his defined KbChars.
void KeyboardManager::registerKbListener(KeyboardEventListener* pKbListener)
{
	const char * chars = pKbListener->getKbChars();
	size_t numCharToRegister = strlen(chars);
	for (size_t i = 0; i < numCharToRegister; ++i) 
	{
		int index = getIndex(chars[i]);
		if (index != -1)
			kbListeners[index].push_back(pKbListener);
	}
}

// KeyboardManager::handleKeyboard handle the user keyboard clicks regarding ESC button and moving the pongBoards, it return 1 if the user pressed ESC otherwise it return 0.
bool KeyboardManager::handleKeyboard()
{
	char k = '\0';
	if (_kbhit()) 
	{
		k = tolower(_getch());
		if (k == ESC)
			return 1;
		int index = getIndex(k);
		if (index != -1) {
			for (auto pKbListener : kbListeners[index]) {
				pKbListener->handleKey(k);
			}
		}
	}
	return 0;
}
