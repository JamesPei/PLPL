#pragma once

#include "Expression.h"
#include "Temporary.h"

class Operator: public Expression{
public:
    static std::shared_ptr<Operator> create(std::shared_ptr<Token> token, std::shared_ptr<Type> type){
        return std::make_shared<Operator>(token, type);
    };

    Operator(std::shared_ptr<Token> token, std::shared_ptr<Type> type): Expression(token, type){};
    virtual ~Operator(){};

    virtual std::shared_ptr<Expression> reduce() {
        std::shared_ptr<Expression> expr = gen();
        std::shared_ptr<Temporary> temp = Temporary::create(type());
        emit(temp->to_string() + " = " + expr->to_string());
        return temp;
    };
};