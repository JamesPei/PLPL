#pragma once

#include "Token.h"

template<typename T, std::uint32_t TAG>
class NumericType: public Token{
public:
    typedef T value_type;
    static std::shared_ptr<NumericType<T, TAG> > create(const T &value){
        return std::make_shared<NumericType<T, TAG> >(value);
    };
    
    explicit NumericType(const T &value):Token(TAG), value_(value){};
    ~NumericType(){};

    value_type value() const{
        return value_;
    };
    std::string toString() const {
        std::stringstream ss;
        ss << value_;
        return ss.str();
    };

private:
    T value_;
};

typedef NumericType<double, Token::kReal> Real;
typedef NumericType<std::int64_t, Token::kInteger> Number;
