#pragma once
#ifndef INTERFACE_SYNC_H
#define INTERFACE_SYNC_H

#include <functional>
#include <mutex>


namespace Chat
{
	class InterfaceSync
	{
	public:

		InterfaceSync(const InterfaceSync& _other) = delete;
		InterfaceSync& operator=(const InterfaceSync& _right) = delete;
		

		template <typename _Funct, typename ..._Args>
		static void captureFunction(_Funct _function, const _Args& ..._args) noexcept;

	protected:

		InterfaceSync() {};
		~InterfaceSync() {};

		static std::mutex m_chat_mutex;

	};



	template <typename _Funct, typename ..._Args>
	void InterfaceSync::captureFunction(_Funct _function, const _Args& ..._args) noexcept
	{
		if constexpr (std::is_function_v<_Funct>)
		{
			m_chat_mutex.lock();
			_function(_args...);
			m_chat_mutex.unlock();
		}
		else
		{
			m_chat_mutex.lock();
			_function(_args...);
			m_chat_mutex.unlock();
		}
	}
}


#endif // !INTERFACE_SYNC_H
