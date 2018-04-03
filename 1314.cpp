#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

struct SuffixArray {
    const int L;
    string s;
    vector<vector<int> > P;
    vector<pair<pair<int,int>,int> > M;

    SuffixArray(const string &s) : L(s.length()), s(s), P(1,vector<int>(L, 0)), M(L) {
        for(int i = 0; i < L; i++) P[0][i] = int(s[i]);
        for(int skip = 1, level = 1; skip < L; skip *= 2, level++){
            P.push_back(vector<int>(L,0));
            for(int i = 0; i < L; i++)
                M[i] = make_pair(make_pair(P[level-1][i], i+skip < L ? P[level-1][i+skip] : P[level-1][i+skip-L]),i);
            sort(M.begin(), M.end());
            for(int i = 0; i < L; i++)
                P[level][M[i].second] = (i > 0 && M[i].first == M[i-1].first) ? P[level][M[i-1].second] : i;

        }
    }

    vector<int> GetSuffixArray() {return P.back(); }

};

int position1, position2;

int main()
{
    int n;
    cin >> n;
    for(int i = 0; i < n; i++) {
        int a;
        string str;
        cin >> a >> str;
        
        SuffixArray S = SuffixArray(str);
        vector<int> O = S.GetSuffixArray();
        for(int i = 0; i < str.length(); i++){
            if(O[i] == 0){
                cout << i << "\n";
                break;
            }
        }
    }

    return 0;
}