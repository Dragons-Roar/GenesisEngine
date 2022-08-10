#include "Platform.hpp"

#ifdef GE_WINDOWS
#	include "platform/windows/WindowsPlatform.hpp"
#endif

namespace ge {
	namespace clientcore {
		#ifdef GE_WINDOWS
		Platform* Platform::instance = new WindowsPlatform();
		#else
		#	error Currenlty, only windows is supported!
		#endif
	}
}
