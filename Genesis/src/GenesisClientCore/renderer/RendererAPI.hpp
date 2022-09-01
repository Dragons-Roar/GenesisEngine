#pragma once
#include "GenesisClientCore/renderer/VertexArray.hpp"
#include <glm/glm.hpp>

#define GE_RendererAPI_None ge::clientcore::RendererAPI::API::NONE
#define GE_RendererAPI_OpenGL ge::clientcore::RendererAPI::API::OPENGL

namespace ge {
	namespace clientcore {
		class RendererAPI {
		public:
			enum class API {
				NONE = 0,
				OPENGL = 1
			};

		public:
			virtual void init() = 0;

			virtual void clear() = 0;
			virtual void setClearColor(const glm::vec4& color) = 0;
			virtual void drawIndexed(const ge::core::Ref<IVertexArray>& array, uint32 indexCount = 0) = 0;

			virtual void setViewport(uint32 x, uint32 y, uint32 width, uint32 height) = 0;

			virtual void setWireframeMode(bool enable = true) = 0;

			static inline API getAPI() { return api; }

		private:
			static API api;
		};
	}
}
