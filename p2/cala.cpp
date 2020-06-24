#include<iostream>
using namespace std;

int main()
{
  int x;
  int count;
  while(cin >> x){
    int n=x;
    count=0;
    while(n!=1){
      if(n%2==0){
      n=n/2;
    }else{
      n=3*n+1;
    }
    count++;
    }
    cout << " termination after" <<    count << " steps.\n";
  }
  return 0;


}