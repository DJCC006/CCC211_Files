#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "Buffer.h"

using std::string, std::vector, std::cin, std::cout;

struct Estudiante {
  int codigo;
  string nombre;
  string carrera;
  double promedio;
  int clasesAprobadas;
};

bool agregarEstudiante(const std::string& path, int codigo, const std::string& nombre, const std::string& carrera, double promedio, int clasesAprobadas);
bool crearArchivo(const std::string& path);
void listarEstudiantes(const std::string& path);
bool buscarEstudiante(const std::string& path, int codigo, Estudiante& resultado);
bool actualizarPromedio(const std::string& path, int codigo, double nuevoPromedio);

int main() {
}

bool agregarEstudiante(const std::string& path, int codigo, const std::string& nombre, const std::string& carrera, double promedio, int clasesAprobadas) {
  if (codigo <= 0) return false;
  if (nombre.empty() || carrera.empty()) return false;
  if (promedio > 100 || promedio < 0) return false;
  if (clasesAprobadas < 0) return false;

  if (!std::filesystem::exists(path)) {
    if (!crearArchivo(path)) return false;
  }

  std::fstream file(path, std::ios::binary | std::ios::in | std::ios::out);

  if (!file.is_open()) return false;

  int readCode;
  while (file.read(reinterpret_cast<char*>(&readCode), sizeof(readCode))) {
    if (readCode == codigo) return false;

    unsigned nombreLen;
    file.read(reinterpret_cast<char*>(&nombreLen), sizeof(nombreLen));
    file.seekg(nombreLen, std::ios::cur);

    unsigned carreraLen;
    file.read(reinterpret_cast<char*>(&carreraLen), sizeof(carreraLen));
    file.seekg(carreraLen, std::ios::cur);

    file.seekg(sizeof(double), std::ios::cur);
    file.seekg(sizeof(int), std::ios::cur);
  }

  file.clear();

  unsigned nombreLen = static_cast<unsigned>(nombre.size());
  unsigned carreraLen = static_cast<unsigned>(carrera.size());

  std::size_t recSize = sizeof(codigo) + sizeof(unsigned) + nombreLen + sizeof(unsigned) + carreraLen + sizeof(promedio) + sizeof(clasesAprobadas);
  Buffer buffer(recSize);

  buffer.write(codigo);
  buffer.write(nombreLen);
  buffer.writeString(nombre);
  buffer.write(carreraLen);
  buffer.writeString(carrera);
  buffer.write(promedio);
  buffer.write(clasesAprobadas);

  file.seekp(0, std::ios::end);
  file.write(buffer.data(), buffer.size());

  if (!file.good()) return false;

  return true;
}

bool crearArchivo(const std::string& path) {
  std::ofstream create(path);

  if (!create.is_open()) return false;

  return true;
}

void listarEstudiantes(const std::string& path) {
  if (!std::filesystem::exists(path)) return;

  std::ifstream in(path, std::ios::binary);

  if (!in.is_open()) return;

  int codigo;
  while (in.read(reinterpret_cast<char*>(&codigo), sizeof(codigo))) {
    string nombre;  // recuerda resizear
    string carrera;
    double promedio;
    int clasesAprobadas;

    unsigned strLen;
    in.read(reinterpret_cast<char*>(&strLen), sizeof(unsigned));

    nombre.resize(strLen);
    in.read(nombre.data(), strLen);

    in.read(reinterpret_cast<char*>(&strLen), sizeof(unsigned));

    carrera.resize(strLen);
    in.read(carrera.data(), strLen);

    in.read(reinterpret_cast<char*>(&promedio), sizeof(promedio));
    in.read(reinterpret_cast<char*>(&clasesAprobadas), sizeof(clasesAprobadas));

    cout << "Codigo: " << codigo << '\n';
    cout << "Nombre: " << nombre << '\n';
    cout << "Carrera: " << carrera << '\n';
    cout << "Promedio: " << promedio << '\n';
    cout << "Clases aprobadas: " << clasesAprobadas << "\n\n";
  }
}

bool buscarEstudiante(const std::string& path, int codigo, Estudiante& resultado) {
  std::ifstream in(path, std::ios::binary);

  if (!in.is_open()) return false;

  int readCode = -1;

  while (in.read(reinterpret_cast<char*>(&readCode), sizeof(readCode))) {
    if (codigo == readCode) return true;

    unsigned len;
    in.read(reinterpret_cast<char*>(&len), sizeof(len));
    in.seekg(len, std::ios::cur);

    in.read(reinterpret_cast<char*>(&len), sizeof(len));
    in.seekg(len, std::ios::cur);
    in.seekg(sizeof(double), std::ios::cur);
    in.seekg(sizeof(int), std::ios::cur);
  }

  return false;
}

bool actualizarPromedio(const std::string& path, int codigo, double nuevoPromedio) {
  if (nuevoPromedio < 0 || nuevoPromedio > 100) return false;

  std::fstream file(path, std::ios::binary | std::ios::in | std::ios::out);

  if (!file.is_open()) return false;

  int readCode = -1;

  while (file.read(reinterpret_cast<char*>(&readCode), sizeof(readCode))) {
    unsigned len;
    file.read(reinterpret_cast<char*>(&len), sizeof(len));
    file.seekg(len, std::ios::cur);

    file.read(reinterpret_cast<char*>(&len), sizeof(len));
    file.seekg(len, std::ios::cur);

    if (readCode == codigo) {
      file.write(reinterpret_cast<const char*>(&nuevoPromedio), sizeof(nuevoPromedio));
      return file.good();
    } else {
      file.seekg(sizeof(double), std::ios::cur);
    }

    file.seekg(sizeof(int), std::ios::cur);
  }

  return false;
}
