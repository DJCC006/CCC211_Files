#include <filesystem>
#include <format>
#include <iostream>
#include <string>

#include "csv.h"

namespace fs = std::filesystem;

int main(){
    const fs::path file = fs::path(EXAMPLE_DATA_DIR) / "invalid_products_bad_price.csv";
    
    try{
        io::CSVReader<4> reader(file.string());
        reader.read_header(io::ignore_extra_column, "sku", "name", "stock", "price");

        std::string sku;
        std::string name;
        int stock=0;
        double price =0.0;

        while(reader.read_row(sku, name, stock, price)){
            //If every row were valid, the conversion to double would succeed.
        }
    }catch(const std::exception& error){
        //The supplied data intentionally has a nonnumeric price. Reporting an
        //error is safer than silently persisting a corrupt record.
        std::cout <<std::format("Expected invalid-input error detected:\n {}\n", error.what());
        return 0;
    }

    std::cerr <<"Test failed: the malformed value was not detected.\n";
    return 1;
}