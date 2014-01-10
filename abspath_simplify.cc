/* Qunar 2014 Campus Hiring
 *  
 *      网上题目，注意甄别。
 *
 * Problem Description:
 *  
 *  将绝对路径转换成相对路径。例如
 *  input: /home/news/../tmp/game/../
 *  ouptut: /home/tmp/
 *
 * Analysis:
 *  
 *  注意：/..与/.与/等价。另外，转换后的并非相对路径。确切地说，
 *  应该为：绝对路径简化。
 *
 */
#include <iostream>
using std::cout; using std::cerr; using std::endl;
#include <string>
using std::string;
#include <vector>
using std::vector;

static void process_entry(vector<string> &svec, string &entry) {
    if(!entry.empty() && entry != ".") {
        if (entry == "..") {
            if(svec.size() != 0)
                svec.pop_back();
        } else
            svec.push_back(entry);
    }
}

string abs_path_conv(const string &s) {
    string::size_type prev, cur;
    const char delim = '/';
    if(s.front() != delim)
        return "";
    prev = 1;
    vector<string> svec;
    while( (cur = s.find(delim, prev)) != string::npos) {
        string entry = s.substr(prev, cur-prev);
        process_entry(svec, entry);
        prev = cur + 1;
    }
    if(prev < s.size()) {
        string entry = s.substr(prev);
        process_entry(svec, entry);
    }
    string ret;
    if(svec.size() == 0)
        ret = "/";
    else {
        for(auto entry: svec)
            ret += "/" + entry;
    }
    return ret;
}
int main(int argc, char *argv[]) {
    if(argc != 2) {
        cout << "Usage: " << argv[0] << " <pathname>" << endl;
        return -1;
    }

    string s = abs_path_conv(argv[1]);
    if (s.empty()) {
        cerr << "The pathname " << argv[1] 
             << " is not absolute." << endl;
        return -1;
    }

    cout << s << endl;
    return 0;
}
