#include <GenesisClientCore/Window.hpp>

#ifdef GE_WINDOWS
#	include <GenesisClientCore/platform/windows/WindowsWindow.hpp>
#else
#	error Undefined Plattform! Currently only Windows is supported!
#endif

namespace ge {
	namespace clientcore {
		IWindow* IWindow::create(const WindowProps& props) {
			#ifdef GE_WINDOWS
			return new WindowsWindow(props);
			#endif
			return nullptr;
		}
	}
}
