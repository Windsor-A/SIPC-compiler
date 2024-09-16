#pragma once

#include "ASTExpr.h"

/*! \brief Class for ternary expressions
 */

class ASTTernaryExpr : public ASTExpr {
    std::shared_ptr<ASTExpr> VAR, FIRST, SECOND;

public:
    std::vector<std::shared_ptr<ASTNode>> getChildren() override;
    ASTTernaryExpr(std::shared_ptr<ASTExpr> VAR, std::shared_ptr<ASTExpr> FIRST, std::shared_ptr<ASTExpr> SECOND) : VAR(VAR), FIRST(FIRST), SECOND(SECOND) {}
    ASTExpr* getVar() const { return VAR.get(); }
    ASTExpr* getFirst() const { return FIRST.get(); }
    ASTExpr* getSecond() const { return SECOND.get(); }
    void accept(ASTVisitor* visitor) override;
    llvm::Value* codegen() override; // LCOV_EXCL_LINE

protected:
    std::ostream &print(std::ostream &out) const override;
};
