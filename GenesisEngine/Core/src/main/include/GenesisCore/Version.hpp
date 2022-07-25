#pragma once
#include "Defines.hpp"
#include "./String.hpp"

namespace ge {
	namespace core {
		class Version {
		public:
			Version(): Version(0, 0, 0, 0) { }
			Version(uint32 major, uint32 minor, uint32 patch, uint32 build): 
					major(major), minor(minor), patch(patch), build(build) { }
			Version(const String& str);

			inline uint32 getMajor() const { return major; }
			inline uint32 getMinor() const { return minor; }
			inline uint32 getPatch() const { return patch; }
			inline uint32 getBuild() const { return build; }

			/// <summary>
			/// Formats the version to a human readable string
			/// </summary>
			/// <param name="build">If build number should be showed in string</param>
			/// <returns>The formated version</returns>
			String format(bool build = true) const;

			/// <summary>
			/// Increments the build number by 1
			/// </summary>
			void incrementBuild() { build++; }

			bool operator>(const Version& v) const;
			bool operator<(const Version& v) const;
			bool operator>=(const Version& v) const;
			bool operator<=(const Version& v) const;
			bool operator==(const Version& v) const;
			bool operator!=(const Version& v) const;

			/// <summary>
			/// Checks if a version is compatible with this version (minor and major must be the same)
			/// </summary>
			/// <param name="v">The version to check</param>
			/// <returns></returns>
			bool isCompatible(const Version& v);

		private:
			uint32 major, minor, patch, build;
		};
	}
}
