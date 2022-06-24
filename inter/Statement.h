#pragma once

#include <cstdint>
#include <memory>

#include "Node.h"

class Statement: public Node{
public:
    static const std::shared_ptr<Statement> kNullStatement;
    static std::shared_ptr<Statement> enclosing_statement;
    
    static std::shared_ptr<Statement> create(){
        return std::make_shared<Statement>();
    };

    Statement():after_(0){};
    virtual ~Statement(){};
    std::uint32_t after() const{
        return after_;
    };
    virtual void gen(const std::uint32_t &b, const std::uint32_t &a){};
protected:
    std::uint32_t after_;
};