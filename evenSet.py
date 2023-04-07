# Even Set

# cook your dish here
def compute(mag,iro,k):
    res=0
    while(mag and iro):
        mc=mag.pop()
        ic=iro.pop()
        if mc>ic:
            if (mc-ic)<=k:
                res+=1
            else:
                iro.append(ic)
        else:
            if (ic-mc)<=k:
                res+=1
            else:
                mag.append(mc)
    return res

t=int(input())
for _ in range(t):
    n,k=map(int,input().split())
    s=input()
    s=s.replace(':','__')
    l=len(s)
    mag=list()
    iro=list()
    ans=0
    for i in range(l):
        if (s[i]=='X'):
            ans+=compute(mag,iro,k)
            mag,iro=[],[]
        elif (s[i]=='I'):
            iro.append(i)
        elif (s[i]=='M'):
            mag.append(i)
    ans+=compute(mag,iro,k)
    print(ans)
    
    
    
    #include <bits/stdc++.h>
# using namespace std;
# typedef long long int ll;
# int main()
# {
# 
#     ios_base::sync_with_stdio(false);
#     cin.tie(NULL);

#     ll t;
#     cin >> t;
#     while (t--)
#     {
# 
#         ll n, k;
#         cin >> n >> k;
#         string s;
#         cin >> s;

#         string new_s = "";
#         for (auto i : s)
#         {
#             if (i == ':')
#             {
#                 new_s += i;
#             }
#             new_s += i;
#         }
#         queue<ll> qi; //iron indexes
#         queue<ll> qm; //magnets indexes
#         int j = 0;
#         int ans = 0;

#         for (auto i : new_s)
#         {
#             if (i == 'I')
#             {
#                 while (!qm.empty() && qm.front() + k < j)
#                 {
#                     qm.pop();
#                 }

#                 if (!qm.empty())
#                 {
#                     ans++;
#                     qm.pop();
#                 }

#                 else
#                 {
#                     qi.push(j);
#                 }
#             }

#             //vice versa if magnet is found.
#             else if (i == 'M')
#             {

#                 while (!qi.empty() && qi.front() + k < j)
#                 {
#                     qi.pop();
#                 }

#                 if (!qi.empty())
#                 {
#                     ans++;
#                     qi.pop();
#                 }

#                 else
#                 {
#                     qm.push(j);
#                 }
#             }

#             //if there is a wall then simply remove all the previous magnets and irons
#             else if (i == 'X')
#             {
#                 while (!qm.empty())
#                 {
#                     qm.pop();
#                 }
#                 while (!qi.empty())
#                 {
#                     qi.pop();
#                 }
#             }

#             //increment the index of string
#             j++;
#         }

#         //output the final answer
#         cout << ans << endl;
#     }
# }
