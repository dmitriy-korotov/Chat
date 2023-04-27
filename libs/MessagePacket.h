#pragma once
#ifndef MESSAGE_PACKET_H
#define MESSAGE_PACKET_H

#include <string>



namespace Chat
{
	class MessagePacket
	{
	public:

		explicit MessagePacket(const std::string& _message_packet) noexcept;
		MessagePacket(const MessagePacket&) = default;
		MessagePacket& operator=(const MessagePacket&) = default;
		MessagePacket(MessagePacket&&) = default;
		MessagePacket& operator=(MessagePacket&&) = default;

		const std::string& getSender() const noexcept;
		const std::string& getMessage() const noexcept;

	private:

		std::string m_sender;
		std::string m_message;

	};
}

#endif // !MESSAGE_PACKET_H
