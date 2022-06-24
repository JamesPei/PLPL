#pragma once

#include "Operator.h"

class Arithmetic : public Operator {
public:
  static std::shared_ptr<Arithmetic> create(
      std::shared_ptr<Token> token,
      std::shared_ptr<Expression> expr1,
      std::shared_ptr<Expression> expr2
  ){
      return std::make_shared<Arithmetic>(token, expr1, expr2);
  };

  Arithmetic(std::shared_ptr<Token> token, std::shared_ptr<Expression> expr1, std::shared_ptr<Expression> expr2):
    Operator(token, std::shared_ptr<Type>()), expr1_(expr1), expr2_(expr2){
    auto type = Type::max(expr1->type().get(), expr2->type().get());
    if (type == nullptr)
        error("Arithmentic expression has no valid types");
    else
        type_ = type->getptr();
  };
  virtual ~Arithmetic(){};

  std::shared_ptr<Expression> expr1() const{
      return expr1_;
  };
  std::shared_ptr<Expression> expr2() const{
      return expr2_;
  };

  virtual std::shared_ptr<Expression> gen(){
      return Arithmetic::create(oper_, expr1_->reduce(), expr2_->reduce());
  };

  virtual std::string to_string() const{
      return expr1_->to_string() + " " + oper_->to_string() + " " + expr2_->to_string();
  };

private:
  std::shared_ptr<Expression> expr1_;
  std::shared_ptr<Expression> expr2_;
};