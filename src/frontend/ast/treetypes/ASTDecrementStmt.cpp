#include "ASTDecrementStmt.h"
#include "ASTVisitor.h"

void ASTDecrementStmt::accept(ASTVisitor* visitor){
    if(visitor->visit(this)){
        getBody()->accept(visitor);
    }
    visitor->endVisit(this);
} // LCOV_EXCL_LINE

std::ostream &ASTDecrementStmt::print(std::ostream &out) const {
    out << *getBody() << "--;";
    return out;
} // LCOV_EXCL_LINE

std::vector<std::shared_ptr<ASTNode>> ASTDecrementStmt::getChildren() {
    std::vector<std::shared_ptr<ASTNode>> children;
    children.push_back(BODY);
    return children;
} // LCOV_EXCL_LINE
