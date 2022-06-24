#include "Expression.h"

#include <sstream>
#include <string>

using namespace std;

void Expression::emit_jumps(const string &test, const uint32_t &to, const uint32_t &from){
    stringstream ss;
    if(to && from){
        ss << "if " << test << " goto L" << to;
        emit(ss.str());
        ss.str("");
        ss << "goto L" << from;
        emit(ss.str());
    }else if(to){
        ss << "if " << test << " goto L" << to;
        emit(ss.str());
    }else if(from){
        ss << "if false " << test << " goto L" << from;
        emit(ss.str());
    }
}