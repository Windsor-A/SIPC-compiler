#include "ASTForStmt.h"
#include "ASTVisitor.h"

void ASTForStmt::accept(ASTVisitor* visitor){
    if(visitor->visit(this)){
        getVar()->accept(visitor);
        getStart()->accept(visitor);
        getEnd()->accept(visitor);
        if(getIncrement() != nullptr){
            getIncrement()->accept(visitor);
        }
        getStatement()->accept(visitor);
    }
    visitor->endVisit(this);
} // LCOV_EXCL_LINE

std::ostream &ASTForStmt::print(std::ostream &out) const {
    out << "for (" << *getVar();
    out << " : " << *getStart();
    out << " .. " << *getEnd();
    if(getIncrement() != nullptr){
        out << " by " << *getIncrement();
    }
    out << ") ";
    out << *getStatement();
    return out;
} // LCOV_EXCL_LINE

std::vector<std::shared_ptr<ASTNode>> ASTForStmt::getChildren(){
    std::vector<std::shared_ptr<ASTNode>> children;

    children.push_back(VAR);
    children.push_back(START);
    children.push_back(END);
    if(getIncrement() != nullptr){
        children.push_back(INCREMENT);
    }
    children.push_back(STATEMENT);
    return children;
} // LCOV_EXCL_LINE
