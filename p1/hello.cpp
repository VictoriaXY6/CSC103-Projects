/*
 * CSc103 Project 1: (hello_world++)
 * See readme.html for details.
 * Please list all references you mde use of in order to complete the
 * assignment: your classmates, websites, etc.  Aside from the lecture notes
 * and the book, please list everything.  And remember- citing a source does
 * NOT mean it is okay to COPY THAT SOURCE.  What you submit here **MUST BE
 * YOUR OWN WORK**.
 * References:csc103-projects/p1/readme.html  cnblogs.com/X-Do-Better/p/8628492.html cnblogs.com/aminxu/p/4686320.html

 *
 */

#include<iostream>
#include<string>
using namespace std;

int main()
{
    string name;
    string relative;
    cout << "Enter your name: " << endl;
    cin >> name;
    cout << "Enter a relative: " << endl;
    cin >> relative;
    cout << "Hello. My name is " << name << ". You killed my "<< relative << ". Prepare to die." <<endl;
    return 0;
}




