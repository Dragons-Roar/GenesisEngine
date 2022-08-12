#pragma once
#include "GenesisCore/Defines.hpp"

namespace ge {
	namespace core {
		/// <summary>
		/// The base class (Like 'Object' in other languages)
		/// </summary>
		class GClass {
		public:
			virtual const String toString() const { return "GClass"; }

		private:
		};

		namespace exceptions {
			/// <summary>
			/// The default Genesis Runtime Exception
			/// </summary>
			class GenesisRuntimeException: public std::runtime_error, public GClass {
			public:
				GenesisRuntimeException(String cause): std::runtime_error(cause.c_str()) { }

				virtual const String name() const {
					return "ge::core::GenesisRuntimeException";
				}

				virtual const String toString() const override { return name() + ": " + String(what()); }
			};
		}
	}
}
