#pragma once

#include <iostream>
#include <memory>
#include <string>

#include "../lexer/Lexer.h"
#include "Environment.h"
#include "../inter/Statement.h"
#include "../inter/Expression.h"
#include "../inter/Access.h"
#include "../lexer/Array.h"
#include "../inter/Statement-sequence.h"
#include "../inter/If.h"
#include "../inter/Else.h"
#include "../inter/While.h"
#include "../inter/Do.h"
#include "../inter/Break.h"
#include "../inter/Set.h"
#include "../inter/Set-elem.h"
#include "../inter/Or.h"
#include "../inter/And.h"
#include "../inter/Relational.h"
#include "../inter/Arithmetic-operator.h"
#include "../inter/Unary.h"
#include "../inter/Not.h"
#include "../inter/Constant.h"

class Parser{
public:
    explicit Parser(std::shared_ptr<Lexer> lexer);
    void program();

protected:
    void move();
    void error(std::string what);

    void match(const std::uint32_t &tag);
    std::shared_ptr<Statement> block();
    void decls();

    std::shared_ptr<Type> type();
    std::shared_ptr<Type> dimension(std::shared_ptr<Type>);

    std::shared_ptr<Statement> statements();
    std::shared_ptr<Statement> statement();
    std::shared_ptr<Statement> assign();

    std::shared_ptr<Expression> boolean();
    std::shared_ptr<Expression> join();
    std::shared_ptr<Expression> equality();
    std::shared_ptr<Expression> relational();
    std::shared_ptr<Expression> expression();
    std::shared_ptr<Expression> term();
    std::shared_ptr<Expression> unary();
    std::shared_ptr<Expression> factor();

    std::shared_ptr<Access> offset(std::shared_ptr<Identifier> id);

private:
    std::shared_ptr<Lexer> lexer_;
    std::shared_ptr<Token> lookahead_;
    std::shared_ptr<Environment> top_;
    std::uint32_t used_;
};