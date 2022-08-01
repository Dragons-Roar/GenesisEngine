#include <GenesisCore/Random.hpp>

namespace ge {
	namespace core {
		Random::Random(int64 seed): seed(seed) {
			std::srand(seed);

			std::cout << seed << std::endl;

			dre = std::default_random_engine(rd());
			floatDist = std::uniform_real_distribution<float64>(0, 1);
		}

		template <>
		float32 Random::get(float32 max);
		template <>
		float64 Random::get(float64 max);

		template <>
		float32 Random::get(float32 min, float32 max);
		template <>
		float64 Random::get(float64 min, float64 max);

		bool Random::perc(float32 perc) {
			return (1.f - perc) <= random();
		}

		float64 Random::random() {
			return (float64) (rand()) / ((float64) RAND_MAX);
		}
	}
}
