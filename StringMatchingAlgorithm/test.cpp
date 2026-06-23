#include "KMP.hpp"
#include "BruteForce.hpp"


void testBF()
{
	cout << BruteForce("abcdef", "def") << endl;   // 3
	cout << BruteForce("abcdefgh", "def") << endl; // 3
	cout << BruteForce("abcdefgh", "ab") << endl;  // 0
	cout << BruteForce("abcdefgh", "cdd") << endl; //-1
}
void testKMP()
{
	cout << KMP("abcdefabcddrf", "abc") << endl;  // 0
	cout << KMP("abcdefabcddrf", "abe") << endl;  //-1
	cout << KMP("abcdefabcddrf", "a") << endl;	  // 0
	cout << KMP("abcdefabcddrf", "cdef") << endl; // 2
	cout << KMP("abcdefabcddrf", "dd") << endl;	  // 9
	cout << KMP("abcdefabcddrf", "de") << endl;	  // 3
	cout << KMP("abcdefabcddrf", "drf") << endl;  // 10
	cout << KMP("abc", "abc") << endl;			  // 0
	cout << KMP("", "drf") << endl;				  //-1
	cout << KMP("", "") << endl;				  //-1
}

int main()
{
	testBF();
	testKMP();
	return 0;
}
