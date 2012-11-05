// factorial.C (Computing n! by addition)

#include <iostream>
#include <limits>
#include "largeint.h"


LargeInt factorial(LargeInt::inputtype n)        // computes n!
{                                                // warning, slow: running time O(n^3)
      LargeInt result(1);
      LargeInt sum(0);
      for (LargeInt::inputtype i = 2; i <= n; ++i)
      {
            sum = 0;
            for (LargeInt::inputtype j = 1; j <= i; ++j)       
            {
                  sum = sum + result;
            }
            result = sum;
      }
      return result;
}

      
int main()
{   
      LargeInt::inputtype n = 1;
      std::cout << "This program computes n!, for a natural number n up to "
                << std::numeric_limits<LargeInt::inputtype>::max() 
                << " (if time and memory suffice).\n";
                
      std::cout << "Enter a natural number n: ";
      std::cin >> n;
      
      std::cout << n << "! = " << factorial(n).decimal() << "\n";
      return 0;
}

