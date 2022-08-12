#pragma once
#include "GenesisCore/Defines.hpp"
#include "GenesisCore/Map.hpp"
#include "GenesisCore/GenesisBase.hpp"

namespace ge {
	namespace core {
		template<class K, class V>
		class Map: public GClass {
		public:
			typedef std::function<void(V)> LoopFunction;
			typedef std::function<void(K, V)> LoopFunctionKey;

			Map() { }
			~Map() { }

			void add(K key, V value) {
				handle.insert(std::make_pair(key, value));
			}
			V get(K key) const {
				return handle.at(key);
			}

			/// <summary>
			/// Loops through the map
			/// </summary>
			/// <param name="func">The loop func (void(Value))</param>
			void foreach(LoopFunction func) {
				for(auto it = handle.begin(); it != handle.end(); ++it) {
					func(it->second);
				}
			}
			/// <summary>
			/// Loops through the map including the key
			/// </summary>
			/// <param name="func">The loop func (void(Key, Value))</param>
			void foreach(LoopFunctionKey func) {
				for(auto it = handle.begin(); it != handle.end(); ++it) {
					func(it->first, it->second);
				}
			}
			/// <summary>
			/// Checks if the map contains a key
			/// </summary>
			/// <param name="key">The key</param>
			/// <returns>If the key was found</returns>
			bool contains(K key) {
				return handle.find(key) != handle.end();
			}
			/// <summary>
			/// Gets the amount of key in the map
			/// </summary>
			/// <returns>The amount of keys</returns>
			inline size_t size() const {
				return handle.size();
			}

			/// <summary>
			/// Clears the entire map
			/// </summary>
			inline void clear() {
				handle.clear();
			}

			const String toString() const override {
				std::stringstream ss;
				ss << "ge::core::Map<" << typeid(K).name() << ", " << typeid(V).name() << ">{size: " << handle.size() << "}";
				return ss.str();
			}

			constexpr V& operator[](K k) { return handle.operator[](k); }

		private:
			std::unordered_map<K, V> handle;
		};
	}
}
