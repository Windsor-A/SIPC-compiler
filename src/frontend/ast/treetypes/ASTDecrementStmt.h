#pragma once

#include "ASTExpr.h"
#include "ASTStmt.h"

/*! \brief Class for a Decrement statement.
 */

class ASTDecrementStmt : public ASTStmt {
    std::shared_ptr<ASTExpr> BODY;

public:
    std::vector<std::shared_ptr<ASTNode>> getChildren() override;
    ASTDecrementStmt(std::shared_ptr<ASTExpr> BODY) : BODY(BODY) {}
    ASTExpr* getBody() const { return BODY.get(); }
    void accept(ASTVisitor *visitor) override;
    llvm::Value* codegen() override; // LCOV_EXCL_LINE

protected:
    std::ostream &print(std::ostream &out) const override;


};
