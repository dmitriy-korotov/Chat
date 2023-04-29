#pragma once 
#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <iostream>



namespace Chat
{
	class KeyBoard
	{
	public:

		enum EKeys : uint16_t
		{
			Escape = 27,
			Slesh = 47
		};

	};
}

#endif // !KEYBOARD_H
