#pragma once

#include "Expression.h"

class Constant : public Expression {
public:
    static std::shared_ptr<Constant> kTrue;
    static std::shared_ptr<Constant> kFalse;

    static std::shared_ptr<Constant> create(std::shared_ptr<Token> token, std::shared_ptr<Type> type){
        return std::make_shared<Constant>(token, type);
    };
    static std::shared_ptr<Constant> create(std::int64_t value){
        return std::make_shared<Constant>(value);
    };

    Constant(std::shared_ptr<Token> token, std::shared_ptr<Type> type):Expression(token, type){};
    explicit Constant(std::int64_t value):Expression(std::make_shared<Number>(value), Type::integer){};
    ~Constant(){};

    void jumping(const std::uint32_t &to, const std::uint32_t &from){
        std::stringstream ss;
        if (this == kTrue.get() && to != 0) {
            ss << to;
            emit("goto L" + ss.str());
        } else if (this == kFalse.get() && from != 0) {
            ss << from;
            emit("goto L" + ss.str());
        }
    };
};