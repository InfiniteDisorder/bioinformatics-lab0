#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

string const A = "ATGAGCACTGCGGGAAAAGTGATCAAATGCAAAGCTGCGGTGCTATGGGAGCTTCACAAACCCTTCACCATCGAGG\n"
        "ACATAGAAGTCGCACCCCCCAAGGCCCATGAAGTTCGAATTAAGATGGTGGCCACTGGTGTCTGCCGCTCAGACGA\n"
        "TCACGTGGTTAGTGGAACCCTGGTCACACCTCTTCCTGCAGTTTTAGGCCATGAGGGAGCAGGCATTGTTGAGAGC\n"
        "GTTGGAGAAGGGGTGACTTGTGTGAAACCAGGTGATAAAGTCATTCCACTCTTTTCCCCTCAGTGTGGAGAATGCA\n"
        "GGATTTGCAAGCACCCGGAAAGCAACTTTTGTAGCCGAAGCGATCTGCTAATGCCTCGGGGGACTTTGCGCGAAGG\n"
        "CACCAGCAGGTTCTCCTGCAAGGGAAAGCAGATCCACAACTTTATCAGCACCAGCACCTTCTCCCAGTACACCGTG\n"
        "GTAGATGATATAGCAGTGGCCAAAATCGATGGAGCTTCACCACTGGACAAAGTCTGCCTCATCGGCTGTGGGTTCT\n"
        "CAACTGGCTATGGCTCTGCCGTCAAAGTCGCCAAGGTGACCCCAGGCTCCACATGTGCCGTGTTTGGCCTCGGAGG\n"
        "TGTCGGTCTGTCTGTCATCATTGGCTGTAAAGCAGCAGGAGCAGCCAGGATCATTGCTGTGGACATCAACAAGGAC\n"
        "AAGTTTGCCAAGGCCAAAGAGTTGGGTGCAACTGAGTGCATCAACCCTCAAGACTACAGCAAACCCATCCAGGAAG\n"
        "TTCTCCAGGAGATGACCGACGGAGGGGTGGACTTTTCGTTTGAAGTCATCGGCCGCCTTGACACCATGACTTCTGC\n"
        "CCTGCTGAGCTGCCATGCAGCATGTGGTGTAAGCGTCGTCGTAGGAGTGCCTCCCAATGCCCAGAACCTCTCCATG\n"
        "AACCCCATGTTGCTGCTGCTGGGACGCACCTGGAAGGGAGCAATATTTGGCGGGTTTAAGAGTAAAGATTCTGTCC\n"
        "CTAAACTTGTGGCTGACTTCATGGCTAAGAAGTTTCCGTTGGACCCGTTAATTACCCATGTTTTACCTTTCGAGAA\n"
        "AATAAATGAAGCATTTGACCTGCTTCGTTCTGGAAAGAGCATCCGTACCGTCCTGACTTTCTGA";
