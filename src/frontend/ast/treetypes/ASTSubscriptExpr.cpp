#include "ASTSubscriptExpr.h"
#include "ASTVisitor.h"

void ASTSubscriptExpr::accept(ASTVisitor* visitor){
    if (visitor->visit(this)) {
        getArr()->accept(visitor);
        getIndex()->accept(visitor);
    }
    visitor->endVisit(this);
} // LCOV_EXCL_LINE

std::ostream &ASTSubscriptExpr::print(std::ostream &out) const {
    out << "(" << *getArr() << "[" << *getIndex() << "]" << ")";
    return out;
} // LCOV_EXCL_LINE

std::vector<std::shared_ptr<ASTNode>> ASTSubscriptExpr::getChildren() {
    std::vector<std::shared_ptr<ASTNode>> children;
    children.push_back(ARR);
    children.push_back(INDEX);
    return children;
} // LCOV_EXCL_LINE
