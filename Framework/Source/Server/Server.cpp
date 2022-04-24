#include "Server.h"

namespace VS
{
	Server::Server()
		: 
		IOContext(),
		Listener(asio::ip::tcp::endpoint(asio::ip::tcp::v4(), Port))
	{

	}
	Server::Server(std::uint16_t Port)
		:
		Server()
	{
		this->Port = Port;
	}

	void Server::Run()
	{
		try
		{
			Listen();
			AsioContextThread = std::thread([this]() { IOContext.run(); });
		}
		catch (std::exception& e)
		{
			// Signal error
			return;
		}
	}

	void Server::Terminate()
	{

	}

	void Server::Listen()
	{
		// Asynchronously listen for incoming connections
		Listener.async_accept(
			[this](std::error_code Err, asio::ip::tcp::socket Soc) 
			{
				if (!Err)
				{
					OnClientConnectionAttempt();
				}
				else
				{
					// Log error
				}
			});
	}
	void Server::OnClientConnectionAttempt()
	{

	}
	void Server::OnClientDisconnected()
	{
	}
}