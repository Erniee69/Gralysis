#pragma once

namespace ac {

	class NonCopyable {
	public:

		NonCopyable(const NonCopyable& other) = delete;
		NonCopyable(NonCopyable&& other) = delete;

		NonCopyable& operator=(const NonCopyable& other) = delete;
		NonCopyable& operator=(NonCopyable&& other) = delete;
	};
}