#pragma once

namespace ge {
	namespace core {
		class DirtyFlag {
		public:
			DirtyFlag(): dirty(true) { }
			DirtyFlag(bool dirty): dirty(dirty) { }

			void setDirty(bool dirty = true) { this->dirty = dirty; }
			bool isDirty() const { return dirty; }

		protected:
			bool dirty;
		};
	}
}
