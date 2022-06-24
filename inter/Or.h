#pragma once

#include "Logical.h"

class Or: public Logical{
public:
    static std::shared_ptr<Or> create(
        std::shared_ptr<Token> token,
        std::shared_ptr<Expression> left,
        std::shared_ptr<Expression> right
    ){
        auto res = std::make_shared<Or>(token, left, right);
        res->init();
        return res;
    };
    Or(std::shared_ptr<Token> token, std::shared_ptr<Expression> left, std::shared_ptr<Expression> right):Logical(token, left, right){};
    ~Or(){};

    void jumping(const std::uint32_t &to, const std::uint32_t &from) override;
};