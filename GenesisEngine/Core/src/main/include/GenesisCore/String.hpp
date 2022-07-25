#pragma once
#include "./Defines.hpp"

namespace ge {
	namespace core {
		template <typename T, typename Index = size_t>
		class List;

		class String {
		public:
			String();
			String(char* val);
			String(const char* val);
			String(const String& src);
			String(const std::string& src);
			String(String&& src) noexcept;
			~String() { delete[] handle; size = 0; }
			
			static const size_t NO_POS;

			String substring(size_t start, size_t end) const;
			String substring(size_t start) const;

			/// <summary>
			/// Adds to strings together
			/// </summary>
			/// <param name="s">The string to concat</param>
			/// <returns>An instance of the current string</returns>
			String& concat(const String& s);
			/// <summary>
			/// Adds to strings together
			/// </summary>
			/// <param name="s">The string to concat</param>
			/// <returns>An instance of the current string</returns>
			String& concat(const char* str);

			/// <summary>
			/// Splits strings into String Lists
			/// </summary>
			/// <param name="list">The list</param>
			/// <param name="seperator">The seperator (Default: ',')</param>
			void split(List<String>& list, char seperator = ',');

			/// <summary>
			/// Splits strings into number lists
			/// </summary>
			/// <typeparam name="T">The number</typeparam>
			/// <param name="list">The list</param>
			/// <param name="seperator">The seperator (Default: ',')</param>
			template <typename T>
			void splitNum(List<T>& list, char seperator = ',') {
				std::stringstream ss(handle);
				std::string item;
				while(std::getline(ss, item, seperator)) {
					list.add(static_cast<T>(std::stoul(item)));
				}
			}

			/// <summary>
			/// Checks if a string contains a char
			/// </summary>
			/// <param name="c">The char</param>
			/// <returns>True if contains</returns>
			bool contains(const char c) const;

			/// <summary>
			/// Searches a char (starts at index 0)
			/// </summary>
			/// <param name="c">The char to find</param>
			/// <returns>The pos of the char (String::NO_POS if not found)</returns>
			size_t find(const char c, size_t start = 0) const;
			/// <summary>
			/// Searches a char (starts at the end)
			/// </summary>
			/// <param name="c">The char to find</param>
			/// <returns>The pos of the char (String::NO_POS if not found)</returns>
			size_t findLast(const char c) const;
			/// <summary>
			/// Searches a other char than this char (starts at index 0)
			/// </summary>
			/// <param name="c">The char to find</param>
			/// <returns>The pos of the char (String::NO_POS if not found)</returns>
			size_t findNot(const char c) const;
			/// <summary>
			/// Searches a other char than this char (starts at the end)
			/// </summary>
			/// <param name="c">The char to find</param>
			/// <returns>The pos of the char (String::NO_POS if not found)</returns>
			size_t findLastNot(const char c) const;

			/// <summary>
			/// Finds a char sequence (starts at index 0)
			/// </summary>
			/// <param name="c">The chars to find</param>
			/// <param name="start">Where to start the search</param>
			/// <returns>The pos where the sequence starts (String::NO_POS if not found)</returns>
			size_t find(const char* c, size_t start = 0) const;
			/// <summary>
			/// Finds a char sequence (starts at the end)
			/// </summary>
			/// <param name="c"></param>
			/// <returns>The pos where the sequence starts (String::NO_POS if not found)</returns>
			size_t findLast(const char* c) const;

			/// <summary>
			/// Converts this string to an uint8
			/// </summary>
			/// <returns>The uint8; 0 if string was no number or to large</returns>
			uint8 toUint8() const;
			/// <summary>
			/// Converts this string to an uint16
			/// </summary>
			/// <returns>The uint16; 0 if string was no number or to large</returns>
			uint16 toUint16() const;
			/// <summary>
			/// Converts this string to an uint32
			/// </summary>
			/// <returns>The uint32; 0 if string was no number or to large</returns>
			uint32 toUint32() const;
			/// <summary>
			/// Converts this string to an uint64
			/// </summary>
			/// <returns>The uint64; 0 if string was no number or to large</returns>
			uint64 toUint64() const;
			/// <summary>
			/// Converts this string to an int8
			/// </summary>
			/// <returns>The int8; 0 if string was no number or to large</returns>
			int8 toInt8() const;
			/// <summary>
			/// Converts this string to an int16
			/// </summary>
			/// <returns>The uint8; 0 if string was no number or to large</returns>
			int16 toInt16() const;
			/// <summary>
			/// Converts this string to an int32
			/// </summary>
			/// <returns>The int32; 0 if string was no number or to large</returns>
			int32 toInt32() const;
			/// <summary>
			/// Converts this string to an int64
			/// </summary>
			/// <returns>The int64; 0 if string was no number or to large</returns>
			int64 toInt64() const;

			/// <summary>
			/// Inserts a string at a pos
			/// </summary>
			/// <param name="pos">The pos</param>
			/// <param name="str">The insertion</param>
			void insert(size_t pos, const char* str);

