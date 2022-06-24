#pragma once

#include "Expression.h"
#include "../lexer/Type.h"

class Identifier : public Expression {
public:
    static std::shared_ptr<Identifier> create(
        std::shared_ptr<Word> identifier,
        std::shared_ptr<Type> type,
        std::uint32_t offset){
        return std::make_shared<Identifier>(identifier, type, offset);
    };
    Identifier(std::shared_ptr<Word> identifier, 
        std::shared_ptr<Type> type, 
        std::uint32_t offset): Expression(identifier, type), offset_(offset){};
    ~Identifier(){};

    std::uint32_t offset() const{
        return offset_;
    };
private:
    std::uint32_t offset_;
};