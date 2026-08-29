#include <filesystem>
#include <format>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <map>
#include <string>

#include <nlohman/json.hpp>

//Establecimiento de alias /Type Alias Declaration
//using json = nlohman::json;
namespace nl = nlohmann;
namespace fs = std::filesystem;

int main(){
    const fs::path file = fs::path(EXAMPLE_DATA_DIR) / "transactions.ndjson";


    try{
        std::ifstream input(file);
        if(!input){
            throw std::runtime_error("cannot open input file");
        }

        std::map<std::string, double> balance_by_account;
        std::string line;
        std::size_t records_read =0;
        
        //NDJSON stores one complete JSON object per line. Unlike a normal JSON
        //array, it can be processed one record at a time with bounded input
        //buffering while preserving sequential disk access.
        while(std::getline(input, line)){
            if(line.empty()){
                continue;
            }
        

            const nl::json record = nl::json::parse(line);
            const std::string account = record.at("account").get<std::string>();
            const std::string type = record.at("type").get<std::string>();
            const double amount = record.at("amount").get<double>();

            balance_by_account[account] += (type == "DEBIT") ? -amount: amount;
            ++records_read;
        }

        std::cout << std::format("Sequentially processed {} records.\n", records_read);
        for(const auto& [account, balance] : balance_by_account){
            std::cout << std::format("   {}: $(:.2f)\n", account, balance);
        }
        std::cout<< "The input buffer is bounded, but the summary uses O(k) memory "
                    "for k distinct accounts.\n";
    }catch(const std::exception& error){
        std::cerr << std::format("Could not process {}: {}\n", file.string(), error.what());
        return 1;
    }
}