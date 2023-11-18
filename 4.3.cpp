//Act 4.3 Actividad Integradora Grafos
//Carlos Tellez
//Diego Rodríguez Romero
//Sergio Ramirez Anaya
//18 de noviembre de 2023

#include <vector>
#include <iostream>
#include <fstream>
#include <sstream> 

using namespace std;

class Graph
{
private:
  int numVertices;
  int adjMatrix[1000][1000];
  int topValue;
  
  bool *visited;
  int *inDegree;
  int *outDegree;
public:
  Graph(int V)
  {
    numVertices = V;
    visited = new bool[V];
    inDegree = new int[1000]();  
    outDegree = new int[1000](); 
    topValue = 0;
  }
  ~Graph()
  {
    delete []visited;
  }
  void addEdge(int, int);
  void printGraph();

  void updOutDegree(int);

  void top10Ips();
  void topIp();
};



void Graph::addEdge(int s, int d)
{
  if(adjMatrix[s][d] != 1)
    this->adjMatrix[s][d] = 1;
}

vector<int> splitStrings(string &s) {
    vector<int> intSplit;

    string mes, dia, hora, direccionIP;
    char ch1, ch2, ch3;
    int ipPart1, ipPart2, ipPart3, ipPart4;

    stringstream SS(s);
    SS.clear();
    SS >> mes >> dia >> hora >> direccionIP;

    SS.clear();
    SS.str(direccionIP);

    SS >> ipPart1 >> ch1 >> ipPart2 >> ch2 >> ipPart3 >> ch3 >> ipPart4;

    intSplit.push_back(ipPart1);
    intSplit.push_back(ipPart2);
    intSplit.push_back(ipPart3);
    intSplit.push_back(ipPart4);

    return intSplit;
}

void Graph::updOutDegree(int vector){
    this->outDegree[vector] += 1;
}

void readFile(Graph& gr) {
    system("clear");

    ifstream InputFile("bitacora.txt");
    if(!InputFile){
        cerr << "Error opening the input file." << endl;
        return;
    }

    // Read and store each entry in the vector
    string entry;
    while (getline(InputFile, entry)) {
        vector<int> ipParts = splitStrings(entry);

        gr.addEdge(ipParts[0],ipParts[1]);
        //Actualizamos los valores de inDegree y outDegrees
        gr.updOutDegree(ipParts[0]);

        gr.addEdge(ipParts[1],ipParts[2]);
        gr.updOutDegree(ipParts[1]); 

        gr.addEdge(ipParts[2],ipParts[3]);
        gr.updOutDegree(ipParts[2]);
    }

    // Closes the file currently associated
    InputFile.close();
}

void Graph::top10Ips(){
    int top10values[10] = {0};
    int top10index[10] = {0};

    for (int i = 0; i < 1000; ++i) {
        for (int j = 0; j < 10; ++j) {
            if (outDegree[i] > top10values[j]) {
                for (int k = 9; k > j; --k) {
                    top10values[k] = top10values[k - 1];
                    top10index[k] = top10index[k - 1];
                }
                top10values[j] = outDegree[i];
                top10index[j] = i;
                break;
            }
        }
    }

    std::cout << "Nodo - OutDegree\n";
    for (int i = 0; i < 10; ++i) {
        std::cout << top10index[i] << " " << top10values[i] << "\n";
    }

    this->topValue = top10index[0];
}

void Graph::topIp(){
    //system("clear");

    ofstream outputFile("TopIp.txt");
    int top = this->topValue;

    ifstream InputFile("bitacora.txt");
    if(!InputFile){
        cerr << "Error opening the input file." << endl;
    }

    string entry;
    while (getline(InputFile, entry)){
        vector<int> ipParts = splitStrings(entry);

        if(ipParts[0] == top || ipParts[1] == top || ipParts[2] == top){
            outputFile << entry << "\n";
            std::cout << entry << "\n";
        }
    }
    InputFile.close();
    outputFile.close();
}


int main(){
  Graph grafo(1000);
  readFile(grafo);
  std::cout << "Top 10 nodos con más Out Degree\n";
  grafo.top10Ips();

  std::cout << "Segun el conteo hecho en el grafo, el boot master esta localizado en el segmento 60\n";

  std::cout << "\n";
  std::cout << "Todas las Ips de dicho nodo\n";
  grafo.topIp();

  
}
