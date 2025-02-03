#include <fstream>
#include <sstream>

#include "Graph.h"

using namespace std;
constexpr unsigned int SIZE_OF_FLAG = 2;

void PrintConnected(const vector<string> &vec);

bool ValidateFile(const string &fileName);

void AddToGraph(const string &fileName, Graph<string> &graph);

void OutputGraph(const string &output_name, const Graph<string> &graph);

void SearchConnectedNodes(const Graph<string> &graph);

int main(const int argc, char **argv) {
    // validate files
    string output_file = "output.txt";
    for (int i = 1; i < argc; i++) {
        string fileName = argv[i];
        if (fileName[0] == '-' && fileName[1] == 'o') {
            string flag = fileName.substr(0, SIZE_OF_FLAG);
            output_file = fileName.substr(SIZE_OF_FLAG);
            // if the -o flag was called, the output file name will change accordingly
            continue;
        }
        try {
            ValidateFile(fileName);
        } catch (const string &e) {
            cerr << e;
            return 1;
        }
    }
    // build graph
    Graph<string> g;
    for (int i = 1; i < argc; i++) {
        string fileName = argv[i];
        AddToGraph(fileName, g);
    }
    // make output file
    OutputGraph(output_file, g);
    // start user interaction
    SearchConnectedNodes(g);

    return 0;
}

void PrintConnected(const vector<string> &vec) {
    for (unsigned int i = 0; i < vec.size(); i++) {
        cout << vec[i];
        if (i != vec.size() - 1) {
            cout << "\t";
        }
    }
    cout << endl;
}

bool ValidateFile(const string &fileName) {
    ifstream input_file(fileName);
    if (!input_file.is_open()) {
        string errMsg = "ERROR: " + fileName + " does not exist or cannot be opened\n";
        throw string(errMsg);
    }
    string errMsg = "ERROR: node definition in " + fileName + " is invalid\n";

    string line;
    while (getline(input_file, line)) {
        stringstream ss(line);
        if (line.find(' ') != string::npos) {
            input_file.close();
            throw string(errMsg);
        }
        string source;
        string target;
        string minuets_str;
        unsigned int minutes;
        if (!(ss >> source >> target >> minuets_str)) {
            input_file.close();
            throw string(errMsg);
        }
        string extra;
        if (ss >> extra) {
            input_file.close();
            throw string(errMsg);
        }
        if (source == "exit" || target == "exit") {
            input_file.close();
            throw string(errMsg);
        }
        if (source.length() > 16 || target.length() > 16) {

            input_file.close();
            throw string(errMsg);
        }
        for (char ch: source) {
            if (!isalpha(ch)) {
                input_file.close();
                throw string(errMsg);
            }
        }
        for (char ch: target) {
            if (!isalpha(ch)) {
                input_file.close();
                throw string(errMsg);
            }
        }
        for (char ch: minuets_str) {
            if (!isdigit(ch)) {
                input_file.close();
                throw string(errMsg);
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
        string errMsg = "ERROR: " + output_name + " does not exist or cannot be opened\n";
        throw string(errMsg);
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
            vector<string> connected_nodes = graph.GetConnected(source);
            if (connected_nodes.empty()) {
                cout << source << " : no outbound travel" << endl;
            } else {
                cout << source << '\t';
                PrintConnected(connected_nodes);
            }
        }
    }
}
