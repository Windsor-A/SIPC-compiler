#include "ASTNegationExpr.h"
#include "ASTVisitor.h"

void ASTNegationExpr::accept(ASTVisitor* visitor){
    if (visitor->visit(this) ){
        getVar()->accept(visitor);
    }
    visitor->endVisit(this);
} // LCOV_EXCL_LINE

std::ostream &ASTNegationExpr::print(std::ostream &out) const {
    out << "(-" << *getVar() << ")";
    return out;
} // LCOV_EXCL_LINE

std::vector<std::shared_ptr<ASTNode>> ASTNegationExpr::getChildren(){
    std::vector<std::shared_ptr<ASTNode>> children;
    children.push_back(VAR);
    return children;
} // LCOV_EXCL_LINE
