#pragma once

#include "Expression.h"
#include "Temporary.h"

class Logical : public Expression {
public:
  static std::shared_ptr<Logical> create(
      std::shared_ptr<Token> token,
      std::shared_ptr<Expression> expr1,
      std::shared_ptr<Expression> expr2
  ){
    auto res = std::make_shared<Logical>(token, expr1, expr2);
    res->init();
    return res;
  };

  Logical(std::shared_ptr<Token> token, std::shared_ptr<Expression> expr1, std::shared_ptr<Expression> expr2):
    Expression(token, std::shared_ptr<Type>()), expr1_(expr1), expr2_(expr2){};
  virtual ~Logical(){};

  std::shared_ptr<Expression> expr1() const{
      return expr1_;
  };

  std::shared_ptr<Expression> expr2() const{
      return expr2_;
  };

  virtual void init(){
    auto type = check(expr1_->type(), expr2_->type());
    if (!type)
        error("type error");
    type_ = type;
  };

  virtual std::shared_ptr<Type> check(
      std::shared_ptr<Type> left,
      std::shared_ptr<Type> right
  ){
      if (left == Type::boolean && right == Type::boolean)
        return Type::boolean;
      else
        return std::shared_ptr<Type>();
  };
  
  virtual std::shared_ptr<Expression> gen() override;

  virtual std::string to_string() const{
      return expr1_->to_string() + " " + oper_->to_string() + " " + expr2_->to_string();
  };

 private:
  std::shared_ptr<Expression> expr1_;
  std::shared_ptr<Expression> expr2_;
};