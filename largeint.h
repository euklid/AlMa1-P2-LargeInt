// largeint.h (Declaration of class LargeInt)

#include <vector>
#include <string>

class LargeInt
{
public:
      typedef long long int inputtype; 

      LargeInt(inputtype);                       // constructor
      std::string decimal();                     // returns the decimal representation 
      bool operator<(const LargeInt&) const;     // comparison
      LargeInt operator+(const LargeInt&) const; // addition
      LargeInt operator*(const LargeInt&) const; // multiplication	
private:
      typedef unsigned long long int basetype;

      static const basetype logbasis;            // Number of decimal digits in basis
      static const basetype basis;               // basis = power of 10

      static basetype power_of_ten(basetype);
      int abs_smaller(const LargeInt&) const;    // absolute value smaller than arg's?
      LargeInt add_abs_values(const LargeInt&) const;   // add absolute values
      LargeInt sub_abs_values(const LargeInt&) const;   // subtract absolute values
      LargeInt();                                // default constructor (private!)
	
      bool _negative;
      std::vector<basetype> _v;      
};

