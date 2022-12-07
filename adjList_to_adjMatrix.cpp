#include <iostream>
#include <fstream>
#include <string>
#include <cstring>

using namespace std;

int main()
{
    int g[20][20];
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 20; j++) {
            g[i][j] = 0;
        }
    }

    fstream f;
    f.open("input.txt", ios_base::in);
    if (!f) return -1;

    int n;
    f >> n;
    f.ignore();

    string str;
    for (int i = 0; i < n; i++) {
        getline(f, str);
        if (str == "") continue;
        while (str.find(" ") != string::npos) {
            string temp = str.substr(0, str.find(" "));
            g[i][stoi(temp)] = 1;
            str = str.substr(str.find(" ") + 1);
        }
        g[i][stoi(str)] = 1;
    }

    f.close();

    f.open("output.txt", ios_base::out);

    f << n << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            f << g[i][j] << " ";
        }
        f << endl;
    }

    f.close();

    return 0;
}
