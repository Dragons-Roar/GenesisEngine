#pragma once
#include "GenesisCore/Defines.hpp"

namespace ge {
	namespace core {
		using AutoLockMutex = std::unique_lock<std::mutex>;
		using AutoLockRecursiveMutex = std::unique_lock<std::recursive_mutex>;
	}
}
