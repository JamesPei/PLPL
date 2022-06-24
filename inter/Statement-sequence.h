#pragma once

#include "Statement.h"

class StatementSequence: public Statement {
public:
    static std::shared_ptr<StatementSequence> create(std::shared_ptr<Statement> first, std::shared_ptr<Statement> second){
        return std::make_shared<StatementSequence>(first, second);
    };

    StatementSequence(std::shared_ptr<Statement> first, std::shared_ptr<Statement> second): first_(first), second_(second){};
    ~StatementSequence(){};

    std::shared_ptr<Statement> first() const{
        return first_;
    };
    
    std::shared_ptr<Statement> second() const{
        return second_;
    };
private:
    std::shared_ptr<Statement> first_;
    std::shared_ptr<Statement> second_;
};