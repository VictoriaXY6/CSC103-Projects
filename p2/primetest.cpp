

/*
 * CSc103 Project 2: prime numbers.
 * See readme.html for details.
 * Please list all references you made use of in order to complete the
 * assignment: your classmates, websites, etc.  Aside from the lecture notes
 * and the book, please list everything.  And remember- citing a source does
 * NOT mean it is okay to COPY THAT SOURCE.  What you submit here **MUST BE
 * YOUR OWN WORK**.
 * References: readme.html  https://aike.baidu.com/zhishu/263515?fr=aladdin  https://blog.csdn.net/jonms/srticle/details/80464622
 *
 */

#include<iostream>
#include<cmath>
using namespace std;

int main()
{
 int input;
 while(cin >> input){
  if(input == 1 || (input%2 == 0 && input != 2)){
   cout << 0 <<endl;
  }
  else
   {
    int factorCounter = 0;
    for(int i = 1;i <= input;i++){
     if(input%i == 0){
      factorCounter++;
     }
    }
    if(factorCounter > 2){
     cout << 0 << endl;
    }
    else
     {
      cout << 1 << endl;
     }
    }
  }
  return 0;
}






/*
method 2:

#include<iostream>
#include<cmath>
using namespace std;

bool isPrime(int n){
 if((n<2 || n%2==0)&& n!=2) return 0;
 int divide=3;
 while(divide<=sqrt(n)){
  if(n%divide==0) return 0;
  divide +=2;
 }
 return 1;
}

int main()
{
 int n;
 while(cin >> n){
  cout << isPrime(n) << endl;
 }
 return 0;
}


*/
