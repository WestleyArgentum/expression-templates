
#include <iostream>
#include <algorithm>
#include <vector>

#include "ExpressionTemplates.hpp"

// Have you ever been in the middle of writing a for_each or transform function call and realized that
// you were going to have make a little functor somewhere to perform the work you needed done?
// It's kind of frustrating because it undermines the readability that you get from using the standard
// algorithms.

// Expression templates help with that problem by allowing you to write simple, clean expressions
// like X * 3 in c++. They are sort of a step towards lamda functions.

// Basically what happens is that you provide some "variables" (which are templated structures that will
// stand in an expression until you provide data to evaluate said expression) and you set up some operators
// like * and + that take in variables and basic types and then output templated "expressions" (which have
// an overloaded () operator).

// You are trying to build a sort of tree out of an expression that someone writes. If a user writes (X + 3) * 4
// you want to make an expression out of the X and 3 and then make an expression out of the (X + 3) and the 4.
// When you go to evaluate this expression you will pass in a value for X and the (X + 3) branch will be evaluated
// and then (X + 3) * 4 branch will be evaluated, leaving you with the result of the whole operation.

// NOTE: This implementation is not as far as these templates can be taken. I have stripped out, for instance,
//       the ability to write expressions that include calls to member functions (mostly because the function
//       binding I was using was very slow and quite bulky). Also, I have not found a way to wrap up compiler
//       generated expressions (think huge template types) which is a big hurdle to actually getting lamda functions.

// ALSO: Just go use a compiler that supports the new standard haha, lamda functions are free now.


int main ( void )
{
  using namespace E;

  // observe:
  std::cout << "X + 3 = " << (_1 + 3)( 10 ) << " where X is 10" << std::endl;
  //                          ^^^^^^ expression compiles into a functor
  //                                  ^^^^ we give that functor 10 and it evaluates the expression and produces the result

  // -------
  std::vector<int> ints( 10 );
  for ( unsigned i = 0; i < 5; ++i )
      ints[i] = i;

  std::vector<int> results( 10 );

  std::transform( ints.begin(), ints.end(), results.begin(), ( _1 * 2 + (3 + _1) ) );

  std::cout << std::endl << "expression X * 2 + (3 + X)" << std::endl << "preformed on vector:" << std::endl;

  std::cout << ints[0];
  for ( unsigned i = 1; i < 5; ++i )
      std::cout << "," << ints[i];

  std::cout << std::endl << std::endl << "yeilds:" << std::endl;
  std::cout << results[0];
  for ( unsigned i = 1; i < 5; ++i )
      std::cout << "," << results[i];



  std::cout << std::endl << std::endl << "also works with up to 3 variables" << std::endl;
  std::cout << "(X + 1) - (Y * 3) + Z = " << ((_1 + 1) - (_2 * 3) + _3)( 3, 5, 4 ) << " where X is 3, Y is 5, and Z is 4";

  return 0;
}
