#include "Parser.h"

using namespace std;

Parser::Parser(shared_ptr<Lexer> lexer): lexer_(lexer) {
    move();
}

void Parser::program(){
    auto stmts = block();
    auto begin = stmts->new_label();
    auto after = stmts->new_label();
    stmts->emit_label(begin);
    stmts->gen(begin, after);
    stmts->emit_label(after);
}

void Parser::move(){
    lookahead_ = lexer_->scan();
    // cout << "after scan:" << lookahead_->to_string() << endl;
}

void Parser::error(string what){
    stringstream ss;
    ss << "Near line " << lexer_->current_line() << ": " << what;
    cerr << ss.str() << '\n';
    throw runtime_error(ss.str());
}

void Parser::match(const uint32_t &tag){
    if(lookahead_->tag() == tag)
        move();
    else
        error("Syntax error");
}

shared_ptr<Statement> Parser::block(){
    match('{');
    shared_ptr<Environment> saved_environment = top_;
    top_ = make_shared<Environment>(top_);
    decls();
    // top_->print_table();
    auto stmts = statements();
    match('}');
    top_ = saved_environment;
    return stmts;
}

void Parser::decls(){
    while(lookahead_->tag() == Token::kBasic){
        auto typ = type();
        auto token = lookahead_;
        match(Token::kIdentifier);
        match(';');
// template< class T, class U >
// std::shared_ptr<T> dynamic_pointer_cast( const std::shared_ptr<U>& r ) noexcept;
// Creates a new instance of std::shared_ptr whose stored pointer is obtained from 
// r's stored pointer using a cast expression.
// 假设Y是shared_ptr<T>::element_type, dynamic_pointer_cast<Y>(r)等同于dynamic_cast<Y*>(r.get())
        auto id = Identifier::create(dynamic_pointer_cast<Word>(token), typ, used_);
        top_->put(token, id);
        used_ += static_cast<uint32_t>(typ->width());
    }
}

shared_ptr<Type> Parser::type(){
    auto typ = dynamic_pointer_cast<Type>(lookahead_);
    match(Token::kBasic);
    if(lookahead_->tag()!='[')
        return typ;
    else
        return dimension(typ);
}

shared_ptr<Type> Parser::dimension(shared_ptr<Type> typ){
    match('[');
    auto token = lookahead_;
    match(Token::kInteger);
    match(']');
    if(lookahead_->tag() == '[')
        typ = dimension(typ);
    return Array::create(dynamic_pointer_cast<Number>(token)->value(), typ);
}

shared_ptr<Statement> Parser::statements() {
    if(lookahead_->tag() == '}'){
        return Statement::kNullStatement;
    } else {
        auto stmt1 = statement();
        auto stmt2 = statements();
        return StatementSequence::create(stmt1, stmt2);
    }
}

shared_ptr<Statement> Parser::statement() {
    shared_ptr<Expression> expr;
    shared_ptr<Statement> stmt, stmt1, stmt2;
    shared_ptr<Statement> saved_statement;

    switch(lookahead_->tag()){
        case ';':
            move();
            return Statement::kNullStatement;
        case Token::kIf:
            match(Token::kIf);
            match('(');
            expr = boolean();
            match(')');
            stmt1 = statement();
            if(lookahead_->tag()!=Token::kElse)
                return If::create(expr, stmt1);
            match(Token::kElse);
            stmt2 = statement();
            return Else::create(expr, stmt1, stmt2);
        case Token::kWhile: {
            auto while_node = While::create();
            saved_statement = Statement::enclosing_statement;
            Statement::enclosing_statement = while_node;
            match(Token::kWhile);
            match('(');
            expr = boolean();
            match(')');
            stmt1 = statement();
            while_node->init(expr, stmt1);
            Statement::enclosing_statement = saved_statement;
            return while_node;
        }
        case Token::kDo:{
            auto do_node = Do::create();
            saved_statement = Statement::enclosing_statement;
            Statement::enclosing_statement = do_node;
            match(Token::kDo);
            stmt1 = statement();
            match(Token::kWhile);
            match('(');
            expr = boolean();
            match(')');
            match(';');
            do_node->init(stmt1, expr);
            Statement::enclosing_statement = saved_statement;
            return do_node;
        }
        case Token::kBreak:
            match(Token::kBreak);
            match(';');
            return Break::create();
        case '{':
            return block();
        default:
            return assign();
    }
}

