#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <vector>
#include <algorithm>

//Incluimos la clase de buffer
#include "Buffer.hpp"


struct Estudiante{
    int id; //4 bytes
    std::string nombre;
    float nota; //4 bytes
};

int main(){
    


    /*

    ======VERSION INICIAL========
    ===PREVIA A INTEGRACION DE FUNCIONES===

    //Establecer el archivo a abrir y como se abrira
    std::ofstream out("data2.dat", std::ios::binary);

    //Validacion de apertura
    if(!out.is_open()){
        std::cerr << "Cannot open file data.dat";
        return -1;
    }

    //Creacion de dato struct
    Estudiante st;
    st.id=0xaabb;
    st.nombre= "Juan Hernandez";
    st.nota= 75.7;

    //cositas para guardar el string
    size_t recSize = sizeof(int)+ sizeof(unsigned)+ st.nombre.length()+ sizeof(float);

    //creamos un buffer temporal de vector del tamanio correcto
    std::vector<char> buffer(recSize); //guardamos como char para evitar el cast a la hora del write


    char *p= buffer.data(); //puntero al primer elemento

    //cosas que no sirven
        //buffer.push_back(st.id);
        //*p =st.id; //compila, pero trunca la informacion para que quede en la direccion


    //Serializacion ID
    *reinterpret_cast<int *>(p) = st.id; //le decimos al compilador que lo tome como un entero y escriba exactamente los 4 bytes del entero
    p+= sizeof(int); //movemos el puntero, asegurando que si se mueva el valor establecido de int...no hay garantia que int tendra un valor definido



    //Serializacion longitud nombre
    unsigned nameLen = st.nombre.length();
    *reinterpret_cast<int *>(p) = nameLen;
    p+=sizeof(unsigned);

    //formas de poner el nombre
        //Mediante std::copy  o std::memcopy

    std::copy(st.nombre.begin(), st.nombre.end(), p); //TENER BIEN DEFINIDO EL TAMANIO ACA
    p+= nameLen;



    //Serializacion de NOTA
    *reinterpret_cast<float *>(p)=st.nota;


    //Indicador de escritura
    //POINTER AL BLOQUE DE MEMORIA, INDICANDO EL TAMANIO A TOMAR
    out.write(buffer.data(), buffer.size()); //casteo confirma que estamos seguro de lo que guardaremos en memoria
    out.close();
    return 0;
    */


    //===VERSION ACTUALIZADA===
    //===IMPLEMENTANDO FUNCIONES SERIALIZABLES===
    std::ofstream out("data.dat", std::ios::binary);

    
    if(!out.is_open()){
        std::cerr << "Cannot open file data.dat";
        return -1;
    }

    Estudiante st;
    st.id= 0xaabb;
    st.nombre= "Juan Hernandez";
    st.nota= 75.7;

    size_t recSize = sizeof(int)+ sizeof(unsigned)+ st.nombre.length()+ sizeof(float);
    Buffer buffer(recSize);
    buffer.write(st.id);
    buffer.write<unsigned>(st.nombre.length()); //indicar el cambio de unsigned a cast
    //buffer.writeString(st.nombre);
    buffer.write(st.nombre.begin(), st.nombre.end());
    buffer.write(st.nota);

    out.write(buffer.data(), buffer.size());
    out.close();

    return 0;
}