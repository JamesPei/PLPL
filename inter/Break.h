#pragma once

#include "Statement.h"

class Break : public Statement {
public:
    static std::shared_ptr<Break> create(){
        return std::make_shared<Break>();
    };

    Break():statement_(Statement::enclosing_statement){
        if (statement_ == Statement::kNullStatement)
            error("Unenclosed break");
    };
    virtual ~Break(){};

    virtual void gen(const std::uint32_t &b, const std::uint32_t &a){
        std::stringstream ss;
        ss << statement_->after();
        emit("goto L" + ss.str());
    };

    std::shared_ptr<Statement> statement() const;
private:
    std::shared_ptr<Statement> statement_;
};