#pragma once

#include "ASTExpr.h"

/*! \brief Class for boolean literals.
 */

class ASTBooleanExpr : public ASTExpr {
    bool VAL;

public:
    ASTBooleanExpr(bool VAL) : VAL(VAL) {}
    bool getValue() const { return VAL; }
    void accept(ASTVisitor *visitor) override;
    llvm::Value* codegen() override; // LCOV_EXCL_LINE

protected:
    std::ostream &print(std::ostream &out) const override;
};
