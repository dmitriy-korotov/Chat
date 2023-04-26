#pragma once
#ifndef MESSAGE_H
#define MESSAGE_H

#include "ConsoleCoords.h"
#include "Console.h"

#include "InterfaceSync.h"



namespace Chat
{
	class OutputMessagesControler : protected InterfaceSync
	{
	public:

		OutputMessagesControler() = delete;
		~OutputMessagesControler() = delete;

		static void setStartPositionMessages(const ConsoleCoords& _console_coords) noexcept;
		static void setStrideBetweenMessages(uint16_t _stride) noexcept;

		static void printMessage(const std::string& _sender, const std::string& _message,
								 Console::EColor _sender_color = Console::EColor::Blue,
							     Console::EColor _message_color = Console::EColor::White) noexcept;

	private:

		static ConsoleCoords m_coords_messages;
		static uint16_t m_stride_between_messages;

	};
}

#endif // !MESSAGE_H
