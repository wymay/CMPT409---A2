#include <vector>
#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

struct SuffixArray
{
  const int L;
  string s;
  vector<vector<int>> P;
  vector<pair<pair<int, int>, int>> M;

  SuffixArray(const string &s) : L(s.length()), s(s), P(1, vector<int>(L, 0)), M(L)
  {
    for (int i = 0; i < L; i++)
      P[0][i] = int(s[i]);
    for (int skip = 1, level = 1; skip < L; skip *= 2, level++)
    {
      P.push_back(vector<int>(L, 0));
      for (int i = 0; i < L; i++)
        M[i] = make_pair(make_pair(P[level - 1][i], i + skip < L ? P[level - 1][i + skip] : -1000), i);
      sort(M.begin(), M.end());
      for (int i = 0; i < L; i++)
        P[level][M[i].second] = (i > 0 && M[i].first == M[i - 1].first)
                                    ? P[level][M[i - 1].second]
                                    : i;
    }
  }

  vector<int> GetSuffixArray() { return P.back(); }

  int LongestCommonPrefix(int i, int j)
  {
    int len = 0;
    if (i == j)
      return L - i;
    for (int k = P.size() - 1; k >= 0 && i < L && j < L; k--)
    {
      if (P[k][i] == P[k][j])
      {
        i += 1 << k;
        j += 1 << k;
        len += 1 << k;
      }
    }
    return len;
  }
};

int main()
{
  int t;
  cin >> t;
  while (t--)
  {
    string s;
    cin >> s;
    SuffixArray suffix(s);
    vector<int> v = suffix.GetSuffixArray();
    vector<int> a(v.size(), 0);
    for (int i = 0; i < v.size(); i++)
      a[v[i]] = i;

    int maxlen = 0, idx = -1;
    for (int i = 0; i < a.size() - 1; i++)
    {
      int l = suffix.LongestCommonPrefix(a[i], a[i + 1]);
      if (maxlen < l)
      {
        maxlen = l;
        idx = i;
      }
    }
    int count = 1;
    for (int i = idx; i < a.size() - 1 && suffix.LongestCommonPrefix(a[i], a[i + 1]) == maxlen; i++)
      count++;
    if (maxlen == 0)
      cout << "No repetitions found!" << endl;
    else
      cout << s.substr(a[idx], maxlen) << " " << count << endl;
  }
}
