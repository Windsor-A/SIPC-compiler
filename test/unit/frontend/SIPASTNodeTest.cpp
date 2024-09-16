#include "ASTHelper.h"

#include <catch2/catch_test_macros.hpp>

#include <iostream>

#include <sstream>
#include "ASTVisitor.h"

class RecordPostPrint : public ASTVisitor {
public:
    std::vector<std::string> postPrintStrings;
    void record(ASTNode * element) {
       std::stringstream s; s << *element; postPrintStrings.push_back(s.str()); 
    }
    void endVisit(ASTProgram * element) { record(element); }
    void endVisit(ASTFunction * element) { record(element); }
    void endVisit(ASTNumberExpr * element) { record(element); }
    void endVisit(ASTVariableExpr * element) { record(element); }
    void endVisit(ASTBinaryExpr * element) { record(element); }
    void endVisit(ASTInputExpr * element) { record(element); }
    void endVisit(ASTFunAppExpr * element) { record(element); }
    void endVisit(ASTAllocExpr * element) { record(element); }
    void endVisit(ASTRefExpr * element) { record(element); }
    void endVisit(ASTDeRefExpr * element) { record(element); }
    void endVisit(ASTNullExpr * element) { record(element); }
    void endVisit(ASTFieldExpr * element) { record(element); }
    void endVisit(ASTRecordExpr * element) { record(element); }
    void endVisit(ASTAccessExpr * element) { record(element); }
    void endVisit(ASTDeclNode * element) { record(element); }
    void endVisit(ASTDeclStmt * element) { record(element); }
    void endVisit(ASTAssignStmt * element) { record(element); }
    void endVisit(ASTWhileStmt * element) { record(element); }
    void endVisit(ASTIfStmt * element) { record(element); }
    void endVisit(ASTOutputStmt * element) { record(element); }
    void endVisit(ASTReturnStmt * element) { record(element); }
    void endVisit(ASTErrorStmt * element) { record(element); }
    void endVisit(ASTBlockStmt * element) { record(element); }
    // Begin SIP Extensions
    void endVisit(ASTTernaryExpr * element) { record(element); }
    void endVisit(ASTArrayComprehensionExpr * element) { record(element); }
    void endVisit(ASTArrayLiteralExpr * element) { record(element); }
    void endVisit(ASTBooleanExpr * element) { record(element); }
    void endVisit(ASTBooleanNotExpr * element) { record(element); }
    void endVisit(ASTDecrementStmt * element) { record(element); }
    void endVisit(ASTIncrementStmt * element) { record(element); }
    void endVisit(ASTForEachStmt * element) { record(element); }
    void endVisit(ASTForStmt * element) { record(element); }
    void endVisit(ASTLengthExpr * element) { record(element); }
    void endVisit(ASTNegationExpr * element) { record(element); }
    void endVisit(ASTSubscriptExpr * element) { record(element); }
};

// Helper function that checks for raw node pointer in list
bool contains(std::vector<std::shared_ptr<ASTNode>> nodeList, ASTNode * nodeP) {
  bool found = false;
  for (auto & sharedNodeP : nodeList) {
    if (sharedNodeP.get() == nodeP) {
      found = true;
      break;
    }
  }
  return found;
}

TEST_CASE("ASTNodeTest: ASTAssign", "[ASTNode]") {
  auto rhs = std::make_unique<ASTNumberExpr>(42);
  auto lhs = std::make_unique<ASTVariableExpr>("x");

  // Record the raw pointers for these values because rhs and lhs will not be 
  // usable after the call to the constructor below.  This is because of the
  // move semantics associated with unique pointers, i.e., after the move the
  // locals rhs and lhs are nullptrs
  auto rhsValue = rhs.get();
  auto lhsValue = lhs.get();

  auto assign = std::make_unique<ASTAssignStmt>(std::move(lhs), std::move(rhs));

  // Test Print Method
  std::stringstream nodePrintStream;
  nodePrintStream << *assign;
  REQUIRE(nodePrintStream.str() == "x = 42;");

  // Test getters 
  REQUIRE(rhsValue == assign->getRHS());
  REQUIRE(lhsValue == assign->getLHS());

  // Test getChildren
  auto children = assign->getChildren();
  REQUIRE(children.size() == 2);
  REQUIRE(contains(children, rhsValue));
  REQUIRE(contains(children, lhsValue));

  // Test accept
  RecordPostPrint visitor;
  assign->accept(&visitor);
  std::string expected[] = { "x", "42", "x = 42;" };
  for (int i=0; i < 3; i++) {
    REQUIRE(visitor.postPrintStrings[i] == expected[i]);
  }
}

