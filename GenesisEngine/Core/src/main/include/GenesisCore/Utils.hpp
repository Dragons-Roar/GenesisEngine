#pragma once
#include "./Defines.hpp"
#include "./List.hpp"

namespace ge {
	namespace core {
		class Utils {
		public:
			/// <summary>
			/// Splits a string into a list
			/// </summary>
			/// <param name="list">The output list</param>
			/// <param name="str">The string to split</param>
			/// <param name="delim">The seperator</param>
			static void splitString(List<String, size_t>& list, const String& str, char delim = ',');
		};
	}
}
