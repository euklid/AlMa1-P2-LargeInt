// largeint.C (Implementation of class LargeInt)

#include <cmath>
#include <limits>
#include "largeint.h"

LargeInt::basetype LargeInt::power_of_ten(const basetype n)
{
      basetype result = 1;
      for (basetype i = 1; i <= n; ++i) result *= 10;
      return result;
}


const LargeInt::basetype LargeInt::logbasis = std::floor(std::log10(std::sqrt(
                                         std::numeric_limits<basetype>::max()) / 2));  

const LargeInt::basetype LargeInt::basis = power_of_ten(logbasis);                  


LargeInt::LargeInt(inputtype i) : _negative(i < 0), _v(1,0)  
{                                         // constructor, calls constructor of vector
      basetype carry = std::abs(i);
      _v[0] = carry % basis;
      carry = carry / basis;
      while (carry > 0)
      {
            _v.push_back(carry % basis);
            carry = carry / basis;
      }
}            


LargeInt::LargeInt() : _negative(false), _v(0)    
{}                                         // default constructor, internal use only

std::string LargeInt::decimal()            // returns decimal representation in string
{
      std::string s = (_negative)? "-" : "";  // conditional asssigment
      bool write = false;                     // do not write leading zeros
      for (size_t i = _v.size(); i > 0; --i)
      {
            basetype n = _v[i-1];
            basetype b = basis / 10;
            while (b > 0)
            {
                  basetype z = n / b;
                  if ((z > 0) or ((b == 1) and (i == 1))) write = true;
                  if (write) s = s + char(z+48);
                  n = n % b;
                  b = b / 10;
            }
            write = true;
      }
      return s;
}


bool LargeInt::operator<(const LargeInt& arg) const      // checks if smaller than arg
{                                             
     if (_negative != arg._negative)
     {
           return _negative;
     }
     else
     {
           return (((not _negative) and (abs_smaller(arg) == 1)) or
                   (_negative and (abs_smaller(arg) == -1)));
     }
}


int LargeInt::abs_smaller(const LargeInt& arg) const   // checks if absolute value is 
{                                                      // smaller (result 1) than, 
     if (_v.size() < arg._v.size()) return 1;          // greater than (result -1), or
     if (_v.size() > arg._v.size()) return -1;         // equal to (result 0) 
     for (size_t i = _v.size(); i >= 1; --i)           // the absolute value of arg
     {
           if (_v[i-1] < arg._v[i-1]) return 1;
           if (_v[i-1] > arg._v[i-1]) return -1;
     }
     return 0;
}            


LargeInt LargeInt::add_abs_values(const LargeInt& arg) const    // add absolute values
{
      basetype carry = 0;
      basetype sum = 0;
      LargeInt result;
      for (size_t i = 0; (i < _v.size()) or (i < arg._v.size()); ++i)
      {
            sum = carry;
            if (i < arg._v.size()) sum += arg._v[i];
            if (i < _v.size())     sum += _v[i];
            result._v.push_back(sum % basis);
            carry = sum / basis;
      }
      if (carry > 0) result._v.push_back(carry);
      return result;
}


LargeInt LargeInt::sub_abs_values(const LargeInt& arg) const 
{                                                          // subtract absolute values
      basetype carry = 1;                                  // result is ||this|-|arg||
      basetype sum = 0;
      LargeInt result;
      if (abs_smaller(arg) == 1) 
      {
            for (size_t i = 0; i < arg._v.size(); ++i)
            {
                  sum = carry + arg._v[i] + basis - 1;
                  if (i < _v.size()) 
                  {
                        sum -= _v[i];
                  }
                  result._v.push_back(sum % basis);
                  carry = sum / basis;
            }
      }
      else
      {
            for (size_t i = 0; i < _v.size(); ++i)
            {
                  sum = carry + _v[i] + basis - 1;
                  if (i < arg._v.size()) 
                  {
                        sum -= arg._v[i];
                  }
                  result._v.push_back(sum % basis);
                  carry = sum / basis;
            }
      }
      while ((result._v.size()>1) and (result._v[result._v.size()-1] == 0)) 
            result._v.pop_back();                              // remove leading zeros
      return result;
}


LargeInt LargeInt::operator+(const LargeInt& arg) const        // addition
{
      LargeInt result;
      if (_negative == arg._negative) 
      {
            result = add_abs_values(arg);
      }
      else
      {
            result = sub_abs_values(arg);
      }
      result._negative = (_negative and arg._negative) or 
                         (arg._negative and (abs_smaller(arg) == 1)) or
                         (_negative and (abs_smaller(arg) == -1));
      return result;
}

LargeInt LargeInt::operator*(const LargeInt& arg) const	// multiplication
{
	LargeInt result;
	result._negative=((_negative && arg._negative) || (!(_negative && arg._negative))); // you can try it out: this always get the right sign of the result
	// now we only have to take care of the multiplication of the absolute values and at the end we will assign the right sign
	basetype mulcarry; // needed for multiplication to store the carry of actual elemental multiplication
	
}

