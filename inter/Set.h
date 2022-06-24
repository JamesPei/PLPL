#pragma once

#include "Statement.h"
#include "Identifier.h"

class Set : public Statement {
 public:
  static std::shared_ptr<Set> create(std::shared_ptr<Identifier> id, std::shared_ptr<Expression> expr){
    return std::make_shared<Set>(id, expr);
  };

  Set(std::shared_ptr<Identifier> id, std::shared_ptr<Expression> expr){
    if (!check(id_->type(), expr_->type())) {
        error("type error");
    }
  };

  ~Set(){};

  std::shared_ptr<Identifier> id() const{
      return id_;
  };

  std::shared_ptr<Expression> expr() const{
      return expr_;
  };

  std::shared_ptr<Type> check(std::shared_ptr<Type> left, std::shared_ptr<Type> right){
      if (left->is_numeric() && right->is_numeric())
        return right;
      else if (left == Type::boolean && right == Type::boolean)
        return right;
      else
        return std::shared_ptr<Type>();
  };

  void gen(const std::uint32_t &b, const std::uint32_t &a){
      emit(id_->to_string() + " = " + expr_->gen()->to_string());
  };

 private:
  std::shared_ptr<Identifier> id_;
  std::shared_ptr<Expression> expr_;
};