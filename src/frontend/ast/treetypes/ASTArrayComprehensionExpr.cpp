#include "ASTArrayComprehensionExpr.h"
#include "ASTVisitor.h"

std::vector<std::shared_ptr<ASTNode>> ASTArrayComprehensionExpr::getChildren() {
  std::vector<std::shared_ptr<ASTNode>> children;
  children.push_back(NUM);
  children.push_back(VAL);
  return children;
} // LCOV_EXCL_LINE

void ASTArrayComprehensionExpr::accept(ASTVisitor *visitor) {
  if (visitor->visit(this)) {
    getNum()->accept(visitor);
    getVal()->accept(visitor);
  }
  visitor->endVisit(this);
} // LCOV_EXCL_LINE

std::ostream &ASTArrayComprehensionExpr::print(std::ostream &out) const {
  out << "[" << *getNum() << " of " << *getVal() << "]"; 
  return out;
} // LCOV_EXCL_LINE