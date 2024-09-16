#pragma once

#include "ASTExpr.h"

/*! \brief class for accessing an element in an array
 */

class ASTSubscriptExpr : public ASTExpr {
    std::shared_ptr<ASTExpr> ARR, INDEX;

public:
    std::vector<std::shared_ptr<ASTNode>> getChildren() override;
    ASTSubscriptExpr(std::shared_ptr<ASTExpr> ARR, std::shared_ptr<ASTExpr> INDEX) : ARR(ARR), INDEX(INDEX) {}
    ASTExpr* getArr() const { return ARR.get(); }
    ASTExpr* getIndex() const { return INDEX.get(); }
    void accept(ASTVisitor* visitor) override;
    llvm::Value* codegen() override; // LCOV_EXCL_LINE

protected:
    std::ostream &print(std::ostream &out) const override;
};
