#include "ASTLengthExpr.h"
#include "ASTVisitor.h"

void ASTLengthExpr::accept(ASTVisitor* visitor){
    if (visitor->visit(this)) {
        getArr()->accept(visitor);
    }
    visitor->endVisit(this);
} // LCOV_EXCL_LINE

std::ostream &ASTLengthExpr::print(std::ostream &out) const {
    out << "(#" << *getArr() << ")";
    return out;
} // LCOV_EXCL_LINE

std::vector<std::shared_ptr<ASTNode>> ASTLengthExpr::getChildren() {
    std::vector<std::shared_ptr<ASTNode>> children;
    children.push_back(ARR);
    return children;
} // LCOV_EXCL_LINE
