#pragma once

#include <asio.hpp>

namespace VS
{
	namespace Net
	{
		class Connection
		{
		public:
			enum class EOwner
			{
				Server,
				Client,
				None
			};

		private:
			EOwner Owner = EOwner::None;

			asio::ip::tcp::socket Socket;
			asio::io_context& IOContext;

			uint32_t ID = 0;
		};
	}
}