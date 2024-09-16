#include "ASTForEachStmt.h"
#include "ASTVisitor.h"

void ASTForEachStmt::accept(ASTVisitor* visitor) {
    if(visitor->visit(this)){
        getElement()->accept(visitor);
        getIterable()->accept(visitor);
        getBody()->accept(visitor);
    }
    visitor->endVisit(this);
} // LCOV_EXCL_LINE

std::ostream &ASTForEachStmt::print(std::ostream &out) const {
    out << "for (" << *getElement() << " : " << *getIterable() << ") ";
    out << *getBody();
    return out;
} // LCOV_EXCL_LINE

std::vector<std::shared_ptr<ASTNode>> ASTForEachStmt::getChildren(){
    std::vector<std::shared_ptr<ASTNode>> children;
    children.push_back(ELEMENT);
    children.push_back(ITERABLE);
    children.push_back(BODY);
    return children;
} // LCOV_EXCL_LINE
