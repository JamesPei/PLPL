#pragma once

#include "Statement.h"
#include "Expression.h"
#include "Identifier.h"
#include "Access.h"
#include "../lexer/Array.h"

class SetElem : public Statement {
public:
    static std::shared_ptr<SetElem> create(std::shared_ptr<Access> access, std::shared_ptr<Expression> expr){
        return std::make_shared<SetElem>(access, expr);
    };

    SetElem(std::shared_ptr<Access> access, std::shared_ptr<Expression> expr):
        array_(access->array()), index_(access->index()), expr_(expr){
        if (!check(access->type(), expr_->type()))
            error("type error");
    };
    ~SetElem(){};

    std::shared_ptr<Identifier> array() const{
        return array_;
    };
    std::shared_ptr<Expression> index() const{
        return index_;
    };
    std::shared_ptr<Expression> expr() const{
        return expr_;
    };

    std::shared_ptr<Type> check(std::shared_ptr<Type> left, std::shared_ptr<Type> right){
        auto left_array = dynamic_cast<Array *>(left.get());
        auto right_array = dynamic_cast<Array *>(right.get());
        if (left_array || right_array)
            return std::shared_ptr<Type>();
        else if (left->is_numeric() && right->is_numeric())
            return right;
        else
            return std::shared_ptr<Type>();
    };

    void gen(const std::uint32_t &b, const std::uint32_t &a){
        auto index = index_->reduce()->to_string();
        auto expression = expr_->reduce()->to_string();
        emit(array_->to_string() + "[ " + index + " ] = " + expression);
    };
    
private:
    std::shared_ptr<Identifier> array_;
    std::shared_ptr<Expression> index_;
    std::shared_ptr<Expression> expr_;
};