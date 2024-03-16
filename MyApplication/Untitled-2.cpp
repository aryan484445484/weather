   #include<bits/stdc++.h>
   using namespace std;
   #define int long long
#define max4(a, b, c, d) max(d, max(a, max(b, c)))
#define min4(a, b, c, d) min(d, min(a, min(b, c)))
#define min3(a, b, c) min(a, min(b, c))
#define max3(a, b, c) max(a, max(b, c))
#define vi vector<int>
#define vin(v, n)               \
    vector<int> v(n);           \
    for (int i = 0; i < n; i++) \
    {                           \
        cin >> v[i];            \
    }
   # define vout(v)                        \
    for (int i = 0; i < v.size(); i++) \
    cout << v[i] << " "
#define cy cout << "Yes" << endl
#define cn cout << "No" << endl


#define krishna \
int t;  \
cin>>t;  \
while(t--)  \

#define radhe             \
    ios::sync_with_stdio(false); \
    cin.tie(nullptr);            \
    cout.tie(nullptr);



 void Shri_ram (){
   
    int n;
    cin>>n;
     vin(v,n) 
     string s;
     char c='a';
     vector<char>a;
     for(int i=0;i<n;i++){
        if(v[i]==0){
       s.push_back(c);
        a.push_back(c);
c++;
        }else{
           a[v[i]]++;
           s.push_back(a[v[i]]);
        }
     }
   cout<<s<<endl;
 }
   signed main(){
      radhe 
        krishna
    Shri_ram();
}