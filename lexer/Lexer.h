#pragma once

#include <unordered_map>
#include <string>
#include <iostream>
#include <fstream>

#include "Token.h"
#include "Word.h"
#include "Type.h"
#include "NumericType.h"

class Lexer{
public:
    static std::shared_ptr<Lexer> create(std::string source_code=""){
        return std::make_shared<Lexer>(source_code);
    };

    Lexer(std::string source_code);
    ~Lexer();
    
    std::shared_ptr<Token> scan();
    static int current_line(){
        return current_line_;
    }; 
    
protected:
    void readch();
    bool readch(char c);
    void reserve(std::shared_ptr<Word> word);
private:
    std::ifstream input_stream;
    static int current_line_;
    char peek_;
    std::unordered_map<std::string, std::shared_ptr<Word>> words_;
};
