#pragma once
#include "GenesisCore/Defines.hpp"
#include "GenesisCore/Logger.hpp"
#include <boost/stacktrace.hpp>

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
				GenesisRuntimeException(String msg): std::runtime_error(msg.c_str()) {
					stack = boost::stacktrace::stacktrace(2, 999999);
				}

				virtual const String name() const {
					return "ge::core::GenesisRuntimeException";
				}

				const String toString() const override {
					return "ge::core::GenesisRuntimeException";
				}

				static void print(const ge::core::exceptions::GenesisRuntimeException& e) {
					std::cerr << "Exception: " << e.name() << ": '" << e.what() << "'" << std::endl;
					std::cerr << e.stack;
				}

			private:
				boost::stacktrace::stacktrace stack;
			};
		}
	}
}
