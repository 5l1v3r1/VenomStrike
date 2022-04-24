#pragma once

#include <thread>
#include <vector>

#include <asio.hpp>

#include <Application.h>
#include <Network/Connection.h>
#include <Core/Utils/ThreadSafeQueue.h>
#include <Core/Utils/ThreadSafeVector.h>


namespace VS
{
	class Server : public Application
	{
	public:
		Server();
		Server(std::uint16_t Port);
		virtual void Run() override;

		//! Forcibly kill the server.
		virtual void Terminate() override;

	protected:
		virtual void Listen();

		virtual void OnClientConnectionAttempt();
		virtual void OnClientDisconnected();

	private:
		asio::io_context IOContext;
		std::thread AsioContextThread;
		
		asio::ip::tcp::acceptor Listener;

		/// <summary>
		/// Queue of incoming connections. These may either be accepted (promoted to a maintained connection) or denied.
		/// </summary>
		TSQueue<std::shared_ptr<Net::Connection>> PendingConnections;

		TSVector<std::shared_ptr<Net::Connection>> MaintainedConnections;

		std::uint16_t Port = 31337;
	};
}