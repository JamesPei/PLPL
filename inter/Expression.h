#pragma once

#include <memory>

#include "Node.h"

class Expression: public Node, public std::enable_shared_from_this<Expression>{
public:
    static std::shared_ptr<Expression> create(std::shared_ptr<Token> oper, std::shared_ptr<Type> type){
        return std::make_shared<Expression>(oper, type);
    };

    explicit Expression(std::shared_ptr<Token> oper, std::shared_ptr<Type> type):type_(type), oper_(oper){};
    virtual ~Expression(){};

    virtual std::shared_ptr<Expression> get_ptr(){
        return shared_from_this();
    };
    virtual std::shared_ptr<Expression> gen(){
        return get_ptr();
    };
    virtual std::shared_ptr<Expression> reduce(){
        return get_ptr();
    };

    virtual void jumping(const std::uint32_t &to, const std::uint32_t &from){
        return emit_jumps(oper_->to_string(), to, from);
    };
    void emit_jumps(const std::string &test, const std::uint32_t &to, const std::uint32_t &from);

    virtual std::string to_string() const{
        return oper_->to_string();
    };

    std::shared_ptr<Token> oper() const{
        return oper_;
    };
    std::shared_ptr<Type> type() const{
        return type_;
    };
protected:
    std::shared_ptr<Type> type_;
    std::shared_ptr<Token> oper_;
};
