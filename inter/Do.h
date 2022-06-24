#pragma once

#include "Statement.h"
#include "Expression.h"
#include "../lexer/Type.h"

class Do: public Statement {
public:
    static std::shared_ptr<Do> create(){
        return std::make_shared<Do>();
    };

    Do(){};
    ~Do(){};

    void init(std::shared_ptr<Statement> stmt, std::shared_ptr<Expression> expr){
        stmt_ = stmt;
        expr_ = expr;
        if (expr->type() != Type::boolean)
            expr->error("Boolean required in do");
    };

    void gen(const std::uint32_t &b, const std::uint32_t &a){
        after_ = a;
        auto label = new_label();
        stmt_->gen(b, label);
        emit_label(label);
        expr_->jumping(b, 0);
    };

    std::shared_ptr<Expression> expr() const{
        return expr_;
    };
    
    std::shared_ptr<Statement> stmt() const{
        return stmt_;
    };
private:
    std::shared_ptr<Expression> expr_;
    std::shared_ptr<Statement> stmt_;
};