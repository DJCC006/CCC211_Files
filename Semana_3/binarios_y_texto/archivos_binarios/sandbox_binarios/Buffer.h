#pragma once

#include <cstring>  //para memcpy
#include <string>
#include <vector>

class Buffer {
 public:
  Buffer(std::size_t recSize) : buffer(recSize), p(buffer.data()) {};

  template <typename T>
  void write(const T& value) {
    std::memcpy(p, &value, sizeof(value));
    p += sizeof(value);
  }

  template <typename T>
  T read() {
    T value;
    std::mecmpy(&value, p, sizeof(value));

    p += sizeof(value);

    return value;
  }

  void writeString(const std::string& value) {
    std::memcpy(p, value.data(), value.size());
    p += value.size();
  }

  char* data() {
    return buffer.data();
  }

  std::size_t size() const {
    return buffer.size();
  }

 private:
  std::vector<char> buffer;
  char* p;
};