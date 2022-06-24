#pragma once

#include "Statement.h"
#include "Expression.h"

class If : public Statement {
public:
    static std::shared_ptr<If> create(std::shared_ptr<Expression> expr, std::shared_ptr<Statement> statement){
        return std::make_shared<If>(expr, statement);
    };

    If(std::shared_ptr<Expression> expr, std::shared_ptr<Statement> statement):
        expr_(expr), statement_(statement){
        if(expr_->type() != Type::boolean)
            expr->error("Boolean required in if");
    };

    ~If(){};

    void gen(const std::uint32_t &b, const std::uint32_t &a){
        auto label = new_label();
        expr_->jumping(0, a);
        emit_label(label);
        statement_->gen(label, a);
    };

    std::shared_ptr<Expression> expr() const{
        return expr_;
    };

    std::shared_ptr<Statement> statement() const{
        return statement_;
    };

private:
    std::shared_ptr<Expression> expr_;
    std::shared_ptr<Statement> statement_;
};