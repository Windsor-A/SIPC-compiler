#pragma once

#include "ASTExpr.h"
#include "ASTStmt.h"

/*! \brief Class for range based for loop.
 */
class ASTForStmt : public ASTStmt {
    std::shared_ptr<ASTExpr> VAR, START, END, INCREMENT;
    std::shared_ptr<ASTStmt> STATEMENT;
public:
    std::vector<std::shared_ptr<ASTNode>> getChildren() override;
    ASTForStmt(std::shared_ptr<ASTExpr> VAR, std::shared_ptr<ASTExpr> START,
	std::shared_ptr<ASTExpr> END, std::shared_ptr<ASTExpr> INCREMENT, std::shared_ptr<ASTStmt> STATEMENT)
	: VAR(VAR), START(START), END(END), INCREMENT(INCREMENT), STATEMENT(STATEMENT) {};
    ASTExpr* getVar() const { return VAR.get(); }
    ASTExpr* getStart() const { return START.get(); }
    ASTExpr* getEnd() const { return END.get(); }
    ASTStmt* getStatement() const { return STATEMENT.get(); }
    /* \fn getIncrement
     * \return Increment value if it exists and nullptr otherwise.
     */
    ASTExpr* getIncrement() const {return INCREMENT.get(); }
    void accept(ASTVisitor* visitor) override;
    llvm::Value* codegen() override; // LCOV_EXCL_LINE

protected:
    std::ostream &print(std::ostream &out) const override;
};
