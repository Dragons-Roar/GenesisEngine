#pragma once
#include "GenesisCore/Defines.hpp"

namespace ge {
	namespace core {
		class GClass {
		public:
			virtual const String toString() const { return "GClass"; }

		private:
		};

		namespace exceptions {
			/**
			 * @brief The default Genesis Runtime Exception
			 */
			class GenesisRuntimeException: public std::runtime_error, public GClass {
			public:
				GenesisRuntimeException(String msg): std::runtime_error(msg.c_str()) {}
				GenesisRuntimeException(String msg, Ref<GenesisRuntimeException> cause): std::runtime_error(msg.c_str()), e_cause(cause) {}

				ge::core::exceptions::GenesisRuntimeException cause() const {
					return *e_cause;
				}

				virtual const String name() const {
					return "ge::core::GenesisRuntimeException";
				}

				const String toString() const override {
					return "ge::core::GenesisRuntimeException";
				}

			private:
				Ref<ge::core::exceptions::GenesisRuntimeException> e_cause;
			};
		}
	}
}
