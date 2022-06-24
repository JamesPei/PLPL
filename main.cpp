#include <iostream>
#include <string>

#include "lexer/Lexer.h"
#include "parser/Parser.h"

using namespace std;

int main(int argc, char const *argv[]){
    if(argc<2 or !argv[1]){
        cout << "need file path";
    };
    string source_code_file(argv[1]);
    cout << "process file:" << source_code_file << endl;
    auto lexer = Lexer::create(source_code_file);
    Parser pars(lexer);
    pars.program();
    return 0;
}
