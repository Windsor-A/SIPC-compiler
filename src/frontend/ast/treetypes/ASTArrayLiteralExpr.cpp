#include "ASTArrayLiteralExpr.h"
#include "ASTVisitor.h"
#include "ASTinternal.h"

std::vector<std::shared_ptr<ASTNode>> ASTArrayLiteralExpr::getChildren() {
  std::vector<std::shared_ptr<ASTNode>> children;
  for (const auto &child : ELEMS)
    children.push_back(child);
  return children;
} // LCOV_EXCL_LINE

std::vector<ASTExpr *> ASTArrayLiteralExpr::getElems() const {
  return rawRefs(ELEMS);
} // LCOV_EXCL_LINE

void ASTArrayLiteralExpr::accept(ASTVisitor *visitor) {
  if (visitor->visit(this)) {
    for (ASTExpr *child : getElems())
      child->accept(visitor);
  }
  visitor->endVisit(this);
} // LCOV_EXCL_LINE

std::ostream &ASTArrayLiteralExpr::print(std::ostream &out) const {
  out << "[";
  auto children = getElems();
  for (int i = 0; i+1 < children.size(); i++)
    out << *children[i] << ", ";
  if (children.size())
    out << *children[children.size()-1];
  out << "]";
  return out;
} // LCOV_EXCL_LINE