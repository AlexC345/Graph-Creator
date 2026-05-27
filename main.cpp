#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct vertex{
	string name;
	vector<vertex*> connections;

	bool inConnections(vertex* a){
		for (int i = 0; i < connections.size(); i++){
			if (connections[i] == a){
				return true;
			}
		}
		return false;
	}

	vertex(string n) : name(n) {}
};

struct edge{
	vertex* v1;
	vertex* v2;
	float weight = 0;

	edge(vertex* v1, vertex* v2, float w) : v1(v1), v2(v2), weight(w) {}
};

struct graph{
	vector<vertex*> vertices;
	vector<edge*> edges;

	void addVertex(string name){//adds a vertex
		vertices.push_back(new vertex(name));//adds a vertex to the vector of vertices
	}

	void addEdge(vertex* v1, vertex* v2, float weight){//adds an edge between 2 vertices
		edges.push_back(new edge(v1, v2, weight));//adds an edge to the vector of edges
		v1->connections.push_back(v2);//connects the 2 vertices
		//v2->connections.push_back(v1);
	}

	int getLongestVertexLen(){
		int maxLen = 0;
		for (int i = 0; i < vertices.size(); i++){
			if (vertices[i]->name.length() > maxLen){;
				maxLen = vertices[i]->name.length();
			}
		}
		return maxLen;
	}

	void printTable(){//assumming all vertex names are only 1 letter
		int maxLen = getLongestVertexLen();

		//print first row
		for (int i=0; i<maxLen; i++){
			cout << " ";
		}

		for (int i = 0; i < vertices.size(); i++){
			cout << vertices[i]->name << " ";
		}
		cout << endl;
		//print other rows
		for (int i = 0; i < vertices.size(); i++){
			cout << vertices[i]->name;
			for (int n = 0; n < maxLen - vertices[i]->name.length(); n++){
				cout << " ";
			}

			for (int j = 0; j < vertices.size(); j++){
				cout << vertices[i]->inConnections(vertices[j]);
				for (int k=0; k<maxLen; k++){
					cout << " ";
				}
			}
			cout << endl;
		}
		
	}

	/*
	void removeVertex(string delName){//removes a vertex
		for (int i = 0; i < vertices.size(); i++){//goes through every vertex
			if (vertices[i]->name == delName){//if it has the name to delete:
				vertices.erase(vertices.begin() + i);
			}
		}
	}*/

	vertex* find(string vertexName){//returns a vertex through its name, if it doesn't exist return nullptr
		for (int i = 0; i < vertices.size(); i++){
			if (vertices[i]->name == vertexName){
				return vertices[i];
			}
		}
		return nullptr;
	}
};

int main(){
	string command;
	bool running = true;
	graph* Graph = new graph();

	while(running){
		cout << "Enter command (Add Vertex[AV], Add Edge[AE], Remove Vertex[RV], Remove Edge[RE], Find Shortest Path[FSP], Print Table[P], Quit[Q]): ";
		cin >> command;
		if (command == "AV"){
			string vertexName;
			cout << "Enter vertex name: ";
			cin >> vertexName;
			Graph->addVertex(vertexName);
		}
		else if (command == "AE"){
			cout << "This will only add an edge from vertex 1 to vertex 2, NOT from vertex 2 to vertex 1." << endl;
			string v1name;
			string v2name;
			float weightInput;
			cout << "Enter vertex 1: ";
			cin >> v1name;
			cout << "Enter vertex 2: ";
			cin >> v2name;
			
			vertex* v1 = Graph->find(v1name);
			vertex* v2 = Graph->find(v2name);
			if (v1 and v2){
				cout << "Enter weight: ";
				cin >> weightInput;
				Graph->addEdge(v1, v2, weightInput);
			}
			else{
				cout << "Invalid Vertices!" << endl;
			}

		}
		else if (command == "RV"){
			cout << "RV" << endl;
		}
		else if (command == "RE"){
			cout << "RE" << endl;
		}
		else if (command == "FSP"){
			cout << "FSP" << endl;
		}
		else if (command == "P"){
			Graph->printTable();
		}
		else if (command == "Q"){
			running = false;
		}
		else{
			cout << "Invalid Command!" << endl;
		}
	}
	return 0;
}
