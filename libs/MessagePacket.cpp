#include "MessagePacket.h"



namespace Chat
{
	MessagePacket::MessagePacket(const std::string& _message_packet) noexcept
	{
		size_t fst_div = _message_packet.find_first_of('|');

		m_sender = _message_packet.substr(0, fst_div);
		m_message = _message_packet.substr(fst_div + 1, _message_packet.length() - fst_div);
	}



	const std::string& MessagePacket::getSender() const noexcept
	{
		return m_sender;
	}



	const std::string& MessagePacket::getMessage() const noexcept
	{
		return m_message;
	}
}