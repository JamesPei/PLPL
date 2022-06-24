#pragma once

#include "Expression.h"
#include "../lexer/Word.h"

class Temporary: public Expression {
public:
    static std::shared_ptr<Temporary> create(std::shared_ptr<Type> type){
        return std::make_shared<Temporary>(type);
    };

    Temporary(std::shared_ptr<Type> type): Expression(Word::temp, type), number_(++count_){};
    ~Temporary(){};

    std::uint32_t number() const {
        return number_;
    };
    std::string to_string() const {
        std::stringstream ss;
        ss << " t " << number_;
        return ss.str();
    };

private:
    static std::uint32_t count_;
    std::uint32_t number_;
};