shared_ptr<Statement> Parser::assign(){
    shared_ptr<Statement> stmt;
    shared_ptr<Token> token = lookahead_;
    match(Token::kIdentifier);
    auto id = top_->get(token);
    if(!id)
        error(token->to_string() + " undeclared");
    
    if(lookahead_->tag() == '='){
        move();
        stmt = Set::create(id, boolean());
    }else{
        auto access = offset(id);
        match('=');
        stmt = SetElem::create(access, boolean());
    }
    match(';');
    return stmt;
}

shared_ptr<Expression> Parser::boolean(){
    auto expr = join();
    while(lookahead_->tag() == Token::kOr){
        auto token = lookahead_;
        move();
        expr = Or::create(token, expr, relational());
    }
    return expr;
}

shared_ptr<Expression> Parser::join(){
    auto expr = equality();
    while (lookahead_->tag() == Token::kAnd) {
        auto token = lookahead_;
        move();
        expr = And::create(token, expr, relational());
  }
  return expr;
}

shared_ptr<Expression> Parser::equality(){
    auto expr = relational();
    while (lookahead_->tag() == Token::kEqual || lookahead_->tag() == Token::kNotEqual) {
        auto token = lookahead_;
        move();
        expr = Relational::create(token, expr, expression());
    }
    return expr;
}

shared_ptr<Expression> Parser::relational(){
    auto expr = expression();
    switch (lookahead_->tag()) {
        case '<':
        case Token::kLessEqual:
        case Token::kGreaterEqual:
        case '>': {
            auto token = lookahead_;
            move();
            return Relational::create(token, expr, expression());
        }
        default:
            return expr;
    }
}

shared_ptr<Expression> Parser::expression(){
    auto expr = term();
    while (lookahead_->tag() == '+' || lookahead_->tag() == '-') {
        auto token = lookahead_;
        move();
        expr = Arithmetic::create(token, expr, term());
    }
    return expr;
}

shared_ptr<Expression> Parser::term(){
    auto expr = unary();
    while (lookahead_->tag() == '*' || lookahead_->tag() == '/') {
        auto token = lookahead_;
        move();
        expr = Arithmetic::create(token, expr, unary());
    }
    return expr;
}

shared_ptr<Expression> Parser::unary(){
    if (lookahead_->tag() == '-') {
        move();
        return UnaryOperator::create(Word::minus, unary());
    } else if (lookahead_->tag() == '!') {
        auto token = lookahead_;
        move();
        return Not::create(token, unary());
    } else {
        return factor();
    }
}

shared_ptr<Expression> Parser::factor(){
    auto expr = shared_ptr<Expression>();
    switch (lookahead_->tag()) {
        case '(':
            move();
            expr = boolean();
            match(')');
            return expr;
        case Token::kInteger:
            expr = Constant::create(lookahead_, Type::integer);
            move();
            return expr;
        case Token::kReal:
            expr = Constant::create(lookahead_, Type::real);
            move();
            return expr;
        case Token::kTrue:
            expr = Constant::kTrue;
            move();
            return expr;
        case Token::kFalse:
            expr = Constant::kFalse;
            move();
            return expr;
        case Token::kIdentifier: {
            auto s = lookahead_->to_string();
            auto id = top_->get(lookahead_);
            if (!id)
                error(lookahead_->to_string() + " undeclared");
            move();
            if (lookahead_->tag() != '[')
                return id;
            else
                return offset(id);
        }
        default:
            error("syntax error");
            return expr;
  }
}

shared_ptr<Access> Parser::offset(shared_ptr<Identifier> id){
    shared_ptr<Expression> width;
    shared_ptr<Expression> term1, term2;
    shared_ptr<Expression> location;

    auto typ = id->type();
    match('[');
    auto index = boolean();
    match(']');
    typ = std::dynamic_pointer_cast<Array>(typ)->type();
    width = Constant::create(typ->width());
    term1 = Arithmetic::create(Token::create('*'), index, width);
    location = term1;
    while (lookahead_->tag() == '[') {
        match('[');
        index = boolean();
        match(']');
        typ = std::dynamic_pointer_cast<Array>(typ)->type();
        width = Constant::create(typ->width());
        term1 = Arithmetic::create(Token::create('*'), index, width);
        term2 = Arithmetic::create(Token::create('+'), location, term1);
        location = term2;
    }
    return Access::create(id, location, typ);
}