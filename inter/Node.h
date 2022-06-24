#pragma once

#include <iostream>
#include <sstream>

#include "../lexer/Lexer.h"

class Node{
public:
    void error(const std::string &message){
        std::stringstream ss;
        ss << "near line " << lexline_ << ": " << message;
        throw std::runtime_error(ss.str());
    };

    static std::uint32_t new_label(){
        return ++labels_;
    };

    void emit_label(const std::uint32_t &i){
        std::cout << "L" << i << ":";
    };

    void emit(const std::string &label){
        std::cout << '\t' << label << '\n';
    };

protected:
    Node():lexline_(Lexer::current_line()){};
    virtual ~Node(){
        lexline_ = 0;
    };

    std::size_t lexline_;
private:
    static std::uint32_t labels_;
};