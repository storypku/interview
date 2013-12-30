/* Alibaba 2014 Campus Hiring
 *      Sep 24, 2013
 *
 * Problem Description:
 *  一个有10亿条记录的文本文件，已按照关键字排好序存储。
 *  请设计算法，可以快速的从文件中查找指字关键字的记录。
 *
 * Analysis:
 *  If the data was devided into blocks with 1, 000, 000
 *  records each, then there are about 1, 000 blocks.
 *
 *  In my experiment, the text file contains 10, 000, 000
 *  records, devided into 1000 blocks with 10, 000 records
 *  each.
 *
 */
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cassert>
using namespace std;
using pos_t = streampos;

bool parse_file(const string dataf, vector<int> &gkeys,
                vector <pos_t> &gposs, pos_t *ope)
{
    assert(ope != nullptr && gkeys.empty() && gposs.empty());
    ifstream fin(dataf.c_str());
    if(!fin) {
        cerr << "Error reading file " << dataf << endl;
        return false;
    }
    const size_t CNT = 10000;

    fin.seekg(0, ios::end);
    *ope = fin.tellg();    // set the "one-pass-end" position
    fin.seekg(0, ios::beg);

    // NOTE: The calc for global indices here is not efficient enough 
    size_t icnt = 0;
    while(!fin.eof()) {
        pos_t pos;
        if(icnt % CNT == 0)
            pos = fin.tellg();
        string s;
        getline(fin, s);
        stringstream ss(s);
        int key;
        if ( (ss >> key) && (icnt++ % CNT == 0) ) {
            gkeys.push_back(key);
            gposs.push_back(pos);
        }
    }
    fin.close();
    return true;
}

static ssize_t index_keys(const vector<int> &keys, int key) {
    ssize_t low = 0, high = keys.size()-1, mid;
    while(low <= high) {
        mid = (low + high)/2;
        if(keys[mid] == key)
            return mid;
        else if (keys[mid] > key)
            high = mid - 1;
        else
            low = mid + 1;
    }
    return high;
}

bool
parse_record_region(const string dataf, pos_t start, pos_t stop,
                vector<int> &lkeys, vector<pos_t> &lposs) {
    assert(lkeys.empty() && lposs.empty());
    ifstream fin(dataf.c_str());
    if(!fin) {
        cerr << "Error reading file " << dataf << endl;
        return false;
    }
    fin.seekg(start, ios::beg);
    pos_t pos;
    while( (pos = fin.tellg()) != stop) {
        string s;
        getline(fin, s);
        stringstream ss(s);
        int key;
        if(ss >> key) {
            lkeys.push_back(key);
            lposs.push_back(pos);
        }
    }
    fin.close();
    return true;
}


string
find_record(const string dataf, const vector<int> &lkeys,
                const vector<pos_t> &lposs, int key) 
{
    ifstream fin(dataf.c_str());
    if(!fin) {
        cerr << "Error reading file " << dataf << endl;
        return string("");
    }
    ssize_t idx = index_keys(lkeys, key);
    if (idx < 0 || lkeys[idx] != key) {
        return string("");
    }
    string s;
    pos_t pos = lposs[idx];
    fin.seekg(pos, ios::beg);
    getline(fin, s);
    fin.close();
    return s;
}

int main(int argc, char *argv[]) {
    const string dataf("data");
    vector<int> gkeys;  // global keys
    vector<pos_t> gposs;    // global positions
    pos_t ope;
    // parse datafile to set global keys and positions. Meanwhile, update
    // the "one-pass-the-end" position
    if(!parse_file(dataf, gkeys, gposs, &ope)) 
        return -1;

    int key;
    cout << "Please input a key: ";
    while(cin >> key) {
        ssize_t idx;
        if( (idx = index_keys(gkeys, key)) < 0) {
            cerr << key << " not found." << endl;
            cout << "Please input a key: ";
            continue;
        }
        pos_t start = gposs[idx], stop;
        stop = (idx == gposs.size() - 1) ? ope: gposs[idx+1]; 
        vector<int> lkeys;
        vector<pos_t> lposs;
        if(!parse_record_region(dataf, start, stop, lkeys, lposs))
            return -1;
        string s = find_record(dataf, lkeys, lposs, key);
        if(!s.empty())
            cout << "Record: " << s << endl;
        else
            cerr << key << " not found." << endl;
        cout << "Please input a key: ";
    }
    return 0;
}
