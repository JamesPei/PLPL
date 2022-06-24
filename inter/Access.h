#pragma once

#include <memory>

#include "Operator.h"
#include "Identifier.h"
#include "Expression.h"
#include "../lexer/Type.h"

class Access: public Operator{
public:
    static std::shared_ptr<Access> create(std::shared_ptr<Identifier> id, 
        std::shared_ptr<Expression> index, 
        std::shared_ptr<Type> type){
        return std::make_shared<Access>(id, index, type);
    };

    Access(std::shared_ptr<Identifier> id, 
        std::shared_ptr<Expression> index, 
        std::shared_ptr<Type> type):
        Operator(Word::create("[]", Token::kIndex), type), array_(id), index_(index){};
    ~Access(){};

    std::shared_ptr<Identifier> array() const {
        return array_;
    };
    std::shared_ptr<Expression> index() const {
        return index_;
    };
    std::shared_ptr<Expression> gen() {
        return Access::create(array_, index_->reduce(), type_);
    };

    void jumping(const std::uint32_t &to, const std::uint32_t &from) {
        emit_jumps(reduce()->to_string(), to, from);
    };
    std::string to_string() const {
        return array_->to_string() + "[" + index_->to_string() + "]";
    };

private:
    std::shared_ptr<Identifier> array_;
    std::shared_ptr<Expression> index_;
};