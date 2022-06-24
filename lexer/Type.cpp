#include "Type.h"

std::shared_ptr<Type> Type::integer = Type::create("int", Token::kBasic, 4);
std::shared_ptr<Type> Type::real = Type::create("float", Token::kBasic, 8);
std::shared_ptr<Type> Type::character = Type::create("char", Token::kBasic, 1);
std::shared_ptr<Type> Type::boolean = Type::create("bool", Token::kBasic, 1);