// Begin SIP Extensions
TEST_CASE("ASTNodeTest: ASTTernary", "[ASTNode]") {
  auto cond = std::make_unique<ASTVariableExpr>("x");
  auto ift = std::make_unique<ASTVariableExpr>("y");
  auto iff = std::make_unique<ASTVariableExpr>("z");

  auto condPtr = cond.get();
  auto iftPtr = ift.get();
  auto iffPtr = iff.get();

  auto ternary = std::make_unique<ASTTernaryExpr>(std::move(cond), std::move(ift), std::move(iff));

  // Test Print Method
  std::stringstream nodePrintStream;
  nodePrintStream << *ternary;
  REQUIRE(nodePrintStream.str() == "(x?y:z)");

  // Test getters
  REQUIRE(condPtr == ternary->getVar());
  REQUIRE(iftPtr == ternary->getFirst());
  REQUIRE(iffPtr == ternary->getSecond());

  // Test getChildren
  auto children = ternary->getChildren();
  REQUIRE(children.size() == 3);
  REQUIRE(contains(children, condPtr));
  REQUIRE(contains(children, iftPtr));
  REQUIRE(contains(children, iffPtr));

  // Test accept
  RecordPostPrint visitor;
  ternary->accept(&visitor);
  std::string expected[] = {"x", "y", "z", "(x?y:z)"};
  for (int i = 0; i < 4; i++) {
    REQUIRE(visitor.postPrintStrings[i] == expected[i]);
  }
}

TEST_CASE("ASTNodeTest: ASTArrayComprehension", "[ASTNode]") {
  auto num = std::make_unique<ASTVariableExpr>("x");
  auto val = std::make_unique<ASTVariableExpr>("y");

  auto numPtr = num.get();
  auto valPtr = val.get();

  auto comprehension = std::make_unique<ASTArrayComprehensionExpr>(std::move(num), std::move(val));

  // Test Print Method
  std::stringstream nodePrintStream;
  nodePrintStream << *comprehension;
  REQUIRE(nodePrintStream.str() == "[x of y]");

  // Test getters
  REQUIRE(numPtr == comprehension->getNum());
  REQUIRE(valPtr == comprehension->getVal());

  // Test getChildren
  auto children = comprehension->getChildren();
  REQUIRE(children.size() == 2);
  REQUIRE(contains(children, numPtr));
  REQUIRE(contains(children, valPtr));

  // Test accept
  RecordPostPrint visitor;
  comprehension->accept(&visitor);
  std::string expected[] = {"x", "y", "[x of y]"};
  for (int i = 0; i < 3; i++) {
      REQUIRE(visitor.postPrintStrings[i] == expected[i]);
  }
}

TEST_CASE("ASTNodeTest: ASTArrayLiteral", "[ASTNode]") {
  std::shared_ptr<ASTExpr> v1 = std::make_shared<ASTVariableExpr>("x");
  std::shared_ptr<ASTExpr> v2 = std::make_shared<ASTVariableExpr>("y");
  std::vector<std::shared_ptr<ASTExpr>> elems;
  elems.push_back(v1);
  elems.push_back(v2);

  std::vector<ASTExpr *> elemsPtr{v1.get(), v2.get()};

  auto literal = std::make_unique<ASTArrayLiteralExpr>(std::move(elems));

  // Test Print Method
  std::stringstream nodePrintStream;
  nodePrintStream << *literal;
  REQUIRE(nodePrintStream.str() == "[x, y]");

  // Test getters
  REQUIRE(elemsPtr == literal->getElems());

  // Test getChildren
  auto children = literal->getChildren();
  REQUIRE(children.size() == 2);
  REQUIRE(contains(children, elemsPtr[0]));
  REQUIRE(contains(children, elemsPtr[1]));

  // Test accept
  RecordPostPrint visitor;
  literal->accept(&visitor);
  std::string expected[] = {"x", "y", "[x, y]"};
  for (int i = 0; i < 3; i++) {
      REQUIRE(visitor.postPrintStrings[i] == expected[i]);
  }
}

TEST_CASE("ASTNodeTest: ASTLength", "[ASTNode]") {
  auto arr = std::make_unique<ASTVariableExpr>("x");

  auto arrPtr = arr.get();

  auto length = std::make_unique<ASTLengthExpr>(std::move(arr));

  // Test Print Method
  std::stringstream nodePrintStream;
  nodePrintStream << *length;
  REQUIRE(nodePrintStream.str() == "(#x)");

  // Test getters
  REQUIRE(arrPtr == length->getArr());

  // Test getChildren
  auto children = length->getChildren();
  REQUIRE(children.size() == 1);
  REQUIRE(contains(children, arrPtr));

  // Test accept
  RecordPostPrint visitor;
  length->accept(&visitor);
  std::string expected[] = {"x","(#x)"};
  for (int i = 0; i < 2; i++) {
      REQUIRE(visitor.postPrintStrings[i] == expected[i]);
  }
}

