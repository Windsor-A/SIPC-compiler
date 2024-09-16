#pragma once

#include "ASTExpr.h"

class ASTArrayComprehensionExpr : public ASTExpr {
  std::shared_ptr<ASTExpr> NUM, VAL;

public: 
  std::vector<std::shared_ptr<ASTNode>> getChildren() override;
  ASTArrayComprehensionExpr(std::shared_ptr<ASTExpr> NUM, std::shared_ptr<ASTExpr> VAL) : NUM(NUM), VAL(VAL) {}
  ASTExpr *getNum() const { return NUM.get(); }
  ASTExpr *getVal() const { return VAL.get(); }
  void accept(ASTVisitor *visitor) override;

  llvm::Value* codegen() override; // LCOV_EXCL_LINE

protected:
  std::ostream &print(std::ostream &out) const override;
};