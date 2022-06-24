#pragma once

#include <string>

#include "Token.h"
#include "Word.h"

class Type: public Word, public std::enable_shared_from_this<Type> {
public:
    static std::shared_ptr<Type> integer;
    static std::shared_ptr<Type> real;
    static std::shared_ptr<Type> character;
    static std::shared_ptr<Type> boolean;

    Type(const std::string &lexeme, const std::uint32_t &tag, const std::size_t &width):
        Word(lexeme, tag), width_(width){};
    virtual ~Type(){ width_ = 0; };

    static std::shared_ptr<Type> create(const std::string &lexeme, const std::uint32_t &tag, 
        const std::size_t &width){
        return std::make_shared<Type>(lexeme, tag, width);
    };
    
    static Type* max(Type* left, Type* right){
        if(!left)
            return right;
        else if(right)
            return left;
        else if(!left->is_numeric() || !right->is_numeric())
            return nullptr;
        else if(*left == *real || *right == *real)
            return real.get();
        else if(*left == *integer || *right == *integer)
            return integer.get();
        else
            return character.get();
    };

    std::size_t width() const{
        return width_;
    };
    bool is_numeric() const{
        return (*real == *this) || (*integer == *this) || (*character == *this);
    };

    std::shared_ptr<Type> getptr(){
        return shared_from_this();
    };
    // 此处必须设置为const对象，否则报错
    bool operator==(const Type& other) const {
        if(this == &other){
            return true;
        }else{
            return width_ == other.width_ && this->lexeme() == other.lexeme() 
                && this->tag() == other.tag();
        }
    }
private:
    std::size_t width_;
};