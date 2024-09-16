#pragma once
#include "ASTExpr.h"

/*! \brief Class for negating a boolean
 */

class ASTBooleanNotExpr : public ASTExpr {
    std::shared_ptr<ASTExpr> BOOL;

public:
    std::vector<std::shared_ptr<ASTNode>> getChildren() override;
    ASTBooleanNotExpr(std::shared_ptr<ASTExpr> BOOL): BOOL(BOOL) {}
    ASTExpr* getBool() const { return BOOL.get(); }
    void accept(ASTVisitor *visitor) override;
    llvm::Value* codegen() override; // LCOV_EXCL_LINE

protected:
    std::ostream &print(std::ostream &out) const override;

};
