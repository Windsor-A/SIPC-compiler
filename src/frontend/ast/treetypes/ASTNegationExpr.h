#pragma once

#include "ASTExpr.h"

/*! \breif Class for negation of an expression
 */

class ASTNegationExpr : public ASTExpr {
    std::shared_ptr<ASTExpr> VAR;

public:
    std::vector<std::shared_ptr<ASTNode>> getChildren() override;
    ASTNegationExpr(std::shared_ptr<ASTExpr> VAR) : VAR(VAR) {}
    ASTExpr *getVar() const { return VAR.get(); }
    void accept(ASTVisitor* visitor) override;
    llvm::Value* codegen() override; // LCOV_EXCL_LINE

protected:
    std::ostream &print(std::ostream &out) const override;
};
