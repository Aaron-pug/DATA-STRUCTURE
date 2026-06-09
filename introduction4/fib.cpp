#include<iostream>
using namespace std;
using ll=long long;

ll M[90];

int fib(int n){
  if(n<2) return n;
  else if(M[n]==0){
    M[n]=fib(n-1)+fib(n-2);
  }
  return M[n];
}


int main(){
  int n;
  cin>>n;
  cout<<fib(n)<<endl;
  return 0;
}