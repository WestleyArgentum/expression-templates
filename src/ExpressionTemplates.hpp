// Westley Hennigh

// ExpressionTemplates.hpp : This is a file containing c++ expression templates that we can use
//                           to effectively get lambda functions.

#pragma once

namespace E
{

  // Expression --------------------------
  template < class expr >
  class Expression //: public Expr
  {
  public:
    Expression ( expr& xp_ ) : xp( xp_ )  {}

    template < typename var_type >
    var_type operator () ( var_type val1 )  { return xp( val1 ); }

    template < typename var_type >
    var_type operator () ( var_type val1, var_type val2 )  { return xp( val1, val2 ); }

    template < typename var_type >
    var_type operator () ( var_type val1, var_type val2, var_type val3 )  { return xp(val1, val2, val3); }

  private:
    expr xp;  // must have overloaded operator ()

  };


  // Variable (leaf) ---------------------

  // Now were going to HAVE to use the variables in order. No (2 + Var3)!
  struct Var1 {};
  struct Var2 {};
  struct Var3 {};

  template < class var_num >
  class Variable
  {
  };


  template <>
  class Variable< Var1 >
  {
  public:
    template < typename var_type >
    var_type& operator () ( var_type& val1 )
    {
      return val1;
    }

    template < typename var_type >
    var_type& operator () ( var_type& val1, var_type& val2 )
    { 
      return val1;
    }

    template < typename var_type >
    var_type& operator () ( var_type& val1, var_type& val2, var_type& val3 )
    {
      return val1;
    }

    template < typename var_type, typename ret >
    Variable< Var1 >& call ( ret (var_type::*fn)() )
    {
      return *this;
    }

    template < typename var_type, typename ret, typename p1 >
    Variable< Var1 >& call ( ret (var_type::*fn)(p1), p1 param1 )
    {
      return *this;
    }

  };


  template <>
  class Variable< Var2 >
  {
  public:
    template < typename var_type >
    var_type operator () ( var_type& val1, var_type& val2 )
    {
      return val2;
    }

    template < typename var_type >
    var_type operator () ( var_type& val1, var_type& val2, var_type& val3 )
    {
      return val2;
    }

    template < typename var_type, typename ret >
    Variable< Var2 >& call ( ret (var_type::*fn)() )
    {
      return *this;
    }

  };


  template <>
  class Variable< Var3 >
  {
  public:
    template < typename var_type >
    var_type operator () ( var_type& val1, var_type& val2, var_type& val3 )
    {
      return val3;
    }

    template < typename var_type, typename ret >
    Variable< Var3 >& call ( ret (var_type::*fn)() )
    {
      return *this;
    }

  };


  // Variable instantiations
  extern Variable<Var1> _1;
  extern Variable<Var2> _2;
  extern Variable<Var3> _3;


  // Pointer Variable (leaf) ---------------------

  template < class var_num >
  class PointerVariable
  {
  };


  template <>
  class PointerVariable< Var1 >
  {
  public:
    template < typename var_type >
    var_type operator () ( var_type& val1 )
    {
      return val1;
    }

    template < typename var_type >
    var_type operator () ( var_type& val1, var_type& val2 )
    {
      return val1;
    }

    template < typename var_type >
    var_type operator () ( var_type& val1, var_type& val2, var_type& val3 )
    {
      return val1;
    }

    template < typename var_type, typename ret >
    PointerVariable< Var1 >& call ( ret (var_type::*fn)() )
    {
      return *this;
    }

  };

  template <>
  class PointerVariable< Var2 >
  {
  public:
    template < typename var_type >
    var_type operator () ( var_type* val1, var_type* val2 )
    {
      return *val2;
    }

    template < typename var_type >
    var_type operator () ( var_type* val1, var_type* val2, var_type* val3 )
    {
      return *val2;
    }

  };

  template <>
  class PointerVariable< Var3 >
  {
  public:
    template < typename var_type >
    var_type operator () ( var_type* val1, var_type* val2, var_type* val3 )
    {
      return *val3;
    }

  };


  // Variable instantiations
  extern PointerVariable<Var1> _p1;
  extern PointerVariable<Var2> _p2;
  extern PointerVariable<Var3> _p3;


  // Constant (leaf) ---------------------
  template < typename const_type >
  class Constant
  {
  public:
    Constant ( const_type val ) : myval( val )
    {;}

    template < typename var_type >
    const_type operator () ( var_type& )
    {
      return myval;
    }

    template < typename var_type >
    const_type operator () ( var_type&, var_type& )
    {
      return myval;
    }

    template < typename var_type >
    const_type operator () ( var_type&, var_type&, var_type& )
    {
      return myval;
    }

  private:
    const_type myval;

  };


  // Binary math functions ---------------
  struct add
  {
    template < typename type >
    static type apply ( type lhs, type rhs )  { return lhs + rhs; }
  };

  struct subtract
  {
    template < typename type >
    static type apply ( type lhs, type rhs )  { return lhs - rhs; }
  };

  struct multiply
  {
    template < typename type >
    static type apply ( type lhs, type rhs )  { return lhs * rhs; }
  };

