// Westley Hennigh

// ExpressionTemplates.cpp : These are just instantiations of the variables needed. Use the
//                           variables in ascending order (don't use _2 or _p2 before using
//                           _1 or _p1, for instance)

#include "ExpressionTemplates.hpp"


namespace E
{

  // Variable instantiations
  Variable<Var1> _1;
  Variable<Var2> _2;
  Variable<Var3> _3;

  PointerVariable<Var1> _p1;
  PointerVariable<Var2> _p2;
  PointerVariable<Var3> _p3;

}
