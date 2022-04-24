#pragma once

#include <vector>
#include <mutex>

namespace VS
{
	template<typename T>
	class TSVector
	{


	private:
		std::mutex Mutex;
		std::vector<T> Vector;
	};
}