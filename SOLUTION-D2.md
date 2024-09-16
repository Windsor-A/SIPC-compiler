We found that a lot of the new features could be added as extensions of the BinaryExpr ASTNodeType. 
The new ASTNode types were not hard to create, however we occasionally had some confusion as to what types certain node’s parameters should be, but they were promptly resolved.

All of our new nodes implement either ASTExpr or ASTStmt, depending on their corresponding type.

The following new ASTNodes were added:
- ArrayComprehensionExpr - arrays declared [a of b]
- ArrayLiteralExpr - arrays delcared [a,b,c,d]
- BooleanExpr - the new bool datatype
- BooleanNotExpr - boolean not
- DecrementStmt - a--
- IncrementStmt - a++
- ForEachStmt - for a : b statements
- ForStmt - for a : b .. c by d statements
- TernaryExpr - a ? b : c
- LengthExpr - #a
- NegationExpr - (-a)
- SubscriptExpr - a[b]

In addition BinaryExpr was updated to include:
- Less than (<)
- Greater than or equal to (>=)
- Less that or equal to (<=)
- Modulus	(%)
	

One thing we realized was that when we created the grammar, we lumped the two types of array declarations together into one type of statement. 
However, they required different types of ASTNodes. This meant we had to go back and adjust our work from deliverable 1. 
While this change was easily implemented, it shows how small decisions made early in the project can have large consequences later on.

Our testing was modeled after the tests that had previously been created/provided in ASTNodeTest and PrettyPrinterTest, 
while the ASTPrinterTest's statement printer and expression printer was updated.

To ensure high test coverage, we implemented all the types tests for each node in ASTNodeTest one by one to ensure they were included everywhere. For ASTPrinterTest, features are completely enumerated and are tested by logical grouping (simple expression? new statement? for loop?). For PrettyPrinterTest, we tested all SIP features at once, and tested several individually. In the future, we will test all them individually.

Due to the fact that these tests interface with some helper utilities from existing tests (and actually add directly onto some existing tests), the original test files were moved to the SIP variant in full--in the future, we will likely separate these properly.

In addition, we checked our test coverage with the gencov shell script.

We adopted a more traditional workflow for this deliverable, where one person would work on it for a time, 
then report to the other person what they had accomplished and what needed to be done next.
