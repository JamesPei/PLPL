#pragma once

#include "Statement.h"
#include "Expression.h"
#include "../lexer/Type.h"

class While : public Statement {
public:
    static std::shared_ptr<While> create(){
        return std::make_shared<While>();
    };
    While(){};
    ~While(){};

    void init(std::shared_ptr<Expression> expr, std::shared_ptr<Statement> stmt){
        stmt_ = stmt;
        expr_ = expr;
        if (expr->type() != Type::boolean){
            expr->error("Boolean required in do");
        }
    };

    void gen(const std::uint32_t &b, const std::uint32_t &a){
        after_ = a;
        expr_->jumping(0, a);
        auto label = new_label();
        emit_label(label);
        stmt_->gen(label, b);
        std::stringstream ss;
        ss << b;
        emit("goto L" + ss.str());
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