#pragma once

#include "ASTExpr.h"

/*! \brief class for getting the length of an array
 */

class ASTLengthExpr : public ASTExpr {
    std::shared_ptr<ASTExpr> ARR;

public:
    std::vector<std::shared_ptr<ASTNode>> getChildren() override;
    ASTLengthExpr(std::shared_ptr<ASTExpr> ARR) : ARR(ARR) {}
    ASTExpr* getArr() const { return ARR.get(); }
    void accept(ASTVisitor* visitor) override;
    llvm::Value* codegen() override; // LCOV_EXCL_LINE

protected:
    std::ostream &print(std::ostream &out) const override;
};

