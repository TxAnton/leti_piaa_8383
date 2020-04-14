#include <string>
#include <iostream>
#include <vector>

using namespace std;

vector<size_t> KMP(const string& sample, const string& text){
    vector<size_t>& prefix = *new vector<size_t>(sample.length());//O(m) memory usage
    vector<size_t> entries;//Entries array

    size_t last_prefix = prefix[0] = 0;//Init prefix value for zero position
    for (size_t i=1; i<sample.length(); i++) {//Hence going from secons position
        while (last_prefix > 0 && sample[last_prefix] != sample[i])
            last_prefix = prefix[last_prefix-1];

        if (sample[last_prefix] == sample[i])
            last_prefix++;

        prefix[i] = last_prefix;
    }

    last_prefix = 0;
    for (size_t i=0; i<text.length(); i++) {
        while (last_prefix > 0 && sample[last_prefix] != text[i])
            last_prefix = prefix[last_prefix-1];

        if (sample[last_prefix] == text[i])
            last_prefix++;

        if (last_prefix == sample.length()) {
            entries.push_back(i + 1 - sample.length());
        }
    }
    delete(&prefix);
    return entries;
}

int cycle(string A, string B){
    vector<size_t>& prefix = *new vector<size_t>(A.length());
    size_t max_prefix = 0;
    size_t last_prefix = prefix[0] = 0;
    for (size_t i=1; i<A.length(); i++) {
        while (last_prefix > 0 && A[last_prefix] != A[i])
            last_prefix = prefix[last_prefix-1];

        if (A[last_prefix] == A[i])
            last_prefix++;

        prefix[i] = last_prefix;
    }

    last_prefix = 0;
    for (size_t i=0; i<B.length(); i++) {
        while (last_prefix > 0 && A[last_prefix] != B[i])
            last_prefix = prefix[last_prefix-1];

        if (A[last_prefix] == B[i])
            last_prefix++;

        if (last_prefix > max_prefix) {
            max_prefix = last_prefix;
        }
    }

    for(int i = 0;i<A.length()-max_prefix;i++){
        if(A[i+max_prefix]!=B[i]){
            delete(&prefix);
            return -1;
        }
    }

    delete(&prefix);
    return max_prefix;

}

int main() {
    string sample;
    string text;
    cin>>sample;
    cin>>text;
    auto entries = KMP(sample,text);
    if(entries.empty())
        cout<<-1;
    else
        for(auto it=entries.begin();it!=entries.end();it++)
            cout<<(it==entries.begin()?"":",")<<*it;
    return 0;
}