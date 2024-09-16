#pragma once

#include "ASTExpr.h"

class ASTArrayLiteralExpr : public ASTExpr {
  std::vector<std::shared_ptr<ASTExpr>> ELEMS;

public: 
  std::vector<std::shared_ptr<ASTNode>> getChildren() override;
  ASTArrayLiteralExpr(std::vector<std::shared_ptr<ASTExpr>> ELEMS) : ELEMS(ELEMS) {}
  std::vector<ASTExpr *> getElems() const;
  void accept(ASTVisitor *visitor) override;

  llvm::Value* codegen() override; // LCOV_EXCL_LINE

protected:
  std::ostream &print(std::ostream &out) const override;
};