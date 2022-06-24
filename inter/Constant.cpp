#include "Constant.h"

std::shared_ptr<Constant> Constant::kTrue = Constant::create(Token::create(Word::kTrue), Type::boolean);
std::shared_ptr<Constant> Constant::kFalse = Constant::create(Token::create(Word::kFalse), Type::boolean);