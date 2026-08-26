#include <filesystem>
#include <format>
#include <iostream>
#include <string>

#include "csv.h"

namespace fs = std::filesystem;

int main(){
    const fs::path file = fs::path(EXAMPLE_DATA_DIR) / "orders_quoted.csv";

    try{
        //This policy accepts fields delimited by double quotes. A qyote inside
        //a quoted field is represented by two quotes: "Ana ""Lopez""".
        using QuotedCSVReader = io::CSVReader<4,
                                                io::trim_chars<' ', '\t'>,
                                                io::double_quote_escape<',', '"'>>;
        QuotedCSVReader reader(file.string());
        reader.read_header(io::ignore_extra_column, "order_id", "customer", "city", "notes");
        
        int order_id=0;
        std::string customer;
        std::string city;
        std::string notes;

        while(reader.read_row(order_id, customer, city, notes)){
            std::cout<<std::format("Order {}\n Customer: {}\n City:     {}\n Notes:    {}\n\n",
                                    order_id, customer, city, notes);
        }

        std::cout<< "Use a quote policy only when the file format requires it.\n";
        cout::cout<< "It correctly handles commas embedded in quoted text.\n";
    }catch(const std::exception& error){
        std::cerr << std::format("Could not read {}: {}\n", file.string(), error.what());
        return 1;
    }
}