#include "ExceptionContainsWhat.h"
#include "FrontEnd.h"
#include "ParseError.h"
#include "ParserHelper.h"

#include <catch2/catch_test_macros.hpp>

//TESTS FOR COMPARISON OPERATORS (<,<=, >=)

TEST_CASE("SIP Parser: comparison operators var against var", "[SIP Parser]") {
    std::stringstream stream;
    stream << R"(
	fun() {
		var x, y, z;
		if (x < y) {
			while(x >= 0) {
				x = x - 1;
			}
		}
		if(z <= y){
			y = y + 1;
		}
		return x;
	}
    )";
    REQUIRE(ParserHelper::is_parsable(stream));
}

TEST_CASE("SIP Parser: comparison operators var against number", "[SIP Parser]") {
    std::stringstream stream;
    stream << R"(
	fun() {
		var x, y, z;
		if(x >= 10) {
			while(y < 12) {
				y = y - 1;
			}
		}
		if(10 <= z){
			z = z + 1;
		}
		return y;
	}
    )";
    REQUIRE(ParserHelper::is_parsable(stream));
}

TEST_CASE("SIP Parser: illegal comparison operator format #1", "[SIP Parser]") {
    std::stringstream stream;
    stream << R"(
	fun() {
		var x, y;
		if( x =< y) {
			x = 4;
		}
		return y;
	}
    )";
    REQUIRE_FALSE(ParserHelper::is_parsable(stream));
}

TEST_CASE("SIP Parser: illegal comparison operator format #2", "[SIP Parser]") {
    std::stringstream stream;
    stream << R"(
	fun() {
		var x, y;
		if(x >< y){
			y = y + 1;
		}
		return y;
	}
    )";
    REQUIRE_FALSE(ParserHelper::is_parsable(stream));
}

TEST_CASE("SIP Parser: illegal comparison operator without value on one side", "[SIP Parser]") {
    std::stringstream stream;
    stream << R"(
	fun() {
		var x;
		if( < x) {
			x = x - 1;
		}
		return x;
	}
    )";
    REQUIRE_FALSE(ParserHelper::is_parsable(stream));
}

//MODULUS OPERATOR TESTS

TEST_CASE("SIP Parser: usage of modulus between vars", "[SIP Parser]") {
    std::stringstream stream;
    stream << R"(
	fun() {
		var x,y,z;
		z = x % y;
		return z;
	}
    )";
    REQUIRE(ParserHelper::is_parsable(stream));
}

TEST_CASE("SIP Parser: usage of modulus between var and literal", "[SIP Parser]") {
    std::stringstream stream;
    stream << R"(
	fun() {
		var x,y;
		x = y % 10;
		y = 467 % x;
		return y;
	}
    )";
    REQUIRE(ParserHelper::is_parsable(stream));
}

TEST_CASE("SIP Parser: misloaded modulus", "[SIP Parser]") {
    std::stringstream stream;
    stream << R"(
	fun() {
		var x;
		return x % ;
	}
    )";
    REQUIRE_FALSE(ParserHelper::is_parsable(stream));
}


TEST_CASE("SIP Parser: modulus operator precedence", "[SIP Parser]") {
    std::stringstream stream;
    stream << R"(main() { return 1 * 2 % 3 + 4;	})";
    std::string expected = "(expr (expr (expr (expr 1) * (expr 2)) % (expr 3)) + (expr 4))";
    std::string tree = ParserHelper::parsetree(stream);
    REQUIRE(tree.find(expected) != std::string::npos);
}


//BOOLEAN DECLERATION AND OPERATORS

TEST_CASE("SIP Parser: boolean decleration", "[SIP Parser]") {
    std::stringstream stream;
    stream << R"(
	fun() {
		var x,y,z;
		x = TRUE;
		y = false;
		z = fAlSe;
		return z;
	}
    )";
    REQUIRE(ParserHelper::is_parsable(stream));
}

TEST_CASE("SIP Parser: boolean operator usage", "[SIP Parser]") {
    std::stringstream stream;
    stream << R"(
	fun() {
		var x,y,z;
		x = y or z;
		z = x and y;
		y = not x;
		return y;
	}
    )";
    REQUIRE(ParserHelper::is_parsable(stream));
}

