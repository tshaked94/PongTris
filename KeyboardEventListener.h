#pragma once


class KeyboardEventListener 
{
public:
	virtual ~KeyboardEventListener() { ; }
	virtual void handleKey(char k) = 0;
	virtual const char* getKbChars()const = 0;
};
