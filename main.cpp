#include <iostream>
#include <vector>
using namespace std;
void printV(vector<int> &v) {
    for (int i = 0; i < v.size(); i++) {
        cout << v[i] << " ";
    }
    cout << endl;
}
int main() {
    // // Creating an empty vector
    // vector<int> v1;
    //
    // // Creating a vector of 5 elements from
    // // initializer list
    // vector<int> v2 = {1, 4, 2, 3, 5};
    //
    // // Creating a vector of 5 elements with
    // // default value
    // vector<int> v3(5, 9);
    //
    // printV(v1);
    // v1 = v2;
    // printV(v1);
    //
    // printV(v2);
    // printV(v3);
    //
    // cout << v1[0] << endl;
    vector<vector<double>> adjList;
    adjList.push_back({3,1,5,78});
    adjList.push_back({444,3,5,4});
    adjList.push_back({1,1,0.2,4});
    for (int i = 0; i < adjList.size(); i++) {
        for (int j = 0; j < adjList[i].size(); j++) {
            cout << adjList[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}