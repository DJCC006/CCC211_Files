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
    const fs::path file =
        fs::path(EXAMPLE_DATA_DIR) / "inventory.json";

    try{

        std::ifstream input(file);
        if(!input){
            throw std::runtime_error("cannot open input file");
        }

        nl::json document;
        //deserializacion de los datos del json original a nuestra variable json
        input >> document;

        const auto& products =  document.at("products");
        double inventory_value =0.0;

        std::cout << "SKU\tStock\tPrice\tName\n";
        for(const auto& product : products){
            const std::string sku = product.at("sku").get<std::string>();
            const std::string name = product.at("name").get<std::string>();
            const int stock = product.at("stock").get<int>();
            const double price = product.at("price").get<double>();

            inventory_value += stock *price;
            std::cout<< std::format ("{}\t{}\t{:.2f}\t{}\n", sku, stock, price, name);
        }

        std::cout<<std::format("\nTotal inventory value: ${:.2f}\n", inventory_value);
        std::cout << "The complete JSON document is decoded in memory before traversal.\n";
    }catch(const std::exception& error){
        std::cerr << std::format("Could not read {}: {}\n", file.string(), error.what());
        return 1;
    }
}