#pragma once
#include <vector>
#include <string>

class Buffer{
    public:
        //constructor
        Buffer(size_t size) : buff(size), p(buff.data()) {}
        
        char *data(){
            return buff.data();}

        size_t size(){
            return buff.size();}

        //Function Template Overloading -sobre carga de plantillas -- 
        //Unificacion de metodos write (int, unsigned, float) mediante template
        template <typename T>
        void write(T value){
            *reinterpret_cast<T *>(p) = value;
            p+= sizeof(T);
        }

        //Unificacion de metodo write de escritura (string) para mantener todo como vector de chars
        template <typename It>
        void write(It beg, It end){
            std::copy(beg,end, p);
            p += std::distance(beg, end);
        }

        void writeInt(int value);
        void writeUnsigned(unsigned value);
        void writeFloat(float value);
        void writeString(const std::string& str);

    private:
        std::vector<char> buff;
        char *p;

};
