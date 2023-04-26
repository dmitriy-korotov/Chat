#include "OutputMessagesControler.h"

#include "ConsoleOutputFunctions.h"

#include <chrono>



namespace Chat
{
	ConsoleCoords OutputMessagesControler::m_coords_messages = ConsoleCoords();
	uint16_t OutputMessagesControler::m_stride_between_messages = 1;



	void OutputMessagesControler::setStartPositionMessages(const ConsoleCoords& _console_coords) noexcept
	{
		m_coords_messages = _console_coords;
	}



	void OutputMessagesControler::setStrideBetweenMessages(uint16_t _stride) noexcept
	{
		m_stride_between_messages = _stride;
	}



	void OutputMessagesControler::printMessage(const std::string& _sender, const std::string& _message,
											   Chat::Console::EColor _sender_color, Chat::Console::EColor _message_color) noexcept
	{
		auto now = std::chrono::system_clock::now();
		std::time_t time = std::chrono::system_clock::to_time_t(now);

		captureFunction([&]()	// thread safety output
			{
				ConsoleCoords _current_coords = Console::getConsoleCursorPosition();

				Console::moveConsoleCursor(m_coords_messages);
				Chat::Console::setConsoleColor(_sender_color);
				std::cout << " => " << _sender << ":";
				printCenteringMessage(std::ctime(&time));
				Chat::Console::setConsoleColor(_message_color);
				std::cout << '\t' << _message;
				Console::moveConsoleCursor(_current_coords);
				m_coords_messages.setY(m_coords_messages.getY() + 3 + static_cast<uint16_t>((_message.length() + 4) / Console::getConsoleSize().getX()));
			});

	}
}