			/// <summary>
			/// Inserts a string at a pos
			/// </summary>
			/// <param name="pos">The pos</param>
			/// <param name="str">The insertion</param>
			void insert(size_t pos, const String& str);

			/// <summary>
			/// Erases a amount of characters out of the string
			/// </summary>
			/// <param name="pos">Where to start</param>
			/// <param name="length">How many</param>
			void erase(size_t pos, size_t length);

			/// <summary>
			/// Replace all occurences with a other string
			/// </summary>
			/// <param name="what">What should be replace</param>
			/// <param name="with">The string to replace with</param>
			void replace(const String& what, const String& with) {
				_replace(what, with, 0);
			}

			inline static String toString(const int v) { return std::to_string(v); } const
			inline static String toString(const unsigned int v) { return std::to_string(v); } const
			inline static String toString(const float32 v) { return std::to_string(v); } const
			inline static String toString(const float64 v) { return std::to_string(v); } const
			inline static String toString(const bool v) { return v ? "true" : "false"; } const

			String& operator=(const String& b) {
				if(this == &b) {
					return *this;
				}

				delete[] handle;

				size = b.size;
				handle = new char[size + 1];
				std::strcpy(handle, b.handle);
				return *this;
			}

			friend std::ostream& operator<<(std::ostream& os, const String& str) {
				return os << str.handle;
			}

			friend String operator+(const String& a, const String& b) {
				size_t l = a.size + b.size;

				char* buff = new char[l + 1];
				std::strcpy(buff, a.handle);
				std::strcat(buff, b.handle);
				buff[l] = '\0';

				String temp(buff);
				delete[] buff;

				return temp;
			}
			const String& operator+=(const String& b) {
				size += b.size;
				char* buff = handle;
				handle = new char[size + 1];
				std::strcpy(handle, buff);
				std::strcat(handle, b.handle);
				buff[size] = '\0';

				return *this;
			}

			String operator+(const char* str) {
				size_t l = size + strlen(str);

				char* buff = new char[l + 1];
				std::strcpy(buff, handle);
				std::strcat(buff, str);
				buff[l] = '\0';

				String temp(buff);
				delete[] buff;

				return temp;
			}
			const String& operator+=(const char* str) {
				size += strlen(str);
				char* buff = handle;
				handle = new char[size + 1];
				std::strcpy(handle, buff);
				std::strcat(handle, str);
				buff[size] = '\0';

				return *this;
			}

			String operator+(int v) {
				return *this + toString(v);
			}
			const String& operator+=(int v) {
				String str = toString(v);
				char* buff = new char[size];
				std::strcpy(buff, handle);

				size += str.size;
				handle = new char[size + 1];
				std::strcpy(handle, buff);
				handle[size] = '\0';
				std::strcat(handle, str.handle);
				handle[size] = '\0';

				return *this;
			}

			String operator+(unsigned int v) {
				return *this + toString(v);
			}
			const String& operator+=(unsigned int v) {
				String str = toString(v);
				char* buff = new char[size];
				std::strcpy(buff, handle);

				size += str.size;
				handle = new char[size + 1];
				std::strcpy(handle, buff);
				handle[size] = '\0';
				std::strcat(handle, str.handle);
				handle[size] = '\0';

				return *this;
			}

			String operator+(float32 v) {
				return *this + toString(v);
			}
			const String& operator+=(float32 v) {
				String str = toString(v);
				char* buff = new char[size];
				std::strcpy(buff, handle);

				size += str.size;
				handle = new char[size + 1];
				std::strcpy(handle, buff);
				handle[size] = '\0';
				std::strcat(handle, str.handle);
				handle[size] = '\0';

				return *this;
			}

			String operator+(float64 v) {
				return *this + toString(v);
			}
			const String& operator+=(float64 v) {
				String str = toString(v);
				char* buff = new char[size];
				std::strcpy(buff, handle);

				size += str.size;
				handle = new char[size + 1];
				std::strcpy(handle, buff);
				handle[size] = '\0';
				std::strcat(handle, str.handle);
				handle[size] = '\0';

				return *this;
			}

			String operator+(bool v) {
				return *this + toString(v);
			}
			const String& operator+=(bool v) {
				String str = toString(v);
				char* buff = new char[size];
				std::strcpy(buff, handle);

				size += str.size;
				handle = new char[size + 1];
				std::strcpy(handle, buff);
				handle[size] = '\0';
				std::strcat(handle, str.handle);
				handle[size] = '\0';

				return *this;
			}

			String operator=(const char* src) {
				return String(src);
			}

			/// <summary>
			/// Gets the length of this string
			/// </summary>
			/// <returns>The length</returns>
			inline size_t length() const { return size; }

		private:
			char* handle;
			size_t size;

		private:
			void _replace(const String& what, const String& with, size_t start) {
				size_t pos = find(what.handle, start);
				if(pos == String::NO_POS) return;
				erase(pos, what.size);
				insert(pos, with);
				_replace(what, with, pos + with.size);
			}
		};
	}
}
