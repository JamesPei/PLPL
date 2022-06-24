#include "Statement.h"

using namespace std;

const shared_ptr<Statement> Statement::kNullStatement = Statement::create();

shared_ptr<Statement> Statement::enclosing_statement = Statement::kNullStatement;