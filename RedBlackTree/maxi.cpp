#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
    string pattern, text;

    while (cin >> pattern) {
        cin >> text;

        vector<int> positions;
        size_t pos = 0;

        while ((pos = text.find(pattern, pos)) != string::npos) {
            positions.push_back(pos);
            pos++;
        }

        for (int i = 0; i < positions.size(); i++) {
            cout << positions[i];
            if (i < positions.size() - 1) {
                cout << " ";
            }
        }

        cout << endl;
    }

    return 0;
}
