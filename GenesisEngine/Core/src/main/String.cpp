#include <GenesisCore/String.hpp>
#include <GenesisCore/List.hpp>

namespace ge {
	namespace core {
		const size_t String::NO_POS = std::string::npos;

		String::String() {
			handle = new char[1];
			handle[0] = '\0';
			size = 0;
		}
		String::String(char* str) {
			if(str == nullptr) {
				handle = new char[1];
				handle[0] = '\0';
				size = 0;
			} else {
				size = strlen(str);
				handle = new char[size + 1];
				std::strcpy(handle, str);
				handle[size] = '\0';
			}
		}
		String::String(const char* str) {
			if(str == nullptr) {
				handle = new char[1];
				handle[0] = '\0';
				size = 0;
			} else {
				size = strlen(str);
				handle = new char[size + 1];
				std::strcpy(handle, str);
				handle[size] = '\0';
			}
		}
		String::String(const String& src) {
			size = src.size;
			handle = new char[size + 1];
			std::strcpy(handle, src.handle);
			handle[size] = '\0';
		}
		String::String(const std::string& src) {
			size = src.size();
			handle = new char[size + 1];
			std::strcpy(handle, src.c_str());
			handle[size] = '\0';
		}
		String::String(String&& src) noexcept {
			handle = src.handle;
			size = src.size;
			src.handle = nullptr;
			src.size = 0;
		}

		String& String::concat(const String& s) {
			size += s.size;
			char* buff = handle;
			handle = new char[size + 1];
			std::strcpy(handle, buff);
			std::strcat(handle, s.handle);

			handle[size] = '\0';

			delete[] buff;

			return *this;
		}
		String& String::concat(const char* str) {
			size += strlen(str);
			char* buff = handle;
			handle = new char[size + 1];
			std::strcpy(handle, buff);
			std::strcat(handle, str);

			handle[size] = '\0';

			delete[] buff;

			return *this;
		}

		bool String::contains(const char c) const {
			for(size_t i = 0; i < size; ++i) {
				if(handle[i] == c) return true;
			}
			return false;
		}

		size_t String::find(const char c, size_t start) const {
			for(size_t i = start; i < size; ++i) {
				if(handle[i] == c) return i;
			}
			return String::NO_POS;
		}
		size_t String::findLast(const char c) const {
			if(size < 1) return std::string::npos;
			for(size_t i = size - 1; i >= 0; --i) {
				if(handle[i] == c) return i;
			}
			return String::NO_POS;
		}

		size_t String::findNot(const char c) const {
			for(size_t i = 0; i < size; ++i) {
				if(handle[i] != c) return i;
			}
			return String::NO_POS;
		}
		size_t String::findLastNot(const char c) const {
			if(size < 1) return std::string::npos;
			for(size_t i = size - 1; i >= 0; --i) {
				if(handle[i] != c) return i;
			}
			return String::NO_POS;
		}

		size_t String::find(const char* c, size_t start) const {
			size_t cLen = strlen(c);
			if(size < cLen) return String::NO_POS;

			size_t i = start;
			while(i < size - cLen) {
				bool found = true;
				for(size_t j = 0; j < cLen; ++j) {
					if(handle[i + j] != c[j]) {
						i++;
						break;
					}
					if(j == cLen - 1) return i;
				}
			}
			return String::NO_POS;
		}
		size_t String::findLast(const char* c) const {
			size_t cLen = strlen(c);
			if(size < cLen) return String::NO_POS;

			size_t i = size - cLen - 1;
			while(i >= 0) {
				bool found = true;
				for(size_t j = 0; j < cLen; ++j) {
					if(handle[i + j] != c[j]) {
						i--;
						break;
					}
					if(j == cLen - 1) return i;
				}
			}
			return String::NO_POS;
		}

		void String::insert(size_t pos, const char* str) {
			// Copy the part before the insertion into a buffer and add the insertion to the buffer
			size_t cLen = strlen(str);
			char* buffer = new char[pos + cLen + 1];
			std::copy_n(handle, pos, buffer);
			buffer[pos] = '\0';
			std::strcat(buffer, str);
			buffer[pos + cLen] = '\0';

			char* temp = new char[size - pos + 1];
			std::strcpy(temp, handle + pos);
			temp[size - pos] = '\0';

			size += cLen; // Remove one so the 0 terminator is not counted
			handle = new char[size + 1]; // Add one so the 0 terminator can later be added back
			std::strcpy(handle, buffer);
			std::strcat(handle, temp);
			handle[size] = '\0'; // Add the 0 terminator back

			delete[] buffer;
			delete[] temp;
		}
		void String::insert(size_t pos, const String& str) {
			// Copy the part before the insertion into a buffer and add the insertion to the buffer
			size_t cLen = str.size;
			char* buffer = new char[pos + cLen + 1];
			std::copy_n(handle, pos, buffer);
			buffer[pos] = '\0';
			std::strcat(buffer, str.handle);
			buffer[pos + cLen] = '\0';

			char* temp = new char[size - pos + 1];
			std::strcpy(temp, handle + pos);
			temp[size - pos] = '\0';

			size += cLen; // Remove one so the 0 terminator is not counted
			handle = new char[size + 1]; // Add one so the 0 terminator can later be added back
			std::strcpy(handle, buffer);
			std::strcat(handle, temp);
			handle[size] = '\0'; // Add the 0 terminator back

			delete[] buffer;
			delete[] temp;
		}
		void String::erase(size_t pos, size_t length) {
			char* buffer = new char[size + 1];
			std::strcpy(buffer, handle);
			buffer[size] = '\0';

			size -= length;
			handle = new char[size + 1];
			std::copy_n(buffer, pos, handle);
			handle[pos] = '\0';
			std::strcat(handle, buffer + pos + length);
			handle[size] = '\0';

			delete[] buffer;
		}

		String String::substring(size_t start, size_t end) const {
			#ifndef GE_DIST
			if(end < start) throw std::exception("Start cannot be greater than end!");
			#endif

			if(start == String::NO_POS) {
				start = 0;
			}
			if(end > size) {
				end = size;
			}

			size_t length = end - start;
			char* buff = new char[length + 1];
			std::strcpy(buff, handle + start);

			buff[length] = '\0';

			return String(buff);
		}
		String String::substring(size_t start) const {
			return substring(start, size);
		}

		uint8 String::toUint8() const {
			return static_cast<uint8>(strtoul(handle, nullptr, 0));
		}
		uint16 String::toUint16() const {
			return static_cast<uint16>(strtoul(handle, nullptr, 0));
		}
		uint32 String::toUint32() const {
			return static_cast<uint32>(strtoul(handle, nullptr, 0));
		}
		uint64 String::toUint64() const {
			return static_cast<uint64>(strtoull(handle, nullptr, 0));
		}
		int8 String::toInt8() const {
			return static_cast<int8>(strtol(handle, nullptr, 0));
		}
		int16 String::toInt16() const {
			return static_cast<int16>(strtol(handle, nullptr, 0));
		}
		int32 String::toInt32() const {
			return static_cast<int32>(strtol(handle, nullptr, 0));
		}
		int64 String::toInt64() const {
			return static_cast<int64>(strtoll(handle, nullptr, 0));
		}

		void String::split(List<String>& list, char seperator) {
			std::stringstream ss(handle);
			std::string item;
			while(std::getline(ss, item, seperator)) {
				list.add(item);
			}
		}
	}
}
