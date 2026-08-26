#include <filesystem>
#include <format>
#include <iostream>
#include <string>

#include "csv.h"

namespace fs = std::filesystem;

int main(){
     const fs::path file = fs::path(EXAMPLE_DATA_DIR) / "transactions.tsv";

     try{
        //The fourth policy skips lines beginning with '#'. The quote policy
        //changes the fields separator from comma to tab.
        using TSVReader = io::CSVReader<4,
                                io::trim_chars<' ', '\t'>,
                                io::no_quote_escape<'\t'>,
                                io::throw_on_overflow,
                                io::single_line_comment<'#'>>;

        TSVReader reader(file.string());
        reader.read_header(io::ignore_extra_column, "account", "date", "type", "amount");

        std::string account;
        std::string date;
        std::string type;
        double amount =0.0;
        std::map<std::string, double> balance_by_account;

        while(reader.read_row(account, balance_by_account)){
            const double signed_amount = (type == "DEBIT") ? amount :amount;
            balance_by_account[account] += signed_amount;
        }

        std::cout <<"Account balances\n";
        for(const auto& [account_number, balance] : balance_by_account){
            std::cout << std::format("   {}: $(:.2f)\n", account_number, balance);
        }

        std::cout<<"\nThe map is an In-memory summary. For a large file, its memory use "
                    "grow with distinct accounts, while input access stays sequential.\n";
     }catch(const std::exception& error){
        std::cerr << std::format("Could not read {}: {}\n", file.string(), error.what());
        return 1;
     }
}