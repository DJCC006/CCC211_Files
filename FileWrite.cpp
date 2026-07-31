#include <iostream>
#include <fstream>
#include <cstring>

struct Estudiante{
    int id; //4 bytes
    char nombre[16]; //16 bytes
    float nota; //4 bytes
};

int main(){
    
    //Establecer el archivo a abrir y como se abrira
    std::ofstream out("data.dat", std::ios::binary);

    //Validacion de apertura
    if(!out.is_open()){
        std::cerr << "Cannot open file data.dat";
        return -1;
    }

    //Creacion de dato struct
    Estudiante st;
    st.id=-50;
    st.nota= 75.7;
    std::strncpy(st.nombre, "Juan Perez", sizeof(st.nombre)-1);

    //Indicador de escritura
    //POINTER AL BLOQUE DE MEMORIA, INDICANDO EL TAMANIO A TOMAR
    out.write(reinterpret_cast<char *>(&st), sizeof(Estudiante)); //casteo confirma que estamos seguro de lo que guardaremos en memoria
    out.close();
    return 0;

}