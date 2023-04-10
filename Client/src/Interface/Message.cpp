#include "Message.h"

#include "ConsoleOutputFunctions.h"



namespace Chat
{
	ConsoleCoords Message::m_coords_messages = ConsoleCoords();
	uint16_t Message::m_stride_between_messages = 1;



	void Message::setStartPositionMessages(const ConsoleCoords& _console_coords) noexcept
	{
		m_coords_messages = _console_coords;
	}



	void Message::setStrideBetweenMessages(uint16_t _stride) noexcept
	{
		m_stride_between_messages = _stride;
	}



	void Message::printMessage(const std::string& _sender, const std::string& _message,
							   ConsoleColor::EColor _sender_color, ConsoleColor::EColor _message_color) noexcept
	{
		moveConsoleCursor(m_coords_messages);
		ConsoleColor::setConsoleColor(_sender_color);
		std::cout << " => " << _sender << ":\n";
		ConsoleColor::setConsoleColor(_message_color);
		std::cout << '\t' << _message;

		m_coords_messages.setY(m_coords_messages.getY() + 3);
	}
}