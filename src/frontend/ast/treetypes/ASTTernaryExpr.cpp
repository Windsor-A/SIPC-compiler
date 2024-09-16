#include "ASTTernaryExpr.h"
#include "ASTVisitor.h"

void ASTTernaryExpr::accept(ASTVisitor* visitor){
    if(visitor->visit(this)){
        getVar()->accept(visitor);
        getFirst()->accept(visitor);
        getSecond()->accept(visitor);
    }
    visitor->endVisit(this);
} // LCOV_EXCL_LINE

std::ostream &ASTTernaryExpr::print(std::ostream &out) const {
    out << "(" << *getVar() << "?" << *getFirst() << ":" << *getSecond() << ")";
    return out;
} // LCOV_EXCL_LINE

std::vector<std::shared_ptr<ASTNode>> ASTTernaryExpr::getChildren() {
    std::vector<std::shared_ptr<ASTNode>> children;
    children.push_back(VAR);
    children.push_back(FIRST);
    children.push_back(SECOND);
    return children;
} // LCOV_EXCL_LINE
