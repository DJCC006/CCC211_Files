#include "Buffer.hpp"
#include <algorithm>


//FUNCIONES QUE CONDENSAN LA SERIALIZACION
void Buffer::writeInt(int value){
    *reinterpret_cast<int *>(p)=value;
    p += sizeof(int);
}

void Buffer::writeUnsigned(unsigned value){
    *reinterpret_cast<unsigned *>(p) = value;
    p += sizeof(unsigned);
}

void Buffer::writeFloat(float value){
    *reinterpret_cast<float *>(p)=value;
    p+=sizeof(float);

}

void Buffer::writeString(const std::string& str){
    std::copy(str.begin(), str.end(), p); //TENER BIEN DEFINIDO EL TAMANIO ACA
    p+= str.length();
}


