#include<bits/stdc++.h>
using namespace std;

typedef pair<int, int> PT;
typedef long long LL;
LL TA, TB = 1000000;
LL S;

bool check(PT A, PT B) {
    LL dx = abs(A.first - B.first);
    LL dy = abs(A.second - B.second);
    LL I = (S-dx)*(S-dy);
    LL SS = S*S;

//    cout<<"---> "<<A.first<<" "<<A.second<<" "<<B.first<<" "<<B.second<<" "<<I<<" "<<SS<<" "<<TA<<" "<<TB<<endl;
    return 1.0L*I*TB > 1.0L*TA*(2*SS-I);
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int t, cs= 0;
    cin>>t;

    while (t--) {
        int n;
        double d;
        cin>>n>>S>>d;
        TA = round(d*TB);

        vector<pair<PT, PT>> s(n);
        for (int i=0; i<n; i++) {
            cin>>s[i].second.first;
            cin>>s[i].second.second;
            double d;
            cin>>d;
            s[i].first.first = round(d*TB);
            s[i].first.second = i+1;
        }
        sort(s.rbegin(), s.rend());

        map<int, set<PT>> mp;
        vector<int> ans;

        int K = S+1;

        for (int i=0; i<n; i++) {
            int x = s[i].second.first;
            int y = s[i].second.second;

//            cout<<"At "<<x<<" "<<y<<endl;

            bool good = true;
            for (auto it = mp.lower_bound(y-S-K), up = mp.upper_bound(y+S+K+1); it != up; it++) {
                auto &st = it->second;
                for (auto it2 = st.lower_bound(PT(x-S, 0)), up2 = st.upper_bound(PT(x+S+1, 0)); it2 != up2; it2++) {
                    PT P = *it2;
//                    cout<<"Check "<<P.first<<" "<<P.second<<endl;
                    if (check(s[i].second, P)) good = false;
                    if (!good)  break;
                }
                if (!good)  break;
            }

            if (good) {
                ans.push_back(s[i].first.second);
                mp[(y/K)*K].insert(s[i].second);
            }
        }

        sort(ans.begin(), ans.end());
        cout<<"Case #"<<++cs<<": "<<ans.size()<<endl;
        for (int x: ans)    cout<<x<<" ";
        cout<<endl;
    }
}