TEST_CASE("SIP Parser: boolean operator precendence", "[SIP Parser]") {
    std::stringstream stream;
    stream << R"(
	fun() {
		var x,y,z;
		return not x and y or z;
	}
    )";
    std::string expected = "(expr (expr (expr not (expr x)) and (expr y)) or (expr z))";
    std::string tree = ParserHelper::parsetree(stream);
    REQUIRE(tree.find(expected) != std::string::npos);

}

TEST_CASE("SIP Parser: boolean literal in function decleration", "[SIP Parser]") {
    std::stringstream stream;
    stream << R"(
	fun(true) {
		return 0;
	}
    )";
    REQUIRE_FALSE(ParserHelper::is_parsable(stream));
}

TEST_CASE("SIP Parser: boolean operator as return value", "[SIP Parser]") {
    std::stringstream stream;
    stream << R"(
	fun(x) {
		return not;
	}
    )";
    REQUIRE_FALSE(ParserHelper::is_parsable(stream));
}


//TERNARY OPERATOR TESTS

TEST_CASE("SIP Parser: simple ternary expression", "[SIP Parser]") {
    std::stringstream stream;
    stream << R"(
        fun(x,y,z) {
		return x ? x : y;
	}
    )";
    REQUIRE(ParserHelper::is_parsable(stream));
}

TEST_CASE("SIP Parser: nested ternary expression operator precedence", "[SIP Parser]") {
    std::stringstream stream;
    stream << R"(
        fun(x,y,z) {
		return x ? x : y ? z : x;
        }
    )";
    std::string expected = "(expr (expr x) ? (expr x) : (expr (expr y) ? (expr z) : (expr x)))";
    std::string tree = ParserHelper::parsetree(stream);
    REQUIRE(tree.find(expected) != std::string::npos);
}

TEST_CASE("SIP Parser: malformed ternary expression", "[SIP Parser]") {
   std::stringstream stream;
   stream << R"(
	fun(x,y) {
		return x?:y;
	}
    )";
    REQUIRE_FALSE(ParserHelper::is_parsable(stream));
}

//FOR LOOP TESTS

TEST_CASE("SIP Parser: simple for loop", "[SIP Parser]") {
    std::stringstream stream;
    stream << R"(
	fun(x,y,z) {
		var w;
		for (w : y .. z by x) {
			x=input;
  		}
 		return x;
	}
    )";
    REQUIRE(ParserHelper::is_parsable(stream));
}


TEST_CASE("SIP Parser: simple for loop without by", "[SIP Parser]") {
    std::stringstream stream;
    stream << R"(
	fun(x,y,z) {
		var w;
		for (w : y .. z) {
		x=input;
		}
		return x;
	}
    )";
    REQUIRE(ParserHelper::is_parsable(stream));
}


TEST_CASE("SIP Parser: simple foreach loop", "[SIP Parser]") {
    std::stringstream stream;
    stream << R"(
	fun(x,y,z) {
		var w;
		for (w : y)
			x=input;
		return x;
	}
    )";
    REQUIRE(ParserHelper::is_parsable(stream));
}

TEST_CASE("SIP Parser: mishmashed for loop", "[SIP Parser]") {
    std::stringstream stream;
    stream << R"(
	fun(x,y,z) {
		for (x:z by z) x=input;
		return x;
	}
    )";
    REQUIRE_FALSE(ParserHelper::is_parsable(stream));
}

//INCREMENT AND DECREMENT TESTS

TEST_CASE("SIP Parser: simple increment and decrement", "[SIP Parser]") {
    std::stringstream stream;
    stream << R"(
        fun(x,y) {
                x++;
		y--;
		return x;
        }
    )";
    REQUIRE(ParserHelper::is_parsable(stream));
}

TEST_CASE("SIP Parser: malformed increment/decrement", "[SIP Parser]") {
    std::stringstream stream;
    stream << R"(
        fun(x,y,z) {
                return x+-;
        }
    )";
    REQUIRE_FALSE(ParserHelper::is_parsable(stream));
}

TEST_CASE("SIP Parser: operator precedence with increment statement", "[SIP Parser]") {
    std::stringstream stream;
    stream << R"(
	fun(x,y,z) {
  		x?y:z--;
		return x;
	}
    )";
    std::string expected = "(decStmt (expr (expr x) ? (expr y) : (expr z)) - - ;)";
    std::string tree = ParserHelper::parsetree(stream);
    REQUIRE(tree.find(expected) != std::string::npos);
}

