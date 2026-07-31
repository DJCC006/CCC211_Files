#include <iostream>
#include <fstream>
#include <cstring>

struct Estudiante{
    int id; //4 bytes
    char nombre[16]; //16 bytes
    float nota; //4 bytes
};

int main(){
    
    
    //ABRIR ARCHIVO EN MODO LECTURA
    std::ifstream in("data.dat", std::ios::binary);
    if(!in.is_open()){
        std::cerr <<"Cannot open file data.dat";
        return -1;
    }

    Estudiante st2={};

    in.read(reinterpret_cast<char *>(&st2), sizeof(Estudiante));
    in.close();

    std::cout<<"ID: "<<st2.id<< "\n"
    <<"Nombre: "<<st2.nombre<< "\n"
    <<"Nota: "<<st2.nota<<"\n";
    
    return 0;

}