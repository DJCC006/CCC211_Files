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
    const fs::path output_directory(EXAMPLE_OUTPUT_DIR);
    const fs::path output_file = output_directory / "inventory_snapshot.json";

    try{
        fs::create_directories(output_directory);

        //Build an in-memory document first. Only the stream operation below
        //perists it to secondary storage.
        const nl::json snapshot = {
            {"generated_at", "2026-07-15T10:30:00Z"},
            {"page_size_bytes", 4096},
            {"records", nl::json::array({
                {{"sku","P100"}, {"stock",12}, {"price", 29.99}},
                {{"sku","P101"}, {"stock",24}, {"price", 14.50}},
                {{"sku","P102"}, {"stock",5}, {"price", 199.95}}
            })}
        };

        std::ofstream output(output_file);
        if(!output){
            throw std::runtime_error("cannot open output file");
        }
        output << snapshot.dump(2) << '\n';
        output.close(); //Ensures write errors are observed before reopening.
        if(!output){
            throw std::runtime_error("error while writing JSON file");
        }

        std::ifstream input(output_file);
        nl::json restored;
        input >> restored;

        std::cout<< std::format("Persisted {} records in {}\n",
                                restored.at("records").size(), output_file.string());
        std::cout<< std::format("Configured page size: {} bytes\n",
                                restored.at("page_size_bytes").get<int>());
    }catch(const std::exception& error){
        std::cerr << std::format("Could not persist snapshot: {}\n", error.what());
        return 1;
    }
}