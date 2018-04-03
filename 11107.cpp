#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

struct SuffixArray {
    const int L;
    string s;
    vector<vector<int> > P;
    vector<pair<pair<int, int>, int> > M;
    
    SuffixArray(const string &s) : L(s.length()), s(s), P(1, vector<int>(L, 0)), M(L) {
        for (int i = 0; i < L; i++) P[0][i] = int(s[i]);
        for (int skip = 1, level = 1; skip < L; skip *=2, level++) {
            P.push_back(vector<int>(L, 0));
            for (int i = 0; i < L; i++) 
                M[i] = make_pair(make_pair(P[level-1][i], i + skip < L ? P[level-1][i+skip] : -1000),i);
            sort(M.begin(), M.end());
            for (int i = 0; i < L; i++)
                P[level][M[i].second] = (i > 0 && M[i].first == M[i-1].first) ? P[level][M[i-1].second] : i;
        }
    }

    vector<int> GetSuffixArray() { return P.back();}

    int LongestCommonPrefix(int i, int j) {
        int len = 0;
        if (i == j) return L - i;
        for (int k = P.size() - 1; k >= 0 && i < L && j < L; k--){
            if (P[k][i] == P[k][j]) {
                i += 1 << k;
                j += 1 << k;
                len += 1 << k;
            }
        }
        return len;
    }
};



int main() {
    int n;
    int flag = 0;
    while(cin >> n && n) {
        if(flag) cout << endl;
        flag = 1;
        string gStr;
        for(int i = 0; i < n; i++) {
            string dna;
            cin >> dna;
            gStr += (dna + '#');
        }
        SuffixArray suffix(gStr);
        vector<int> tempSA = suffix.GetSuffixArray();
        int len = tempSA.size();
        // cout << "len= " << len << endl;
        vector<int> suffixArr(len, 0);
        vector<int> lifeForms(len, 0);
        vector<int> endIndex(n, 0);
        int lf = 0;
        for (int i = 0; i < len; i++){
            suffixArr[tempSA[i]] = i;
            lifeForms[tempSA[i]] = lf;
            if(gStr[i] == '#'){
                endIndex[lf] = i;
                lf++;
            } 
        }
        vector<int> count(n, 0);
        // for(int i=0; i<len; i++){
        // //    cout << endIndex[i] << " " ;
        //    cout << suffixArr[i] << " " ;
        // }
        // cout << endl;

        // First n suffix starts with '#'

        int i = n;
        int j = n;
        int num = 0;
        int maxLen = 0;
        vector<int> index;
        while(i < len && j < len){
            while(num < (n/2+1)){
                while(j < len && count[lifeForms[j]] != 0 ){
                    count[lifeForms[j]]++;
                    j++;
                }
                if(j == len) break;
                num ++; 
                count[lifeForms[j]]++; 
                while(i < len && count[lifeForms[i]] > 1){
                    count[lifeForms[i]]--;
                    i++;
                }
                if (num < (n/2+1))
                    j++;
            }
            // cout << "i= " << i << " j= " << j << "len= " << len << endl;
            // cout<< num<<endl;
            if(num == (n/2+1)) {
                int minP = min((endIndex[lifeForms[i]]-suffixArr[i]),(endIndex[lifeForms[j]]-suffixArr[j]));
                // cout << "min= " << minP << endl;
                int LCP = min(suffix.LongestCommonPrefix(suffixArr[i], suffixArr[j]),minP);
                // cout << "LCP= " << LCP << endl;
                if(LCP == maxLen){
                    index.push_back(suffixArr[i]);
                }
                else if( LCP > maxLen){
                    maxLen = LCP;
                    index.clear();
                    index.push_back(suffixArr[i]);
                }
                count[lifeForms[i]]--;
                i++;
                num--;
                j++;
                // cout << i << "," << j << "," << num << "," << n << endl;
            }
        }
        // cout << maxLen << endl;
        if(maxLen == 0){
            cout << "?" << endl;
        }
        else {
            for(int i = 0; i < index.size(); i++){
                if (i==0 || suffix.LongestCommonPrefix(index[i], index[i-1]) < maxLen){
                    string s = gStr.substr(index[i],maxLen);
                    cout << s << endl;
                }
            }
        }
        // cout << endl;
    }  
    return 0;
}
