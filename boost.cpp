//Sa�l Enrique Labra Cruz A01020725
//Grafos - Boost
//15/10/2017

#include <iostream>
#include <boost/graph/adjacency_list.hpp> // incluye la lista de adyacencia
#include <boost/graph/graph_traits.hpp> // incluye las propiedades
#include <boost/graph/graphviz.hpp> // incluye la funci�n de impresi�n
#include <stack>
#include <map>
#include <queue>
#include <vector>
#include <iostream>
#include <chrono>
#include <boost/tuple/tuple.hpp> // incluye la funcionalidad "tie" para crear tuplas
#include <boost/graph/breadth_first_search.hpp>

using namespace boost;
using namespace std;
using namespace std::chrono;

typedef property<edge_weight_t, int> EdgeWeightProperty; // se define la porpiedad de arista pesada con un valor entero
typedef adjacency_list<listS, vecS, directedS, no_property, EdgeWeightProperty> grafo_direccional_pesado; // se define un tipo de variable con el nombre grafo_dirigido
typedef boost::adjacency_list<boost::vecS, boost::hash_setS, boost::undirectedS, uint32_t, uint32_t, boost::no_property> graph_t;
typedef boost::property<boost::edge_weight_t, int> EdgeWeightProperty;

typedef boost::graph_traits<grafo_direccional_pesado>::out_edge_iterator oe_it;
typedef boost::graph_traits<grafo_direccional_pesado>::edge_iterator e_it;
typedef boost::graph_traits<grafo_direccional_pesado>::vertex_iterator v_it;
typedef boost::graph_traits<grafo_direccional_pesado>::vertex_descriptor Vertex;
typedef boost::graph_traits<grafo_direccional_pesado>::edge_descriptor Edge;


grafo_direccional_pesado g(13);
void agregaArista(int s, int d, int w, grafo_direccional_pesado &a);
void eliminaNodo(int cual, grafo_direccional_pesado &a);
void agregaNodo(grafo_direccional_pesado &grafo);
void eliminaArista(int s, int d, grafo_direccional_pesado &graf);
void agregaAristaBi(int s, int d, int w, grafo_direccional_pesado &a);
void dfs(grafo_direccional_pesado &a, unsigned long startingNode);
void bfs(grafo_direccional_pesado &a, unsigned long startingNode);
vector<std::tuple<Vertex, Vertex, int>> kruskal(grafo_direccional_pesado g);
vector<pair<Vertex, int>> prim(grafo_direccional_pesado g, int vertexStart);
vector<pair<int, Vertex>> dijkstra(grafo_direccional_pesado g, unsigned long initialNode);
vector<vector<int>> floydWarshall(grafo_direccional_pesado g);

struct oper{
    bool operator()(const std::tuple<int,Vertex, Vertex>& one, const std::tuple<int,Vertex, Vertex>& two)
    {
        return std::get<0>(one) > std::get<0>(two);
    }
};

