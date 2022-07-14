#pragma once

#include <memory>
#include <map>
#include <utility>

#include "../lexer/Token.h"
#include "../inter/Identifier.h"

class Environment: public std::enable_shared_from_this<Environment> {
public:
    static std::shared_ptr<Environment> create(std::shared_ptr<Environment> previous){
        return std::make_shared<Environment>(previous);
    };
    explicit Environment(std::shared_ptr<Environment> previous):previous_(previous), table_(){};

    void put(std::shared_ptr<Token> token, std::shared_ptr<Identifier> id){
        table_.insert(std::make_pair(token, id));
    };

    std::shared_ptr<Identifier> get(std::shared_ptr<Token> token) const{
        for(auto env = this->shared_from_this(); env.get()!=nullptr; env = env->previous_){
            auto found = env->table_.find(token);
            if(found!=env->table_.end())
                return found->second;
        }
        return std::shared_ptr<Identifier>();
    };

    void print_table(){
        for(auto m = table_.begin(); m!=table_.end(); ++m){
            std::cout << "Token:" << m->first->to_string() << " Identifier:" << m->second->to_string() << "\n";
        }
        std::cout << std::endl;
    };

protected:
    std::shared_ptr<Environment> previous_;
private:
    std::map<std::shared_ptr<Token>, std::shared_ptr<Identifier> > table_;
};