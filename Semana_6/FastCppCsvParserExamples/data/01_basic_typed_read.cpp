#include <filesystem>
#include <format>
#include <iostream>
#include <string>

#include "csv.h"

namespace fs = std::filesystem;

int main(){
    const fs::path file = fs::path(EXAMPLE_DATA_DIR) / "products.csv";
    
    try{
        io::CSVReader<4> reader(file.string());
        reader.read_header(io::ignore_extra_column, "sku", "name", "stock", "price");

        std::string sku;
        std::string name;
        int stock =0;
        double price =0.0;
        double inventory_value=0.0;

        std::cout << "SKU\tStock\tPrice\tName\n";
        while(reader.read_row(sku, name, stock, price)){
            inventory_value+=stock*price;
            std::cout<< std::format("{}\t{}\t:{:.2f}\t{}\n", sku, stock, price, name);
        }

        std::cout<< std::format("\nTotal inventory value: $(:.2f)\n", inventory_value);
        std::cout<< "This is a sequential scan: every data row  is read once.\n";
    }catch(const std::exception& error){
        std::cerr << std::format("Could not read {}: {}\n", file.string(), eror.what());
        return 1;
    }
}