struct oper2{
    bool operator()(const Edge& one, const Edge& two){
        return boost::get(boost::edge_weight_t(), g, one) > boost::get(boost::edge_weight_t(), g, two);
    }
};
int main()
{
    agregaArista(0 ,2, 8, g);
    agregaArista(0, 3, 8, g);// funci�n que a�ade arista pesada al grafo g
    agregaArista(2, 1, 7, g);
    agregaArista(2, 9, 4, g);
    agregaArista(2, 4, 8, g);
    agregaArista(1, 4, 7, g);
    agregaArista(3, 7, 2, g);
    agregaArista(3, 6, 3, g);
    agregaArista(3, 4, 1, g);
    agregaArista(4, 5, 9, g);
    agregaArista(5, 12, 4, g);
    agregaArista(6, 3, 6, g);

    agregaArista(7, 6, 3, g);
    agregaArista(7, 8, 3, g);
    agregaArista(8, 9, 2, g);
    agregaArista(8, 11, 4, g);
    agregaArista(9, 2, 10, g);
    agregaArista(9, 5, 6, g);
    agregaArista(10, 11, 6, g);
    agregaArista(11, 8, 2, g);
    agregaArista(11, 10, 8, g);
    agregaArista(11, 13, 9, g);
    agregaArista(12, 13, 6, g);
    agregaArista(13,12,12,g);

    eliminaArista(12,13,g);

    agregaNodo(g); // funci�n que a�ade vertices nuevos al grafo con un nuevo �ndice (hace push_back al vector)
    //add_edge(22, 12, 2, g);
    /*eliminaNodo(6, g);
    eliminaNodo(1, g);
    eliminaNodo(2, g);
    eliminaNodo(3, g);
    eliminaNodo(4, g);
    eliminaNodo(5, g);
    eliminaNodo(6, g);
    eliminaNodo(7, g);
    eliminaNodo(8, g);
    eliminaNodo(9, g);
    eliminaNodo(10, g);*/

    graph_traits<grafo_direccional_pesado>::vertex_iterator vi, vi_fin, sig; // se crean los iteradores
    tie(vi, vi_fin) = vertices(g); // se obtiene el iterador inicial y fianl para el grafo g


    write_graphviz(cout, g);

    bfs(g, 0);

    high_resolution_clock::time_point t1 = high_resolution_clock::now();
    dfs(g,0);

    vector<pair<Vertex, int>> Prim = prim(g, 0); //Se obtiene un vector de pares

    vector<std::tuple<Vertex, Vertex, int>> Kruskal = kruskal(g); // Se obtiene una tupla de vertices y enteros

    vector<pair<int, Vertex>> Dijkstra = dijkstra(g,1); // Se obtienen las distancias m�nimas de un nodo a los dem�s por medio de Dijkstra

    vector<vector<int>> FloydWarhsall = floydWarshall(g); // Se obtiene un vector de vectores de enteros con la distancia menor de todos los vertices a todos los vertices

    auto duration = duration_cast<microseconds>( t2 - t1 ).count();

    cout << "tiempo: " << duration << " microseconds" << endl;

    return 0;
}
void agregaArista(int s, int d, int w, grafo_direccional_pesado &a)
{
     add_edge(s, d, w, a);
}
void agregaAristaBi(int s, int d, int w, grafo_direccional_pesado &a){
    add_edge(s,d,w,a);
    add_edge(d,s,w,a);
}
void eliminaArista(int s, int d, grafo_direccional_pesado &graf)
{

    remove_edge(s,d,graf);
}
void eliminaNodo(int cual, grafo_direccional_pesado &a)
{
    remove_vertex(cual, a);
}
void agregaNodo(grafo_direccional_pesado &grafo)
{

    add_vertex(grafo);
}
void dfs(grafo_direccional_pesado &a, unsigned long startingNode){
    stack<Vertex> visiting;
    map<Vertex,bool> travelled;
    Vertex checking = a.vertex_set()[startingNode];
    visiting.push(checking);
    travelled[checking] = true;
    while(!visiting.empty()){
        checking = visiting.top();
        visiting.pop();
        pair<oe_it,oe_it> iterators = out_edges(checking,a);
        for(oe_it it = iterators.first; it != iterators.second; ++it){
            Vertex target = boost::target(*it,a);
            if(travelled[target]) continue;
            travelled[target] = true;
            visiting.push(target);
        }
        cout << checking << "-";

    }
    cout<<"\n";

}

void bfs(grafo_direccional_pesado &a, unsigned long startingNode){
    std::queue<Vertex> visiting;
    map<Vertex,bool> travelled;
    Vertex checking = a.vertex_set()[startingNode];
    visiting.push(checking);
    travelled[checking] = true;
    while(!visiting.empty()){
        checking = visiting.front();
        visiting.pop();
        pair<oe_it,oe_it> iterators = out_edges(checking,a);
        for(oe_it it = iterators.first; it != iterators.second; ++it){
            Vertex target = boost::target(*it,a);
            if(travelled[target]) continue;
            travelled[target] = true;
            visiting.push(target);
        }
        cout << checking << "-";

    }
    cout<<"\n";

}

vector<pair<Vertex, int>> prim(grafo_direccional_pesado g, int vertexStart){
    vector<pair<Vertex, int>> result;
    priority_queue<std::tuple<int,Vertex,Vertex>,vector<std::tuple<int,Vertex, Vertex>>, oper> next;
    map<Vertex,bool> travelled;
    std::tuple<int,Vertex,Vertex> now;
    int weight;
    pair<v_it,v_it> iterators = vertices(g);
    Vertex checking = g.vertex_set()[vertexStart];
    for(v_it it = iterators.first; it != iterators.second; ++it){
        result.push_back(make_pair(-1, INT32_MIN));
    }
    result[checking].second = 0;
    next.push(make_tuple(0,checking,checking));
    while(!next.empty()){
        now = next.top();
        next.pop();
        checking = std::get<1>(now);
        if(travelled[checking]) continue;
        travelled[checking] = true;
        result[checking] = make_pair(std::get<2>(now), std::get<0>(now));
        pair<oe_it,oe_it> oeIt = out_edges(checking,g);
        for(oe_it it = oeIt.first; it != oeIt.second; ++it){
            Vertex target = boost::target(*it,g);
            if(travelled[target]) continue;
            //std::pair<Edge,bool> a = boost::edge(checking,std::get<2>(now), g);
            weight = boost::get(boost::edge_weight_t(),g, *it);
            next.push(make_tuple(weight,target,checking));
        }

    }
    return result;

}