TEST_CASE("ASTNodeTest: ASTBooleanNot", "[ASTNode]") {
  auto val = std::make_unique<ASTVariableExpr>("x");

  auto valPtr = val.get();

  auto neg = std::make_unique<ASTBooleanNotExpr>(std::move(val));

  // Test Print Method
  std::stringstream nodePrintStream;
  nodePrintStream << *neg;
  REQUIRE(nodePrintStream.str() == "(not x)");

  // Test getters
  REQUIRE(valPtr == neg->getBool());

  // Test getChildren
  auto children = neg->getChildren();
  REQUIRE(children.size() == 1);
  REQUIRE(contains(children, valPtr));

  // Test accept
  RecordPostPrint visitor;
  neg->accept(&visitor);
  std::string expected[] = {"x","(not x)"};
  for (int i = 0; i < 2; i++) {
      REQUIRE(visitor.postPrintStrings[i] == expected[i]);
  }
}

TEST_CASE("ASTNodeTest: ASTBooleanFalse", "[ASTNode]") {
  auto b = std::make_unique<ASTBooleanExpr>(0);

  // Test Print Method
  std::stringstream nodePrintStream;
  nodePrintStream << *b;
  REQUIRE(nodePrintStream.str() == "0");

  // Test getters
  REQUIRE(b->getValue() == false);

  // Test getChildren
  auto children = b->getChildren();
  REQUIRE(children.size() == 0);

  // Test accept
  RecordPostPrint visitor;
  b->accept(&visitor);
  std::string expected[] = {"0"};
  for (int i = 0; i < 1; i++) {
      REQUIRE(visitor.postPrintStrings[i] == expected[i]);
  }
}

TEST_CASE("ASTNodeTest: ASTBooleanTrue", "[ASTNode]") {
  auto b = std::make_unique<ASTBooleanExpr>(1);

  // Test Print Method
  std::stringstream nodePrintStream;
  nodePrintStream << *b;
  REQUIRE(nodePrintStream.str() == "1");

  // Test getters
  REQUIRE(b->getValue() == true);

  // Test getChildren
  auto children = b->getChildren();
  REQUIRE(children.size() == 0);

  // Test accept
  RecordPostPrint visitor;
  b->accept(&visitor);
  std::string expected[] = {"1"};
  for (int i = 0; i < 1; i++) {
      REQUIRE(visitor.postPrintStrings[i] == expected[i]);
  }
}

TEST_CASE("ASTNodeTest: ASTSubscript", "[ASTNode]") {
  auto arr = std::make_unique<ASTVariableExpr>("x");
  auto index = std::make_unique<ASTVariableExpr>("y");

  auto arrPtr = arr.get();
  auto indexPtr = index.get();

  auto sub = std::make_unique<ASTSubscriptExpr>(std::move(arr), std::move(index));

  // Test Print Method
  std::stringstream nodePrintStream;
  nodePrintStream << *sub;
  REQUIRE(nodePrintStream.str() == "(x[y])");

  // Test getters
  REQUIRE(arrPtr == sub->getArr());
  REQUIRE(indexPtr == sub->getIndex());

  // Test getChildren
  auto children = sub->getChildren();
  REQUIRE(children.size() == 2);
  REQUIRE(contains(children, arrPtr));
  REQUIRE(contains(children, indexPtr));

  // Test accept
  RecordPostPrint visitor;
  sub->accept(&visitor);
  std::string expected[] = {"x","y","(x[y])"};
  for (int i = 0; i < 3; i++) {
      REQUIRE(visitor.postPrintStrings[i] == expected[i]);
  }
}

TEST_CASE("ASTNodeTest: ASTNegation", "[ASTNode]") {
  auto val = std::make_unique<ASTVariableExpr>("x");

  auto valPtr = val.get();

  auto neg = std::make_unique<ASTNegationExpr>(std::move(val));

  // Test Print Method
  std::stringstream nodePrintStream;
  nodePrintStream << *neg;
  REQUIRE(nodePrintStream.str() == "(-x)");

  // Test getters
  REQUIRE(valPtr == neg->getVar());

  // Test getChildren
  auto children = neg->getChildren();
  REQUIRE(children.size() == 1);
  REQUIRE(contains(children, valPtr));

  // Test accept
  RecordPostPrint visitor;
  neg->accept(&visitor);
  std::string expected[] = {"x","(-x)"};
  for (int i = 0; i < 2; i++) {
      REQUIRE(visitor.postPrintStrings[i] == expected[i]);
  }
}

