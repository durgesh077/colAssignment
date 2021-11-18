#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define pb push_back
ll dp[100][100],where[100][100];
vector<int>v;
int solve()
{
   const int n=v.size();

   
   for(int i=1;i<n;i++)
    for(int j=i;j>=1;j--){
      for(int k=j;k<=i;k++){ 
         int pre=dp[j][i];
      dp[j][i]=min(dp[j][i],dp[j][k-1]+dp[k][i]+(v[j-1]*v[k-1]*v[i]));
      if(dp[j][i]!=pre)
         where[j][i]=k;
   }
      // cout<<j<<" "<<i<<" "<<dp[j][i]<<" \n";
}
   return dp[1][n-1];
}
string printGroup(int l,int r)
{
   if(r<l)
      return "";
   if(r==l)
      return to_string(l);
   if(l+1==r)
      {
         string ans="(";
         ans+=to_string(l)+","+to_string(r)+")";
         return ans;
      }

   int k=where[l][r];
   string ans="(";
   ans+=printGroup(l,k-1);
   ans+=printGroup(k,r)+")";
   return ans;
}

int main()
{
   v.assign({ 40, 20, 30, 10, 30 ,34,34,12,12,6,1,9,5,56,2,3,34,2,35,});//, 1, 3
   for(int i=0;i<100;i++)
      for(int j=0;j<100;j++)
         dp[i][j]=i==j ?0:0x3f3f3f3f;

   cout<<solve()<<endl;
 cout<<  printGroup(1,v.size()-1);
}