string const B = "ATGAGCACAGCAGGAAAAGTAATCAAATGCAAAGCAGCTGTGCTATGGGAGTTAAAGAAACCCTTTTCCATTGAGG\n"
        "AGGTGGAGGTTGCACCTCCTAAGGCCCATGAAGTTCGTATTAAGATGGTGGCTGTAGGAATCTGTGGCACAGATGA\n"
        "CCACGTGGTTAGTGGTACCATGGTGACCCCACTTCCTGTGATTTTAGGCCATGAGGCAGCCGGCATCGTGGAGAGT\n"
        "GTTGGAGAAGGGGTGACTACAGTCAAACCAGGTGATAAAGTCATCCCACTCGCTATTCCTCAGTGTGGAAAATGCA\n"
        "GAATTTGTAAAAACCCGGAGAGCAACTACTGCTTGAAAAACGATGTAAGCAATCCTCAGGGGACCCTGCAGGATGG\n"
        "CACCAGCAGGTTCACCTGCAGGAGGAAGCCCATCCACCACTTCCTTGGCATCAGCACCTTCTCACAGTACACAGTG\n"
        "GTGGATGAAAATGCAGTAGCCAAAATTGATGCAGCCTCGCCTCTAGAGAAAGTCTGTCTCATTGGCTGTGGATTTT\n"
        "CAACTGGTTATGGGTCTGCAGTCAATGTTGCCAAGGTCACCCCAGGCTCTACCTGTGCTGTGTTTGGCCTGGGAGG\n"
        "GGTCGGCCTATCTGCTATTATGGGCTGTAAAGCAGCTGGGGCAGCCAGAATCATTGCGGTGGACATCAACAAGGAC\n"
        "AAATTTGCAAAGGCCAAAGAGTTGGGTGCCACTGAATGCATCAACCCTCAAGACTACAAGAAACCCATCCAGGAGG\n"
        "TGCTAAAGGAAATGACTGATGGAGGTGTGGATTTTTCATTTGAAGTCATCGGTCGGCTTGACACCATGATGGCTTC\n"
        "CCTGTTATGTTGTCATGAGGCATGTGGCACAAGTGTCATCGTAGGGGTACCTCCTGATTCCCAAAACCTCTCAATG\n"
        "AACCCTATGCTGCTACTGACTGGACGTACCTGGAAGGGAGCTATTCTTGGTGGCTTTAAAAGTAAAGAATGTGTCC\n"
        "CAAAACTTGTGGCTGATTTTATGGCTAAGAAGTTTTCATTGGATGCATTAATAACCCATGTTTTACCTTTTGAAAA\n"
        "AATAAATGAAGGATTTGACCTGCTTCACTCTGGGAAAAGTATCCGTACCATTCTGATGTTTTGA";

struct Point {
    int i;
    int j;
    int val;
    Point* pred;
};

int maximum(struct Point **V, int k, int m) {
    if (k < 0 || m < 0)
        return 0;

    int max = 0;
    int max_i = 0;
    int max_j = 0;

    for(int i=0; i<=k; i++) {
        if (V[i][m].val > max) {
            max = V[i][m].val;
            max_i = i;
            max_j = m;
        }
    }

    for(int j=0; j<=m; j++) {
        if (V[k][j].val > max) {
            max = V[k][j].val;
            max_i = k;
            max_j = j;
        }
    }

    if (A[max_i] == B[max_j])
        V[k+1][m+1].pred = &V[max_i][max_j];
    else
        V[k+1][m+1].pred = V[max_i][max_j].pred;

    return max;
}

int main() {

    auto lenA = A.length();
    auto lenB = B.length();

    auto **V = new struct Point * [lenA];

    for(int i=0; i<lenA; i++) {
        V[i] = new struct Point [lenB];
        for(int j=0; j< lenB; j++) {
            V[i][j].i=i;
            V[i][j].j=j;
            V[i][j].val=0;
        }
    }

    auto *max = new struct Point;
    max->val = 0;

    for(int i=0; i<lenA; i++) {
        for(int j=0; j<lenB; j++) {
            V[i][j].val = maximum(V,i-1,j-1) + (A[i] == B[j] ? 1 : 0);
        }
    }
    for (int i=0; i < lenA; i++) {
        if (V[i][lenB-1].val > max->val)
            max = &V[i][lenB-1];
    }

    for(int j=0; j < lenB; j++) {
        if (V[lenA-1][j].val > max->val)
            max = &V[lenA-1][j];
    }

    vector<struct Point> path;
    while(max->i > 0 && max->j > 0) {
        path.push_back(*max);
        max = max->pred;
    }

    path.push_back(*max);

    reverse(path.begin(),path.end());

    cout << path[0].i << " " << path[0].j << endl;
    int pos_i = -1;
    int pos_j = -1;

    for (auto &it : path) {
        if (it.i - pos_i == 1)
            if (it.j - pos_j == 1)
                cout << A[it.i] << " " << B[it.j] << endl;
            else {
                for(int j = pos_j+1; j< it.j;j++) {
                    cout << "-" << " " << B[j] << endl;
                }
                cout << A[it.i] << " " << B[it.j] << endl;
            }
        else {
            for(int i = pos_i+1; i< it.i;i++) {
                cout << A[i] << " " << "-" << endl;
            }
            cout << A[it.i] << " " << B[it.j] << endl;
        }
        pos_i= it.i;
        pos_j= it.j;
    }
    cout << "LENGTH A : " << A.length() << "\nLENGTH B: " << B.length() << endl;
    cout << "MATCHES : " << path.size() << endl;
    return 0;
}