#pragma once
#include "GenesisCore/Defines.hpp"

// Disable type cast warning for this section
#pragma warning (push)
#pragma warning (disable: 4244)
namespace ge {
	namespace core {
		class Location {
		public:
			Location() { }
			Location(const glm::vec3& pos): Location(pos.x, pos.y, pos.z) { }
			Location(const VoxelWorldPos& pos) {
				fx = 0.f; fy = 0.f; fz = 0.f;
				ix = pos.x; iy = pos.y; iz = pos.z;
			}
			Location(float32 x, float32 y, float32 z) {
				ix = x; iy = y; iz = z;
				fx = x - ix; fy = y - iy; fz = z - iz;
			}

			void setX(float32 x) {
				ix = x;
				fx = x - ix;
			}
			void setY(float32 y) {
				iy = y;
				fy = y - iy;
			}
			void setZ(float32 z) {
				iz = z;
				fz = z - iz;
			}

			void addX(float32 x) {
				setX(ix + fx + x);
			}
			void addY(float32 y) {
				setX(iy + fy + y);
			}
			void addZ(float32 z) {
				setX(iz + fz + z);
			}

			inline float32 getXf() const { return fx + ix; }
			inline float32 getYf() const { return fy + iy; }
			inline float32 getZf() const { return fz + iz; }

			inline float32 getXr() const { return fx; }
			inline float32 getYr() const { return fy; }
			inline float32 getZr() const { return fz; }

			inline int32 getX() const { return ix; }
			inline int32 getY() const { return iy; }
			inline int32 getZ() const { return iz; }

			inline int32 getChunkX() const { return ix / GE_CHUNK_SIZE_F; }
			inline int32 getChunkY() const { return iy / GE_CHUNK_SIZE_F; }
			inline int32 getChunkZ() const { return iz / GE_CHUNK_SIZE_F; }

			inline ChunkPos getChunkPos() const { return ChunkPos(getChunkX(), getChunkZ()); }

			operator glm::vec3() const {
				return glm::vec3(fx + ix, fy + iy, fz + iz);
			}
			operator VoxelWorldPos() const {
				return VoxelWorldPos(ix, iy, iz);
			}

		private:
			float32 fx, fy, fz;
			int32 ix, iy, iz;
		};
	}
}
#pragma warning (pop)
