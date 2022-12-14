#pragma once
#include "GenesisCore/Defines.hpp"
#include "GenesisCore/GenesisBase.hpp"

namespace ge {
	namespace core {
		template <typename T, typename Index = size_t>
		class List: public GClass {
		public:
			typedef std::function<void(T&)> LoopFunction;
			typedef std::function<void(T&, Index)> LoopIndexFunction;
			typedef std::function<bool(const T&, const T&)> SortFunction;

			List() {}
			List(std::vector<T>& v) {
				resize(v.size());
				for(Index i = 0; i < v.size(); ++i) {
					add(v[i]);
				}
			}

			List(std::initializer_list<T> list) {
				handle = std::vector<T>(list);
			}

			/// <summary>
			/// Pushes an element on top of the list
			/// </summary>
			/// <param name="t"></param>
			void add(const T& t) {
				handle.push_back(t);
			}
			/// <summary>
			/// Removes an element at an index
			/// </summary>
			/// <param name="index"></param>
			void remove(Index index) {
				handle.erase(handle.begin() + index);
			}

			/// <summary>
			/// Changes the size of the list to allocate memory
			/// </summary>
			/// <param name="size">The new size of this list</param>
			void resize(Index size) {
				handle.resize(size);
			}

			/// <summary>
			/// Gets a element at a index
			/// </summary>
			/// <param name="index">The index</param>
			/// <returns>The element</returns>
			constexpr const T& get(const Index index) const {
				return handle.at(index);
			}
			/// <summary>
			/// Gets the size of this lsit
			/// </summary>
			/// <returns>The size</returns>
			Index size() const {
				return handle.size();
			}

			/// <summary>
			/// Loops through the array
			/// </summary>
			/// <param name="func">The Loop func (void(Element))</param>
			void foreach(LoopFunction func) {
				for(Index i = 0; i < handle.size(); ++i) {
					func(handle[i]);
				}
			}
			/// <summary>
			/// Loops through the array
			/// </summary>
			/// <param name="func">The Loop func (void(Element, Index))</param>
			void foreach(LoopIndexFunction func) {
				for(Index i = 0; i < handle.size(); ++i) {
					func(handle[i], i);
				}
			}

			std::vector<T>::iterator begin() { return handle.begin(); }
			std::vector<T>::iterator end() { return handle.end(); }
			std::vector<T>::reverse_iterator rbegin() { return handle.rbegin(); }
			std::vector<T>::reverse_iterator rend() { return handle.rend(); }

			String popLast(bool remove = true) {
				String out = handle.back();
				if(remove) handle.pop_back();
				return out;
			}
			void reverse() {
				List<T> list;
				std::vector<T> temp;
				temp.reserve(size());
				for(size_t i = handle.size() - 1; i >= 0; --i) {
					temp.push_back(handle[i]);
				}
				handle = temp;
			}

			constexpr T& operator[](Index i) {
				return handle.operator[](i);
			}
			constexpr const T& operator[](const Index i) const {
				return handle.operator[](i);
			}

			/// <summary>
			/// Sorts an array
			/// </summary>
			/// <param name="func">The function used to determine if the pair has to be swapped</param>
			void sort(SortFunction func) {
				Index i, j, min;
				for(i = 0; i < size() - 1; ++i) {
					min = i;
					for(j = i + 1; j < size(); ++j) {
						if(func(get(j), get(min))) {
							min = j;
						}
					}
					const T t = get(i);
					handle[i] = get(min);
					handle[min] = t;
				}
			}

			/// <summary>
			/// A string used to seperate the elements from the array and returning the resulting string
			/// </summary>
			/// <param name="seperator">The seperator</param>
			/// <returns>The string</returns>
			String join(std::string seperator) {
				std::stringstream ss;
				for(Index i = 0; i < size(); ++i) {
					ss << get(i);
					if(i < size() - 1) {
						ss << seperator;
					}
				}
				return ss.str();
			}

			const String toString() const override {
				std::stringstream ss;
				ss << "List<" << typeid(T).name() << "," << typeid(Index).name() << ">{size:" << handle.size() << "}";
				return ss.str();
			}

		private:
			std::vector<T> handle;
		};
	}
}