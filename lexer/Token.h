#pragma once

#include <iostream>
#include <string>
#include <memory>
#include <limits>
#include <sstream>

class Token{
public:
    // static如果定义在文件中，它的作用域是当前文件,在其他文件中是不可见的，也就是说如果头文件A.h中
    // 定义了一个变量static int a = 100，然后cpp文件A01.cpp和A02.cpp都包含了A.h.那么两个cpp中
    // 的a的地址是不同的。可以正常编译通过。
    static const std::uint32_t kAnd = 256;
    static const std::uint32_t kBasic = 257;
    static const std::uint32_t kBreak = 258;
    static const std::uint32_t kDo = 259;
    static const std::uint32_t kElse = 260;
    static const std::uint32_t kEqual = 261;
    static const std::uint32_t kFalse = 262;
    static const std::uint32_t kGreaterEqual = 263;
    static const std::uint32_t kIdentifier = 264;
    static const std::uint32_t kIf = 265;
    static const std::uint32_t kIndex = 266;
    static const std::uint32_t kLessEqual = 267;
    static const std::uint32_t kMinus = 268;
    static const std::uint32_t kNotEqual = 269;
    static const std::uint32_t kInteger = 270;
    static const std::uint32_t kOr = 271;
    static const std::uint32_t kReal = 272;
    static const std::uint32_t kTemp = 273;
    static const std::uint32_t kTrue = 274;
    static const std::uint32_t kWhile = 275;
    static const std::uint32_t kSemicolon = 59;

    static std::shared_ptr<Token> create(const std::uint32_t &tag){
        return std::make_shared<Token>(tag);
    };
    explicit Token(const std::uint32_t tag):tag_(tag){};
    virtual ~Token(){
        // the largest possible value for type uint32_t
        tag_ = std::numeric_limits<std::uint32_t>::max();
    };

    std::uint32_t tag() const {
        return tag_;
    };
    
    virtual std::string to_string() const{
        std::stringstream ss;
        ss << static_cast<char>(tag_);
        // gets or sets the contents of underlying string device object
        return ss.str();
    };
private:
    std::uint32_t tag_;
};