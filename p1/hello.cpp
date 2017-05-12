/*
 * CSc103 Project 1: (hello_world++)
 * See readme.html for details.
 * Please list all references you made use of in order to complete the
 * assignment: your classmates, websites, etc.  Aside from the lecture notes
 * and the book, please list everything.  And remember- citing a source does
 * NOT mean it is okay to COPY THAT SOURCE.  What you submit here **MUST BE
 * YOUR OWN WORK**.
 * References:
 * http://stackoverflow.com/questions/5739937/using-getlinecin-s-after-cin
 */

#include <iostream>
using std::cin;
using std::cout;
#include <string>
using std::string;

int main()
{
	cout << "Enter your name:" << "\n";
	string name;
	getline(cin, name);

	cout << "Enter a relative:" << "\n";
	string relative;
	getline(cin, relative);

	cout << "Hello. My name is " << name << ". You killed my " << relative << ". Prepare to die. " << "\n";

	return 0;
}
