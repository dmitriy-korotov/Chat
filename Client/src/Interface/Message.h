#pragma once
#ifndef MESSAGE_H
#define MESSAGE_H

#include "ConsoleCoords.h"
#include "ConsoleColor.h"



namespace Chat
{
	class Message
	{
	public:

		Message() = delete;

		static void setStartPositionMessages(const ConsoleCoords& _console_coords) noexcept;
		static void setStrideBetweenMessages(uint16_t _stride) noexcept;

		static void printMessage(const std::string& _sender, const std::string& _message,
								 ConsoleColor::EColor _sender_color = ConsoleColor::EColor::Blue,
							     ConsoleColor::EColor _message_color = ConsoleColor::EColor::White) noexcept;

	private:

		static ConsoleCoords m_coords_messages;
		static uint16_t m_stride_between_messages;

	};
}

#endif // !MESSAGE_H
