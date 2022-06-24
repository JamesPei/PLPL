#pragma once

#include "Operator.h"

class UnaryOperator : public Operator {
public:
  static std::shared_ptr<UnaryOperator> create(
      std::shared_ptr<Token> token,
      std::shared_ptr<Expression> expression
  ){
    return std::make_shared<UnaryOperator>(token, expression);
  };

  UnaryOperator(std::shared_ptr<Token> token, std::shared_ptr<Expression> expression):
    Operator(token, std::shared_ptr<Type>()), expression_(expression){
    auto type = Type::max(Type::integer.get(), expression_->type().get());
    if (!type)
        error("Type error");
    else
        type_ = type->getptr();
  };

  ~UnaryOperator(){};

  std::shared_ptr<Expression> expression() const{
      return expression_;
  };
  
  std::shared_ptr<Expression> gen(){
      return UnaryOperator::create(oper(), expression_->reduce());
  };

  std::string to_string() const{
      return oper()->to_string();
  };

private:
  std::shared_ptr<Expression> expression_;
};