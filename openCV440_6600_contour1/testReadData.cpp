#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

int testReadData(string infile, double* x, double* y, double* z) {
    std::ifstream ifs(infile);
    std::string str, s;

    int number = 0;

    if (ifs.fail()) {
        cerr << "Failed to open file." << std::endl;
        return -1;
    }

    int i = 0;
    while (getline(ifs, str)) {
        // std::cout << str << std::endl;
        stringstream ss{ str };
        vector<string> v;
        while (getline(ss, s, ' ')) {
            v.push_back(s);
        }

        /*for (const string& s : v) {
            cout << s << endl;
        }*/

        x[i] = stod(v[0]);
        y[i] = stod(v[1]);
        z[i] = stod(v[2]);

        i++;
        number++;

    }

    ifs.close();

    return number;
}