#pragma once

#include "Logical.h"

class And : public Logical{
public:
    static std::shared_ptr<And> create(
        std::shared_ptr<Token> token,
        std::shared_ptr<Expression> left,
        std::shared_ptr<Expression> right
    ){
        auto res = std::make_shared<And>(token, left, right);
        res->init();
        return res;
    };

    And(std::shared_ptr<Token> token, std::shared_ptr<Expression> left, std::shared_ptr<Expression> right):
        Logical(token, left, right){};
    ~And(){};

    void jumping(const std::uint32_t &to, const std::uint32_t &from){
        int label = from != 0 ? from : new_label();
        expr1()->jumping(0, label);
        expr2()->jumping(to, from);
        if (!from)
            emit_label(label);
    };
};