#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>

#include "Graph.h"
using namespace std;

void PrintConnected(const set<string> &s);

bool ValidateFile(const string &fileName);

void AddToGraph(const string &fileName, Graph<string> &graph);

void OutputGraph(const string &output_name, const Graph<string> &graph);

void SearchConnectedNodes(const Graph<string> &graph);

int main(const int argc, char **argv) {
    string output_file = "output.txt";
    for (int i = 1; i < argc; i++) {
        string fileName = argv[i];
        if (fileName[0] == '-' && fileName[1] == 'o') {
            string flag = fileName.substr(0, 2);
            string name;
            output_file = fileName.substr(flag.length());
            continue;
        }
        try {
            ValidateFile(fileName);
        } catch (const string &e) {
            cerr << e << endl;
            return 1;
        }
    }
    Graph<string> g;
    for (int i = 1; i < argc; i++) {
        string fileName = argv[i];
        AddToGraph(fileName, g);
    }
    OutputGraph(output_file, g);
    SearchConnectedNodes(g);

    return 0;
}

void PrintConnected(const set<string> &s) {
    for (const auto &it: s) {
        cout << it << "\t";
    }
    cout << endl;
}

bool ValidateFile(const string &fileName) {
    ifstream input_file(fileName);
    if (!input_file.is_open()) {
        return false;
    }
    string line;
    while (getline(input_file, line)) {
        stringstream ss(line);
        if (line.find(' ') != string::npos) {
            input_file.close();
            throw string("Invalid input");
        }
        string source;
        string target;
        string minuets_str;
        unsigned int minutes;
        if (!(ss >> source >> target >> minuets_str)) {
            input_file.close();
            throw string("Invalid input");
        }
        string extra;
        if (ss >> extra) {
            input_file.close();
            throw string("Invalid input");
        }
        if (source == "exit" || target == "exit") {
            input_file.close();
            throw string("Invalid input");
        }
        if (source.length() >= 16 || target.length() >= 16) {
            input_file.close();
            throw string("Invalid input");
        }
        for (char ch: minuets_str) {
            if (!isdigit(ch)) {
                input_file.close();
                throw string("Invalid input");
            }
        }
        stringstream min(minuets_str);
        min >> minutes;
    }
    input_file.close();
    return true;
}

void AddToGraph(const string &fileName, Graph<string> &graph) {
    ifstream input_file(fileName);
    string line;
    while (getline(input_file, line)) {
        stringstream ss(line);
        string source;
        string target;
        unsigned int minutes;
        ss >> source >> target >> minutes;
        graph.AddEdge(source, target, minutes);
    }
}

void OutputGraph(const string &output_name, const Graph<string> &graph) {
    ofstream outfile(output_name);
    if (!outfile.is_open()) {
        outfile.close();
        return;
    }
    outfile << graph << endl;
    outfile.close();
}

void SearchConnectedNodes(const Graph<string> &graph) {
    string line;
    while (getline(cin, line)) {
        stringstream ss(line);
        string source;
        ss >> source;
        if (source == "exit") {
            return;
        }
        if (graph.getVertexIndex(source) == -1) {
            cout << source << " does not exist in the current network" << endl;
            cout << "USAGE: <node> or 'exit' to terminate" << endl;
        } else {
            set<string> connected_nodes = graph.GetConnected(source);
            if (connected_nodes.empty()) {
                cout << source << " : no outbound travel" << endl;
            } else {
                cout << source << '\t';
                PrintConnected(connected_nodes);
            }
        }
    }
}
