#include <filesystem>
#include <format>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>

#include <nlohmann/json.hpp>

//Establecimiento de alias /Type Alias Declaration
//using json = nlohman::json;
namespace nl = nlohmann;
namespace fs = std::filesystem;

int main(){
    const fs::path file = fs::path(EXAMPLE_DATA_DIR) / "invalid_inventory.json";

    try{
        std::ifstream input(file);
        if(!input){
            throw std::runtime_error("cannot open input file");
        }

        const nl::json document = nl::json::parse(input);
        (void)document;
    }catch(const nl::json::parse_error& error){
        //This data file deliberately has a trailing comma. A loader should
        //reject malformed persistence data rather than accepting corruption.
        std:: cout<< std::format("Expected JSON syntax error detected:\n   {}\n", error.what());
        return 0;
    }catch(const std::exception& error){
        std::cerr <<std::format("Unexpected error:  {}\n", error.what());
        return 1;
    }

    std::cerr << "Test failed: the malformed JSON document was accepted.\n";
    return 1;
}