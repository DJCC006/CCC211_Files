#include <filesystem>
#include <format>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>

#include <nlohman/json.hpp>

//Establecimiento de alias /Type Alias Declaration
//using json = nlohman::json;
namespace nl = nlohmann;
namespace fs = std::filesystem;

int main(){
    const fs::path file = fs::path(EXAMPLE_DATA_DIR) / "warehouse_layout.json";
    const std::string target_sku = "P102";

    try{
        std::ifstream input(file);
        if(!input){
            throw std::runtime_error("cannot open input file");
        }

        nl::json document;
        input >>document;

        //This is a logical search through the decoded JSON tree. It is not a 
        //disk index. the file was already read and parsed in its entirety.
        for(const auto& warehouse: document.at("warehouses")){
            for(const auto& zone: warehouse.at("zones")){
                for(const auto& item: zone.at("items")){
                    if(item.at("sku").get<std::string>() == target_sku){
                        std::cout << std::format("{} found in warehouse {}, zone {},  shelf {}\n",
                        target_sku,
                        warehouse.at("code").get<std::string>(),
                        zone.at("name").get<std::string>(),
                        item.at("shelf").get<std::string>());
                        return 0;
                    }
                }
            }
        } 

        std::cout << std::format("{} was not found.\n", target_sku);
        return 0;
    }catch(const std::exception& error){
        std::cerr << std::format("Could not search {}\n", file.string(), error.what());
        return 1;
    }
}