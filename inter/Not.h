#pragma once

#include "Logical.h"

class Not: public Logical{
public:
    static std::shared_ptr<Not> create(std::shared_ptr<Token> token, std::shared_ptr<Expression> expr){
        auto res = std::make_shared<Not>(token, expr);
        res->init();
        return res;
    };

    Not(std::shared_ptr<Token> token, std::shared_ptr<Expression> expr):Logical(token, expr, expr){};
    ~Not(){};

    void jumping(const std::uint32_t &to, const std::uint32_t &from){
        expr1()->jumping(from, to);
    };
    
    std::string to_string() const{
        return oper()->to_string() + " " + expr1()->to_string();
    };
};