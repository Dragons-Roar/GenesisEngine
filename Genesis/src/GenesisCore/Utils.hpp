#pragma once
#include "GenesisCore/Defines.hpp"
#include "GenesisCore/List.hpp"

namespace ge {
	namespace core {
		class Utils {
		public:
			Utils() = delete;

			/// <summary>
			/// Splits a string into a list
			/// </summary>
			/// <param name="list">The output list</param>
			/// <param name="str">The string to split</param>
			/// <param name="delim">The seperator</param>
			static void splitString(List<String, size_t>& list, const String& str, char delim = ',');

			/// <summary>
			/// Counts chars in a string
			/// </summary>
			/// <param name="str">The string</param>
			/// <param name="c">The char to count</param>
			/// <returns>The count</returns>
			static uint32 countChars(const String& str, char c);
		};
	}
}
