#pragma once
#include <glm/glm.hpp>
#include "VertexArray.hpp"

#define GE_RendererAPI_None ge::clientcore::RendererAPI::API::NONE
#define GE_RendererAPI_OpenGL ge::clientcore::RendererAPI::API::OPENGL

namespace ge {
	namespace clientcore {
		class RendererAPI {
		public:
			enum class API {
				NONE = 0, OPENGL = 1
			};

		public:
			virtual void clear() = 0;
			virtual void setClearColor(const glm::vec4& color) = 0;

			virtual void drawIndexed(const ge::core::Ref<IVertexArray>& array) = 0;

			static inline API getAPI() { return api; }

		private:
			static API api;
		};
	}
}
