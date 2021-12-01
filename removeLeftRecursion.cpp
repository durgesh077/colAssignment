#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define pb push_back
map<string,vector<string>>table;
vector<string> split(string s,char ch)
{
   string cur;
   s+=ch;
   vector<string>ans;
   int started=0;
   for(int i=0;i<s.size();i++)
   {  
      if(s[i]==ch and started)
         ans.pb(cur),
         started=0,
         cur.clear();
      else
      if(not started and s[i]==' ')
         continue;
      else
          started=1, cur.push_back(s[i]);
   }
   return ans;
}
string strip(string s)
{
   int started=0;
   string ans;
    while(s.size() and s.back()==' ')
       s.pop_back();

   for(int i=0;i<s.size();i++)
      if(started or s[i]!=' ')
         ans.pb(s[i]),started=1;
   return ans;
}   
void update(string s)
{
      string by="->";
      auto srch=search(s.begin(),s.end(),by.begin(),by.end())-s.begin();
      assert(srch<s.size());
      auto left=s.substr(0,srch);
      left=strip(left);
      auto right=s.substr(srch+by.size());
      right=strip(right);
      assert(left.size() and right.size());
      for(auto &s:split(right,'|'))
         table[left].push_back(s);
      sort(table[left].begin(),table[left].end());
}  
void removeLeftRecursion()
{
   int Zcnt=1;
   decltype(table) tmpTable;
   for(auto &[key,prods]:table)
   {
      set<int>ws;
      int ind=0;
      for(auto &s:prods)
      {
         if(s.substr(0,key.size())==key)
            ws.insert(ind);
         ind++;
      }
      if(ws.empty())
         tmpTable[key]=prods;
      else{
         string newKey=string("Z")+to_string(Zcnt++);
         ind=0;
         for(auto &s:prods)
            {
               if(ws.count(ind))
                  tmpTable[newKey].push_back(strip(s.substr(key.size()))+" "+newKey);
               else
                  tmpTable[key].push_back(s+" "+newKey);
               ind++;
            }
            tmpTable[newKey].push_back("EPSILON");
      }
   }
   table=tmpTable;
} 
void printGrammar()
{
   for(auto &[key,prods]:table)
   {
      cout<<key<< " -> ";
      for(int i=0;i<prods.size();i++)
         cout<<prods[i]<<(i==prods.size()-1?"":" | ");
      cout<<endl;
   }
}     
int main()
{
   int n=1;
   cin>>n;
   fflush(stdin);
   for(int i=0;i<n;i++){
      string s;
      getline(cin,s);
      update(s);
   }

   removeLeftRecursion();
   printGrammar();
}
