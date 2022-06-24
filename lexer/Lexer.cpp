#include <cctype>

#include "Lexer.h"

using namespace std;

int Lexer::current_line_ = 0;

Lexer::Lexer(string source_code): words_(), peek_(' '), input_stream(source_code, ios::binary){
  reserve(make_shared<Word>("if", Token::kIf));
  reserve(make_shared<Word>("else", Token::kElse));
  reserve(make_shared<Word>("while", Token::kWhile));
  reserve(make_shared<Word>("do", Token::kDo));
  reserve(make_shared<Word>("break", Token::kBreak));

  reserve(Word::true_word);
  reserve(Word::false_word);

  reserve(Type::integer);
  reserve(Type::real);
  reserve(Type::boolean);
  reserve(Type::character);
}

void Lexer::reserve(std::shared_ptr<Word> word){
    words_.insert({word->lexeme(), word});
};

Lexer::~Lexer(){}

void Lexer::readch(){
    input_stream.get(peek_);
    if(input_stream.eof()){
        peek_ = '\0';
    }
}

bool Lexer::readch(char c){
    readch();
    if(peek_ != c) return false;
    peek_ = ' ';
    return true;
}

shared_ptr<Token> Lexer::scan(){
    // 略过所有空白字符
    if(input_stream.good()){
        while(!input_stream.eof()){
            if(peek_==';'){
                peek_ = input_stream.peek();
                return Token::create(static_cast<uint32_t>(';'));
            }else if (peek_=='['){
                peek_ = input_stream.peek();
                return Token::create(static_cast<uint32_t>('['));
            }else if (peek_==']'){
                peek_ = input_stream.peek();
                return Token::create(static_cast<uint32_t>(']'));
            }else if (peek_=='('){
                peek_ = input_stream.peek();
                return Token::create(static_cast<uint32_t>('('));
            }else if (peek_==')'){
                peek_ = input_stream.peek();
                return Token::create(static_cast<uint32_t>(')'));
            }
            
            input_stream.get(peek_);
            if(peek_ == ' ' || peek_=='\t'){
                continue;
            }else if(peek_ == '\n'){
                ++current_line_;
            }else{
                break;
            }
        }
    }else{
        throw runtime_error("source file not existed!");
    }

    // 识别符号
    switch (peek_){
        case '&':
            if(readch('&')){
                return Word::and_word;;
            }else{
                return Token::create(static_cast<uint32_t>('&'));
            }
            break;
        case '|':
            if(readch('|')){
                return Word::or_word;
            }else{
                return Token::create(static_cast<uint32_t>('|'));
            }
            break;
        case '=':
            if(readch('=')){
                return Word::equal;
            }else{
                return Token::create(static_cast<uint32_t>('='));
            }
            break;
        case '!':
            if(readch('=')){
                return Word::not_equal;
            }else{
                return Token::create(static_cast<uint32_t>('!'));
            }
            break;
        case '<':
            if(readch('=')){
                return Word::less_equal;
            }else{
                return Token::create(static_cast<uint32_t>('<'));
            }
            break;
        case '>':
            if(readch('=')){
                return Word::greater_equal;
            }else{
                return Token::create(static_cast<uint32_t>('>'));
            }
            break;
    }
    
    // 识别数字
    if(isdigit(peek_)){
        std::int64_t value = 0;
        do{
            value = 10ull*value + static_cast<int64_t>(peek_ - '0'); // '1'-->1
            readch();
        }while(isdigit(peek_));

        if(peek_!='.'){
            return make_shared<Number>(value);
        }

        double dvalue = static_cast<double>(value);
        double power = 10.0;
        for(;;){
            readch();
            if(!isdigit(peek_)){
                break;
            }
            dvalue += static_cast<double>(peek_ - '0')/power;
            power *= 10.0;
        }
        return make_shared<Real>(dvalue);
    }
    // 识别字母
    if(isalpha(peek_)){
        string str;
        do{
            str += peek_;
            readch();
        } while (isalnum(peek_));

        cout << __FILE__ << "-" << __LINE__ << " isalnum:" << str << endl;
        
        auto word_it = words_.find(str);
        if (word_it != words_.end())
            return word_it->second;
        auto word = Word::create(str, Token::kIdentifier); 
        words_.insert({str, word});
        return word;
    }
    auto token = Token::create(static_cast<uint32_t>(peek_));
    peek_ = ' ';
    return token;
}