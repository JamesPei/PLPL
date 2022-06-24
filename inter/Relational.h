#pragma once

#include "Logical.h"
#include "../lexer/Array.h"

class Relational : public Logical {
 public:
  static std::shared_ptr<Relational> create(
      std::shared_ptr<Token> token,
      std::shared_ptr<Expression> left,
      std::shared_ptr<Expression> right
  ){
    auto res = std::make_shared<Relational>(token, left, right);
    res->init();
    return res;
  };

  Relational(std::shared_ptr<Token> token, std::shared_ptr<Expression> left, std::shared_ptr<Expression> right):
    Logical(token, left, right){};
  ~Relational(){};

  std::shared_ptr<Type> check(std::shared_ptr<Type> left, std::shared_ptr<Type> right){
    Array *arr_left = dynamic_cast<Array *>(left.get());
    Array *arr_right = dynamic_cast<Array *>(right.get());
    if (arr_left || arr_right) {
        return std::shared_ptr<Type>();
    } else if (left == right) {
        return Type::boolean;
    } else {
        return std::shared_ptr<Type>();
    }
  };

  void jumping(const std::uint32_t &to, const std::uint32_t &from){
    auto a = expr1()->reduce();
    auto b = expr2()->reduce();
    emit_jumps(a->to_string() + " " + oper()->to_string() + " " + b->to_string(), to, from);
  };
};