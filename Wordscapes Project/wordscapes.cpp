//cheat for the popular app Wordscapes

#include<bits/stdc++.h>
using namespace std;

#define FOR(i, a, b) for(int i = (a); i < (b); ++i)
#define RFOR(i, b, a) for(int i = (b) - 1; i >= (a); --i)
#define REP(i, N) FOR(i, 0, N)
#define RREP(i, N) RFOR(i, N, 0)
#define FILL(A,value) memset(A,value,sizeof(A))
#define endl '\n'

#define ALL(V) V.begin(), V.end()
#define SZ(V) (int)V.size()
#define pb push_back
#define mp make_pair
#define Pi 3.14159265358979
#define A first
#define B second

typedef long long ll;
typedef vector <int> vi;
typedef vector<ll> vl;
typedef pair <int, int> pi;
typedef pair <ll, int> pl;
typedef pair <ll, ll> pll;
typedef pair <double, double> pd;

//change these according to prob constraints
const int INF = 1000000000;
const int MAX = 100005;
const int MAX1 = 1005;
const int MAX2 = 105;
const int LEN = 105;
const int BASE = 1000000000;
const double EPS = 1e-7;
const int MOD = 1000000007;
//g++ -std=c++11 your_file.cpp -o your_program

set<string> S;
set<string> outp;

void output(string s, int ct, string arr[]){
    int lo = 0, hi = ct - 1, mid;
    bool f = 0;
    while (lo <= hi){
        mid = (lo + hi) / 2;
        if (arr[mid] == s) {
            outp.insert(s);
            break;
        }
        else if (arr[mid] < s){
            lo = mid + 1;
        }
        else hi = mid - 1;
    }
}

int main(void){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    clock_t begin = clock();
    string s;
    cin >> s;
    int n = SZ(s);
    string line;
    ifstream myfile("words1.txt"); //dictionary 
    string arr[235887];
    int ct = 0;
    if (myfile.is_open()){
        while (! myfile.eof() ){
            getline (myfile,line);
            if (SZ(line) <= n) {
                bool f = 0;
                REP(i, SZ(line)){
                    if (isupper(line[i])){
                        f = 1;
                        break;
                    }
                }
                if (!f) {
                    arr[ct] = line;
                    ++ct;
                }
            }
        }
        myfile.close();
    }
    sort(ALL(s));
    do {
        RFOR(i, n + 1, 3){
            REP(j, n - i + 1){
                string tmp = s.substr(j, i);
                if (S.find(tmp) == S.end()) {
                    S.insert(tmp);
                    output(tmp, ct, arr);
                }
            }
        }
    } 
    while (next_permutation(ALL(s)));
    int tmp;
    cout << "Special? " << endl;
    cin >> tmp;
    if (tmp == 1){
        while (1){
            char c;
            cin >> c;
            bool f = 0;
            REP(i, n) {
                if (s[i] == c) f = 1;
            }
            if (f){
                for (auto x : outp){
                    if (x[0] == c) cout << x << endl;
                }
                cout << endl;
            }
            else break;
        }
    }
    else{
        for (auto x : outp){
            cout << x << endl;
        }
    }
    clock_t end = clock();
    double esecs = double(end - begin) / CLOCKS_PER_SEC;
    //cout << esecs << " seconds" << endl;
    return 0;
}
