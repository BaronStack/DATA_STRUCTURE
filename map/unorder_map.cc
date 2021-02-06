
#include <iostream>
#include <map>
#include <string>
#include <unordered_map>


using namespace std;

int main() {
    
    unordered_map<string, map<string,map<string,string>>> u_mp;
    map<string, map<string,string>> mp;
    map<string,string> tmp_mp;
    tmp_mp.insert({"ke1-2","value1"});
    tmp_mp.insert({"ke2-2","value2"});
    tmp_mp.insert({"ke3-2","value3"});
    tmp_mp.insert({"ke4-2","value4"});

    mp.insert({"key1",tmp_mp});
    mp.insert({"key2",tmp_mp});
    mp.insert({"key3",tmp_mp});
    mp.insert({"key4",tmp_mp});

    u_mp.insert({"final", mp});

    cout << "u_map --> unordered_map<string, map<string,map<string,string>>> " << endl;
    cout << u_mp.at("final").size() << " " << u_mp.size() << endl;

    map<string, string>::iterator one_iter;
    for (auto v: u_mp.at("final")){
        if(v.first != "") {
            cout << "v.first: " << v.first << " size is :" <<  v.second.size() << endl;  
        }
        for(one_iter = v.second.begin(); one_iter != v.second.end(); ++one_iter) {
            cout << " one_iter.first " << one_iter->first << " one_iter.second " << one_iter->second << endl;
        }
    }

    cout << "Traverse 1" << endl;
    for(auto element : mp) {
        cout << element.first << " " << element.second.size() << endl;
    }

    // cout << "Traverse 2" << endl;
    // map<string, map<string,string>>::iterator it;
    // for(it = mp.begin(); it != mp.end(); ++it) {
        // cout << it->first << " " << it->second.size() << endl;
    // }

    return 0;
}
