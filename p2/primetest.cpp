/*
 * CSc103 Project 2: prime numbers.
 * See readme.html for details.
 * Please list all references you made use of in order to complete the
 * assignment: your classmates, websites, etc.  Aside from the lecture notes
 * and the book, please list everything.  And remember- citing a source does
 * NOT mean it is okay to COPY THAT SOURCE.  What you submit here **MUST BE
 * YOUR OWN WORK**.
 * References:
 *
 */

#include <iostream>
using std::cin;
using std::cout;
using std::endl;
#include <cmath>

int main()
{
	unsigned long n;
	bool isp=true;
	while(cin>>n)
	{
		isp=true;
		if (n<2)
		{
			cout << "0" << "\n";
		} else if (n!=2 && n%2==0)
		{
			cout << "0" << "\n";
		} else if (n%2!=0)
		{	
			for (int i=3; i<=sqrt(n); i+=2)
			{	
				if (n%i==0)
				{
					isp=false;
					cout << "0" << endl;
					break;		
				}
			
			}
			if(isp)
				cout << "1" <<endl;
		} else
		{
			cout << "1" << endl;
		}

	}
	return 0;
}
