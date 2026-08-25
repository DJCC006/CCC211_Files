#include <cstring>
#include <filesystem>
#include <fstream>
#include <optional>
#include <string>
#include <vector>

struct Product {
  int id;
  std::string name;
  double price;
  int stock;
};

std::optional<std::vector<std::string>> parseCSVLine(const std::string& line) {
  bool inQuotes = false;
  std::vector<std::string> fields;

  std::string field;

  for (char c : line) {
    if (c == '"') {
      inQuotes = !inQuotes;
    } else if (c == ',' && !inQuotes) {
      fields.push_back(field);
    } else {
      field += c;
    }
  }

  if (inQuotes) return std::nullopt;

  fields.push_back(field);

  return fields;
}

std::optional<std::vector<Product>> parseCSVFile(const std::string& path) {
  std::ifstream in(path);

  if (!in.is_open()) return std::nullopt;

  std::string line;

  while (std::getline(in, line)) {
    std::optional<std::vector<std::string>> result = parseCSVLine(line);

    if (!result) return std::nullopt;

    std::vector<std::string> fields = *result;

    if (fields.size() != 4) return std::nullopt;

    Product product;
    product.id = std::stoi(fields[0]);
  }
}