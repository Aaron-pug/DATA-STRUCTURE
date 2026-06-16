#include<iostream>
using namespace std;
typedef unsigned Rank;

template<typename T>
Rank binSearch(T *S,const T &e,Rank lo,Rank hi){
  while(lo<hi){
    Rank mi=(lo+hi)/2;
    if(e<S[mi]) hi=mi;
    else if(S[mi]<e) lo=mi+1;
    else return mi;
  }
  return -1;
}


int main(){
  
  return 0;
}
