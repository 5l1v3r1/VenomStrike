#pragma once

#include <queue>
#include <mutex>
#include <memory>

namespace VS
{
	template<typename T>
	class TSQueue
	{
	public:
		TSQueue() = default;
		TSQueue(const TSQueue<T>&) = delete;
		TSQueue& operator=(const TSQueue<T>&) = delete;
		TSQueue(TSQueue&& Other)
		{
			std::lock_guard<std::mutex> Lock(Mutex);
			Queue = std::move(Other.Queue);
		}
		size_t GetLength() const
		{
			std::lock_guard<std::mutex> Lock(Mutex);
			return Queue.size();
		}

		T Front()
		{
			std::lock_guard<std::mutex> Lock(Mutex);

			if (GetLength() == 0)
			{
				// Scream
			}
			return Queue.front();
		}

		T Pop()
		{
			T Temp = Front();
			Queue.pop();
			return Temp;
		}

		void Push(const T& Item)
		{
			std::lock_guard<std::mutex> Lock(Mutex);
			Queue.push(Item);
		}

	private:
		std::queue<T> Queue;
		mutable std::mutex Mutex;
	};
}