//ARRAY TESTS

TEST_CASE("SIP Parser: simple array decleration with literals", "[SIP Parser]") {
    std::stringstream stream;
    stream << R"(
	fun(x,y,z) {
		return [x,y,z];
	}
    )";
    REQUIRE(ParserHelper::is_parsable(stream));
}

TEST_CASE("SIP Parser: simple array decleration with of", "[SIP Parser]") {
    std::stringstream stream;
    stream << R"(
        fun(x,y,z) {
                return [x of z];
        }
    )";
    REQUIRE(ParserHelper::is_parsable(stream));
}

TEST_CASE("SIP Parser: simple array decleration with ternary operation", "[SIP Parser]") {
    std::stringstream stream;
    stream << R"(
	fun(x,y,z) {
		return [4+3 of z ? x : y];
	}
    )";
    std::string expected = "(expr (arrayDefExpr [ (expr (expr 4) + (expr 3)) of (expr (expr z) ? (expr x) : (expr y)) ]))";
    std::string tree = ParserHelper::parsetree(stream);
    REQUIRE(tree.find(expected) != std::string::npos);
}

TEST_CASE("SIP Parser: simple array length", "[SIP Parser]") {
    std::stringstream stream;
    stream << R"(
        fun(x,y,z) {
                return #x;
        }
    )";
    REQUIRE(ParserHelper::is_parsable(stream));
}

TEST_CASE("SIP Parser: array length on array literal", "[SIP Parser]") {
    std::stringstream stream;
    stream << R"(
        fun(x,y,z) {
                return #[x,y,z];
        }
    )";
    REQUIRE(ParserHelper::is_parsable(stream));
}

TEST_CASE("SIP Parser: array length with array literal and operator precedence", "[SIP Parser]") {
    std::stringstream stream;
    stream << R"(
        fun(x,y,z) {
                return #[] == 0;
        }
    )";
    std::string expected = "(expr (expr # (expr (arrayDefExpr [ ]))) == (expr 0))";
    std::string tree = ParserHelper::parsetree(stream);
    REQUIRE(tree.find(expected) != std::string::npos);
}

TEST_CASE("SIP Parser: array length on bad array literal", "[SIP Parser]") {
    std::stringstream stream;
    stream << R"(
        fun(x,y,z) {
                return #[x,y,z,];
        }
    )";
    REQUIRE_FALSE(ParserHelper::is_parsable(stream));
}

TEST_CASE("SIP Parser: simple array access", "[SIP Parser]") {
    std::stringstream stream;
    stream << R"(
        fun(x,y,z) {
                return x[y];
        }
    )";
    REQUIRE(ParserHelper::is_parsable(stream));
}

TEST_CASE("SIP Parser: array access in arrays of arrays", "[SIP Parser]") {
    std::stringstream stream;
    stream << R"(
        fun(x,y,z) {
                return [[0]][0][0];
        }
    )";
    std::string expected = "(expr (expr (expr (arrayDefExpr [ (expr (arrayDefExpr [ (expr 0) ])) ])) [ (expr 0) ]) [ (expr 0) ])";
    std::string tree = ParserHelper::parsetree(stream);
    REQUIRE(tree.find(expected) != std::string::npos);
}

//NEGATIVE EXPRESSION TESTS

TEST_CASE("SIP Parser: simple negative expression", "[SIP Parser]") {
    std::stringstream stream;
    stream << R"(
        fun(x,y,z) {
                return -x;
        }
    )";
    REQUIRE(ParserHelper::is_parsable(stream));
}

TEST_CASE("SIP Parser: negative expression inside ternary expression", "[SIP Parser]") {
    std::stringstream stream;
    stream << R"(
        fun(x,y,z) {
                z=x?-y:-z;
		return -x;
        }
    )";
    REQUIRE(ParserHelper::is_parsable(stream));
}

TEST_CASE("SIP Parser: nested negative expression", "[SIP Parser]") {
    std::stringstream stream;
    stream << R"(
        fun(x,y,z) {
                y = ---x;
		return y;
        }
    )";
    std::string expected = "(expr - (expr - (expr - (expr x))))";
    std::string tree = ParserHelper::parsetree(stream);
    REQUIRE(tree.find(expected) != std::string::npos);
}