TEST_CASE("ASTNodeTest: ASTDecrement", "[ASTNode]") {
  auto lhs = std::make_unique<ASTVariableExpr>("x");
  auto lhsValue = lhs.get();

  auto dec = std::make_unique<ASTDecrementStmt>(std::move(lhs));

  // Test Print Method
  std::stringstream nodePrintStream;
  nodePrintStream << *dec;
  REQUIRE(nodePrintStream.str() == "x--;");

  // Test getters
  REQUIRE(lhsValue == dec->getBody());

  // Test getChildren
  auto children = dec->getChildren();
  REQUIRE(children.size() == 1);
  REQUIRE(contains(children, lhsValue));

  // Test accept
  RecordPostPrint visitor;
  dec->accept(&visitor);
  std::string expected[] = {"x","x--;"};
  for (int i = 0; i < 2; i++) {
      REQUIRE(visitor.postPrintStrings[i] == expected[i]);
  }
}

TEST_CASE("ASTNodeTest: ASTIncrement", "[ASTNode]") {
  auto lhs = std::make_unique<ASTVariableExpr>("x");
  auto lhsValue = lhs.get();

  auto dec = std::make_unique<ASTIncrementStmt>(std::move(lhs));

  // Test Print Method
  std::stringstream nodePrintStream;
  nodePrintStream << *dec;
  REQUIRE(nodePrintStream.str() == "x++;");

  // Test getters
  REQUIRE(lhsValue == dec->getBody());

  // Test getChildren
  auto children = dec->getChildren();
  REQUIRE(children.size() == 1);
  REQUIRE(contains(children, lhsValue));

  // Test accept
  RecordPostPrint visitor;
  dec->accept(&visitor);
  std::string expected[] = {"x","x++;"};
  for (int i = 0; i < 2; i++) {
      REQUIRE(visitor.postPrintStrings[i] == expected[i]);
  }
}

TEST_CASE("ASTNodeTest: ASTFor", "[ASTNode]") {
  auto v = std::make_unique<ASTVariableExpr>("x");
  auto l = std::make_unique<ASTNumberExpr>(1);
  auto u = std::make_unique<ASTNumberExpr>(2);
  auto b = std::make_unique<ASTNumberExpr>(1);
  auto vv = std::make_unique<ASTVariableExpr>("x");
  auto s = std::make_unique<ASTIncrementStmt>(move(vv));

  auto vptr = v.get();
  auto lptr = l.get();
  auto uptr = u.get();
  auto bptr = b.get();
  auto sptr = s.get();

  auto f = std::make_unique<ASTForStmt>(std::move(v),std::move(l),std::move(u),std::move(b),std::move(s));

  REQUIRE(f->getVar() == vptr);
  REQUIRE(f->getStart() == lptr);
  REQUIRE(f->getEnd() == uptr);
  REQUIRE(f->getIncrement() == bptr);
  REQUIRE(f->getStatement() == sptr);


  auto children = f->getChildren();
  REQUIRE(children.size() == 5);
  REQUIRE(contains(children, vptr));
  REQUIRE(contains(children, lptr));
  REQUIRE(contains(children, uptr));
  REQUIRE(contains(children, bptr));
  REQUIRE(contains(children, sptr));


  RecordPostPrint visitor;
  f->accept(&visitor);
  std::string expected[] = { "x", "1", "2", "1", "x", "x++;", "for (x : 1 .. 2 by 1) x++;"};
  for (int i=0; i < 7; i++) {
    REQUIRE(visitor.postPrintStrings[i] == expected[i]);
  }
}

TEST_CASE("ASTNodeTest: ASTForEach", "[ASTNode]") {
  auto v = std::make_unique<ASTVariableExpr>("x");
  auto a = std::make_unique<ASTVariableExpr>("y");
  auto vv = std::make_unique<ASTVariableExpr>("x");
  auto s = std::make_unique<ASTIncrementStmt>(move(vv));
  
  auto vptr = v.get();
  auto aptr = a.get();
  auto sptr = s.get();

  auto f = std::make_unique<ASTForEachStmt>(std::move(v),std::move(a),std::move(s));

  REQUIRE(f->getElement() == vptr);
  REQUIRE(f->getIterable() == aptr);
  REQUIRE(f->getBody() == sptr);

  auto children = f->getChildren();
  REQUIRE(children.size() == 3);
  REQUIRE(contains(children, vptr));
  REQUIRE(contains(children, aptr));
  REQUIRE(contains(children, sptr));

  
  RecordPostPrint visitor;
  f->accept(&visitor);
  std::string expected[] = { "x", "y", "x", "x++;", "for (x : y) x++;"};
  for (int i=0; i < 5; i++) {
    REQUIRE(visitor.postPrintStrings[i] == expected[i]);
  }
}
