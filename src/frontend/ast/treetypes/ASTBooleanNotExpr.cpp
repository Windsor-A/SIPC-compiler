#include "ASTBooleanNotExpr.h"
#include "ASTVisitor.h"

void ASTBooleanNotExpr::accept(ASTVisitor* visitor){
    if(visitor->visit(this)){
        getBool()->accept(visitor);
    }
    visitor->endVisit(this);
} // LCOV_EXCL_LINE

std::ostream &ASTBooleanNotExpr::print(std::ostream &out) const {
    out << "(not " << *getBool() << ")";
    return out;
} // LCOV_EXCL_LINE

std::vector<std::shared_ptr<ASTNode>> ASTBooleanNotExpr::getChildren() {
    std::vector<std::shared_ptr<ASTNode>> children;
    children.push_back(BOOL);
    return children;
} // LCOV_EXCL_LINE
