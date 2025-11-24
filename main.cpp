#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;


vector<int> computeLPS(string pattern) {
    int m = pattern.length();
    if (m == 0) return {};

    vector<int> lps(m, 0);
    int len = 0;

    for (int i = 1; i < m; i++) {
        while (len > 0 && pattern[i] != pattern[len]) {
            len = lps[len - 1];
        }
        if (pattern[i] == pattern[len]) {
            len++;
        }
        lps[i] = len;
    }
    return lps;
}

void KMP_search(string text, string pattern) {
    int n = text.length();
    int m = pattern.length();

    if (m == 0) return;

    vector<int> lps = computeLPS(pattern);

    int i = 0;
    int j = 0;

    while (i < n) {
        if (pattern[j] == text[i]) {
            i++;
            j++;
        }

        if (j == m) {
            cout << "KMP: 패턴을 인덱스 " << (i - j) << "에서 찾았습니다." << endl;
            j = lps[j - 1];
        }
        else if (i < n && pattern[j] != text[i]) {
            if (j != 0) {
                j = lps[j - 1];
            }
            else {
                i++;
            }
        }
    }
}

void print_SP_table(string pattern) {
    int m = pattern.length();
    if (m == 0) return;

    vector<int> sp = computeLPS(pattern);

    cout << "--- KMP SP (LPS) 테이블 ---" << endl;
    cout << "Pattern P = \"" << pattern << "\"" << endl;
    //cout << "--------------------" << endl;
    cout << setw(7) << "index" << " | " << setw(10) << "SP[index]" << endl;
    //cout << "--------------------" << endl;

    for (int i = 0; i < m; i++) {
        cout << setw(7) << i << " | " << setw(10) << sp[i] << endl;
    }
    //cout << "--------------------" << endl;
    cout << endl;
}

#define d 256

void RabinKarp_search(string text, string pattern, int q) {
    int n = text.length();
    int m = pattern.length();

    if (m == 0 || m > n) return;

    int p_hash = 0;
    int t_hash = 0;
    int h = 1;

    for (int i = 0; i < m - 1; i++) {
        h = (h * d) % q;
    }

    for (int i = 0; i < m; i++) {
        p_hash = (d * p_hash + pattern[i]) % q;
        t_hash = (d * t_hash + text[i]) % q;
    }

    for (int s = 0; s <= n - m; s++) {
        if (p_hash == t_hash) {
            int j;
            for (j = 0; j < m; j++) {
                if (text[s + j] != pattern[j]) break;
            }
            if (j == m) {
                cout << "Rabin-Karp: 패턴을 인덱스 " << s << "에서 찾았습니다." << endl;
            }
        }

        if (s < n - m) {
            t_hash = (t_hash - (text[s] * h) % q + q) % q;
            t_hash = (t_hash * d) % q;
            t_hash = (t_hash + text[s + m]) % q;
        }
    }
}

void bruteForce_search_table(string text, string pattern) {
    int n = text.length();
    int m = pattern.length();

    if (m == 0 || m > n) return;

    cout << "--- 직선적 알고리즘 (Brute-Force) 결과 ---" << endl;
    cout << "Text T = \"" << text << "\"" << endl;
    cout << "Pattern P = \"" << pattern << "\"" << endl;
    //cout << "------------------------" << endl;
    cout << endl;
    cout << setw(10) << "Match #" << " | " << setw(13) << "Found Index (i)" << endl;
    //cout << "------------------------" << endl;


    int match_count = 0;
    for (int i = 0; i <= n - m; i++) {
        int j;
        for (j = 0; j < m; j++) {
            if (text[i + j] != pattern[j]) break;
        }
        if (j == m) {
            match_count++;
            cout << setw(10) << match_count << " | " << setw(13) << i << endl;
        }
    }
    if (match_count == 0) cout << "(패턴을 찾지 못했습니다.)" << endl;
    //cout << "------------------------" << endl;
}

// --- Main 함수 ---
int main() {
    string text = "ABABDABACDABABCABAB";
    string pattern = "ABABCABAB";

    cout << "--- KMP 알고리즘 결과 ---" << endl;
    KMP_search(text, pattern);
    cout << endl;
    string pattern_from_image = "abcabe";
    print_SP_table(pattern_from_image);

    cout << "\n--- 라빈-카프 알고리즘 결과 ---" << endl;
    int q = 101;
    RabinKarp_search(text, pattern, q);

    cout << endl;


    cout << endl;
    bruteForce_search_table(text, pattern);

    return 0;
}