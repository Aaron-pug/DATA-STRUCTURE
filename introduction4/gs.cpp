#include<iostream>
using namespace std;

int A[]={1,-2,7,2,6,-9,5,6,-12,-8,13,0,-3,1,-2,8,0,-5,3};

int gs_IC(int A[],int n){
  int gs=0;
  for(int lo=0;lo<n;lo++)
    for(int s=0,hi=lo;hi<n;hi++){
      s+=A[hi];
      gs=max(gs,s);
    }
  return gs;
}

int gs_DC(int A[],int lo,int hi){
  if(hi-lo<2) return A[lo];
  int mi=(lo+hi)/2;
  int gsL=0,gsR=0;
  for(int s=0,i=mi-1;i>=lo;i--)
    gsL=max(gsL,s+=A[i]);
  for(int s=0,j=mi;j<hi;j++)
    gsR=max(gsR,s+=A[j]);
  return max(gsL+gsR,max(gs_DC(A,lo,mi),gs_DC(A,mi,hi)));
}

int gs_LS(int A[],int n){
  int gs=0;
  for(int sum=0,k=n-1;k>=0;k--){
    sum+=A[k];
    gs=max(gs,sum);
    sum=max(sum,0);
  }
  return gs;
}



int main(){
  int ans1=gs_IC(A,sizeof(A)/sizeof(A[0]));
  cout<<ans1<<endl;
  int ans2=gs_DC(A,0,sizeof(A)/sizeof(A[0]));
  cout<<ans2<<endl;
  int ans3=gs_LS(A,sizeof(A)/sizeof(A[0]));
  cout<<ans3<<endl;
  return 0;
}