vector<std::tuple<Vertex, Vertex, int>> kruskal(grafo_direccional_pesado g){
    vector<vector<int>*> travelled;
    vector<std::tuple<Vertex, Vertex, int>> result;
    priority_queue<Edge, vector<Edge>, oper2> next;
    pair<v_it,v_it> iterators = vertices(g);
    int counter = 0;
    Edge checking;
    Vertex source, target;
    for(v_it it = iterators.first; it != iterators.second; ++it){
        vector<int>* a = new vector<int>;
        a->push_back(counter);
        travelled.push_back(a);
        //result.push_back(make_tuple(source, source, INT32_MIN));
        ++counter;
    }
    pair<e_it,e_it> edIt = edges(g);
    for(e_it it = edIt.first; it != edIt.second; ++it){
        std::pair<Edge,bool> a = boost::edge(boost::source(*it,g),boost::target(*it,g), g);
        next.push(a.first);
    }
    while(!next.empty()){
        checking = next.top();
        source = boost::source(checking,g);
        target = boost::target(checking,g);
        next.pop();
        if(*travelled[source] == *travelled[target]) continue;
        vector<int> add;
        for(vector<int>::iterator it = travelled[target]->begin(); it != travelled[target]->end(); ++it){
            travelled[source]->push_back(*it);
            add.push_back(*it);
        }
        for(vector<int>::iterator it = add.begin(); it != add.end(); ++it){
            travelled[*it] = travelled[source];
        }
        /*
        for(int i = 0; i < travelled.size(); ++i){
            for(vector<int>::iterator it = travelled[i]->begin(); it != travelled[i]->end(); ++it){
                cout << *it << " ";
            }
            cout << "\n";
        }*/
        result.push_back(make_tuple(source,target, boost::get(boost::edge_weight_t(), g, checking)));
    }
    return result;

}

vector<pair<int, Vertex>> dijkstra(grafo_direccional_pesado g, unsigned long initialNode){
    vector<pair<int, Vertex>> distances;
    map<Vertex, bool> visited;
    priority_queue<std::tuple<int,Vertex,Vertex>, vector<std::tuple<int,Vertex,Vertex>>,oper> next;
    std::tuple<int,Vertex,Vertex> checking;
    Vertex source, target;
    int weight, checkingWeight;
    pair<v_it,v_it> iterators = vertices(g);
    for(v_it it = iterators.first; it != iterators.second; ++it){
        distances.push_back(make_pair(INT_MAX, -1));
    }
    distances[initialNode].first = 0;
    next.push(std::make_tuple(0,initialNode,initialNode));
    while(!next.empty()){
        checking = next.top();
        next.pop();
        target = std::get<2>(checking);
        source = std::get<1>(checking);
        if(visited[target]) continue;
        visited[target] = true;
        checkingWeight = std::get<0>(checking);
        if(distances[target].first < checkingWeight) continue;
        distances[target] = make_pair(checkingWeight,source);
        pair<oe_it,oe_it> oeIt = out_edges(target,g);
        for(oe_it it = oeIt.first; it != oeIt.second; ++it){
            Vertex newTarget = boost::target(*it,g);
            if(visited[newTarget]) continue;
            weight = boost::get(boost::edge_weight_t(),g, *it);
            next.push(make_tuple(distances[target].first + weight,target,newTarget));
        }
    }

    return distances;

}

vector<vector<int>> floydWarshall(grafo_direccional_pesado g){
    vector<vector<int>> distances;
    unsigned long vNum = num_vertices(g);
    distances.resize(vNum);
    pair<v_it,v_it> iterators = vertices(g);
    for(v_it it = iterators.first; it != iterators.second; ++it){
        for(v_it it2 = iterators.first; it2 != iterators.second; ++it2){
            if(it == it2){
                distances[*it].push_back(0);
                continue;
            }
            else distances[*it].push_back(100000);
        }
    }
    pair<e_it,e_it> edIt = edges(g);
    for(e_it it = edIt.first; it != edIt.second; ++it){
        distances[boost::source(*it,g)][boost::target(*it,g)] = boost::get(boost::edge_weight_t(),g, *it);
    }

    for(int k = 0; k < vNum; ++k){
        for(int i = 0; i < vNum; ++i){
            for(int j = 0; j < vNum; ++j){
                if(distances[i][j] > distances[i][k] + distances[k][j])
                    distances[i][j] = distances[i][k] + distances[k][j];
            }
        }
    }

    return distances;

}
