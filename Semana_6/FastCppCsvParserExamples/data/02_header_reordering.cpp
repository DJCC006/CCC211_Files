#include <filesystem>
#include <string>

#include "csv.h"

namespace fs = std::filesystem;

int main(){
    const fs::path file = fs::path(EXAMPLE_DATA_DIR) / "warehouse_stock.csv";

    try{
        //The physical order in the file is unit_price, warehouse, sku, units.
        //read_header maps fields by their names, so read_row can use a clearer
        //logical order. The unused warehouse column is explicitly tolerated. 
        io::CSVReader<3> reader(file.string());
        reader.read_header(io::ignore_extra_column, "sku", "units", "unit_price");

        std::string sku;
        int units=0;
        double unit_price =0.0;

        std::cout<< "SKU\tunits\tValue\n";
        while(reader.read_row(sku, units, unit_price)){
            std::cout <<std::format("{}\t{}\t${:.2f}\n", sku, units, unit_price);
        }

        std::cout<< "\nHeader-based mapping reduces coupling to column order.\n";
        std::cout<< "It does not avoid I/0: this remains a sequential file scan.\n";
    }catch(const std::exception& error){
        std::cerr<< std::format("Could not read {}: {}\n", file.string(), error.what());
        return 1;
    }
}