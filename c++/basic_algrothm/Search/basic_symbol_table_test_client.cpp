#include <iostream>
#include <string>

int main(int argc, char *argv[])
{
    ST<string,int> st;
    string key;
    for (int i = 0; cin>> s; ++i) {
        st.put(key,i);
    }

    for(string s:ST.keys())
        cout<<s<<" "<<st.get(s);
    return 0;
}