  struct divide
  {
    template < typename type >
    static type apply ( type lhs, type rhs )  { return lhs / rhs; }
  };


  // Complex (non-leaf) ------------------
  template < class xp1, class xp2, class oper >
  class Complex
  {
  public:
    Complex ( Expression<xp1> left_, Expression<xp2> right_ )
      : left( left_ ), right( right_ )
    {;}

    template < typename var_type >
    var_type operator () ( var_type& val1 )  { return oper::apply( left( val1 ), right( val1 ) ); }

    template < typename var_type >
    var_type operator () ( var_type& val1, var_type& val2 )  { return oper::apply( left( val1, val2 ), right( val1, val2 ) ); }

    template < typename var_type >
    var_type operator () ( var_type& val1, var_type& val2, var_type& val3 )  { return oper::apply( left( val1, val2, val3 ), right( val1, val2, val3 ) ); }

  private:
    Expression<xp1> left;
    Expression<xp2> right;

  };


  // Enable_if and conditions
  template < typename T, typename R, bool b = T::value >
  struct Enable_if {};

  template < typename T, typename R >
  struct Enable_if < T, R, true >
  {
    typedef R type;
  };

  template < typename T1, typename T2 >
  struct IsNotPOD
  {
    enum { value = true };
  };

  template < typename T >
  struct IsPOD
  {
    enum { value = false };
  };

  // Specializations for basic types -----
  template < typename T1 >
  struct IsNotPOD < T1, int > { enum { value = false }; };

  template < typename T1 >
  struct IsNotPOD < T1, unsigned > { enum { value = false }; };

  template < typename T1 >
  struct IsNotPOD < T1, double > { enum { value = false }; };

  template < typename T1 >
  struct IsNotPOD < T1, float > { enum { value = false }; };


  template < typename T2 >
  struct IsNotPOD < int, T2 > { enum { value = false }; };

  template < typename T2 >
  struct IsNotPOD < unsigned, T2 > { enum { value = false }; };

  template < typename T2 >
  struct IsNotPOD < double, T2 > { enum { value = false }; };

  template < typename T2 >
  struct IsNotPOD < float, T2 > { enum { value = false }; };



  template <>
  struct IsPOD < int > { enum { value = true }; };

  template <>
  struct IsPOD < unsigned > { enum { value = true }; };

  template <>
  struct IsPOD < double > { enum { value = true }; };

  template <>
  struct IsPOD < float > { enum { value = true }; };



  // Operators (exp to exp) --------------
  template<class xp1, class xp2>
  typename Enable_if <
                       IsNotPOD< xp1, xp2 >,
                       Expression< Complex< Expression<xp1>, Expression<xp2>, add > >
                     >::type
   operator + ( xp1 lhs, xp2 rhs )
  {
    typedef Complex< Expression<xp1>, Expression<xp2>, add > ExprType;
    return Expression<ExprType>( ExprType( Expression<xp1>(lhs), Expression<xp2>(rhs) ) );
  }

  // -----

  template<class xp1, class xp2>
  typename Enable_if <
                      IsNotPOD< xp1, xp2 >,
                      Expression< Complex< Expression<xp1>, Expression<xp2>, subtract > >
                     >::type
  operator - ( xp1 lhs, xp2 rhs )
  {
    typedef Complex< Expression<xp1>, Expression<xp2>, subtract > ExprType;
    return Expression<ExprType>( ExprType( Expression<xp1>(lhs), Expression<xp2>(rhs) ) );
  }

  // -----

  template<class xp1, class xp2>
  typename Enable_if <
                      IsNotPOD< xp1, xp2 >,
                      Expression< Complex< Expression<xp1>, Expression<xp2>, multiply > >
                     >::type
  operator * ( xp1 lhs, xp2 rhs )
  {
    typedef Complex< Expression<xp1>, Expression<xp2>, multiply > ExprType;
    return Expression<ExprType>( ExprType( Expression<xp1>(lhs), Expression<xp2>(rhs) ) );
  }

  // -----

  template<class xp1, class xp2>
  typename Enable_if <
                      IsNotPOD< xp1, xp2 >,
                      Expression< Complex< Expression<xp1>, Expression<xp2>, divide > >
                     >::type
  operator / ( xp1 lhs, xp2 rhs )
  {
    typedef Complex< Expression<xp1>, Expression<xp2>, divide > ExprType;
    return Expression<ExprType>( ExprType( Expression<xp1>(lhs), Expression<xp2>(rhs) ) );
  }


