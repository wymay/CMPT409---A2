#include <vector>
#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int n, m, k;
vector<vector<char>> grid;
vector<string> words;

int input()
{
  grid.clear();
  words.clear();

  cin >> n >> m;
  for (int i = 0; i < n; i++)
  {
    char c;
    grid.push_back(vector<char>());

    for (int j = 0; j < m; j++)
    {
      cin >> c;
      if (c <= 'z' && c >= 'a')
        c = c - 'a' + 'A';
      grid[i].push_back(c);
    }
  }

  cin >> k;
  for (int i = 0; i < k; i++)
  {
    string s;
    cin >> s;
    for (int i = 0; i < s.length(); i++)
      if (s[i] <= 'z' && s[i] >= 'a')
        s[i] = s[i] - 'a' + 'A';
    words.push_back(s);
  }
}

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
};

int main()
{
  int t;
  cin >> t;
  while (t--)
  {
    input();
    string str;
    vector<pair<int, int>> pos;
    vector<pair<int, int>> starting;
    for (int i = 0; i < n; i++)
    {
      starting.push_back(make_pair(i, 0));
      starting.push_back(make_pair(i, m - 1));
    }
    for (int j = 0; j < m; j++)
    {
      starting.push_back(make_pair(0, j));
      starting.push_back(make_pair(n - 1, j));
    }

    for (auto p : starting)
    {

      for (int ii = -1; ii <= 1; ii++)
        for (int jj = -1; jj <= 1; jj++)
          if (ii != 0 || jj != 0)
          {
            int i = p.first, j = p.second;
            while (i >= 0 && i < n && j >= 0 && j < m)
            {
              str += grid[i][j];
              pos.push_back(make_pair(i, j));
              i += ii;
              j += jj;
            }
            str += "$";
            pos.push_back(make_pair(-1, -1));
          }
    }
    vector<int> strpos;
    for (auto s : words)
    {
      strpos.push_back(str.length());
      str += s + '#' + s + '^';
    }

    SuffixArray suffix(str);
    vector<int> v = suffix.GetSuffixArray();
    vector<int> a(v.size(), 0);
    for (int i = 0; i < v.size(); i++)
    {
      a[v[i]] = i;
    }
    for (int i = 0; i < words.size(); i++)
    {
      int st = v[strpos[i]], ed = v[strpos[i] + words[i].length() + 1];
      pair<int, int> ans = make_pair(1000, 1000);
      for (int j = st + 1; j <= ed - 1; j++)
      {
        if (a[j] < pos.size() && pos[a[j]] < ans)
        {
          ans = pos[a[j]];
        }
      }
      cout << ans.first + 1 << " " << ans.second + 1 << endl;
    }
    if (t != 0)
      cout << endl;
  }
}