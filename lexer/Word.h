#pragma once

#include "Token.h"

class Word: public Token{
/* 用于管理保留字，标识符和像&&这样的符合词法单元的词素，也可以用来管理在中间代码
中运算符的书写形式，比如单目减号 */
public:
    static std::shared_ptr<Word> and_word;
    static std::shared_ptr<Word> or_word;
    static std::shared_ptr<Word> equal;
    static std::shared_ptr<Word> not_equal;
    static std::shared_ptr<Word> less_equal;
    static std::shared_ptr<Word> greater_equal;
    static std::shared_ptr<Word> minus;
    static std::shared_ptr<Word> true_word;
    static std::shared_ptr<Word> false_word;
    static std::shared_ptr<Word> temp;

    static std::shared_ptr<Word> create(const std::string &lexeme, const std::uint32_t &tag){
        return std::make_shared<Word>(lexeme, tag);
    };
    Word(const std::string lexeme, const std::uint32_t tag):Token(tag), lexeme_(lexeme){};
    virtual ~Word(){};

    std::string lexeme() const{
        return lexeme_;
    };
    virtual std::string to_string() const {
        return lexeme();
    };
private:
    std::string lexeme_;
};