  //template<class xp1, class xp2>
  //Expression< Complex< Expression<xp1>, Expression<xp2>, subtract > > operator - (xp1 lhs, xp2 rhs)
  //{
  //  typedef Complex< Expression<xp1>, Expression<xp2>, subtract > ExprType;
  //  return Expression<ExprType>( ExprType( Expression<xp1>(lhs), Expression<xp2>(rhs) ) );
  //}
  //
  //template<class xp1, class xp2>
  //Expression< Complex< Expression<xp1>, Expression<xp2>, multiply > > operator * (xp1 lhs, xp2 rhs)
  //{
  //  typedef Complex< Expression<xp1>, Expression<xp2>, multiply > ExprType;
  //  return Expression<ExprType>( ExprType( Expression<xp1>(lhs), Expression<xp2>(rhs) ) );
  //}
  //
  //template<class xp1, class xp2>
  //Expression< Complex< Expression<xp1>, Expression<xp2>, divide > > operator / (xp1 lhs, xp2 rhs)
  //{
  //  typedef Complex< Expression<xp1>, Expression<xp2>, divide > ExprType;
  //  return Expression<ExprType>( ExprType( Expression<xp1>(lhs), Expression<xp2>(rhs) ) );
  //}


  // Operators (exp to basic) ------------
  template<class xp1, typename const_type>
  typename Enable_if <
                       IsPOD< const_type >,
                       Expression< Complex< Expression<xp1>, Expression< Constant<const_type> >, add > >
                     >::type
  operator + ( xp1 lhs, const_type rhs )
  {
    typedef Complex< Expression<xp1>, Expression< Constant<const_type> >, add > XpType;
    return Expression<XpType>( XpType( Expression<xp1>(lhs), Expression< Constant<const_type> >( Constant<const_type>(rhs) ) ) );
  }

  template<class xp1, typename const_type>
  typename Enable_if <
                       IsPOD< const_type >,
                       Expression< Complex< Expression<xp1>, Expression< Constant<const_type> >, add > >
                     >::type
  operator + ( const_type rhs, xp1 lhs )
  {
    typedef Complex< Expression<xp1>, Expression< Constant<const_type> >, add > XpType;
    return Expression<XpType>( XpType( Expression<xp1>(lhs), Expression< Constant<const_type> >( Constant<const_type>(rhs) ) ) );
  }

  // -----

  template<class xp1, typename const_type>
  typename Enable_if <
                      IsPOD< const_type >,
                      Expression< Complex< Expression<xp1>, Expression< Constant<const_type> >, subtract > >
                     >::type
  operator - ( xp1 lhs, const_type rhs )
  {
    typedef Complex< Expression<xp1>, Expression< Constant<const_type> >, subtract > XpType;
    return Expression<XpType>( XpType( Expression<xp1>(lhs), Expression< Constant<const_type> >( Constant<const_type>(rhs) ) ) );
  }

  template<class xp1, typename const_type>
  typename Enable_if <
                      IsPOD< const_type >,
                      Expression< Complex< Expression<xp1>, Expression< Constant<const_type> >, subtract > >
                     >::type
  operator - ( const_type rhs, xp1 lhs )
  {
    typedef Complex< Expression<xp1>, Expression< Constant<const_type> >, subtract > XpType;
    return Expression<XpType>( XpType( Expression<xp1>(lhs), Expression< Constant<const_type> >( Constant<const_type>(rhs) ) ) );
  }

  // -----

  template<class xp1, typename const_type>
  typename Enable_if <
                      IsPOD< const_type >,
                      Expression< Complex< Expression<xp1>, Expression< Constant<const_type> >, multiply > >
                     >::type
  operator * ( xp1 lhs, const_type rhs )
  {
    typedef Complex< Expression<xp1>, Expression< Constant<const_type> >, multiply > XpType;
    return Expression<XpType>( XpType( Expression<xp1>(lhs), Expression< Constant<const_type> >( Constant<const_type>(rhs) ) ) );
  }

  template<class xp1, typename const_type>
  typename Enable_if <
                      IsPOD< const_type >,
                      Expression< Complex< Expression<xp1>, Expression< Constant<const_type> >, multiply > >
                     >::type
  operator * ( const_type rhs, xp1 lhs )
  {
    typedef Complex< Expression<xp1>, Expression< Constant<const_type> >, multiply > XpType;
    return Expression<XpType>( XpType( Expression<xp1>(lhs), Expression< Constant<const_type> >( Constant<const_type>(rhs) ) ) );
  }

  // -----

  template<class xp1, typename const_type>
  typename Enable_if <
                      IsPOD< const_type >,
                      Expression< Complex< Expression<xp1>, Expression< Constant<const_type> >, divide > >
                     >::type
  operator / ( xp1 lhs, const_type rhs )
  {
    typedef Complex< Expression<xp1>, Expression< Constant<const_type> >, divide > XpType;
    return Expression<XpType>( XpType( Expression<xp1>(lhs), Expression< Constant<const_type> >( Constant<const_type>(rhs) ) ) );
  }

  template<class xp1, typename const_type>
  typename Enable_if <
                      IsPOD< const_type >,
                      Expression< Complex< Expression<xp1>, Expression< Constant<const_type> >, divide > >
                     >::type
  operator / ( const_type rhs, xp1 lhs )
  {
    typedef Complex< Expression<xp1>, Expression< Constant<const_type> >, divide > XpType;
    return Expression<XpType>( XpType( Expression<xp1>(lhs), Expression< Constant<const_type> >( Constant<const_type>(rhs) ) ) );
  }

}