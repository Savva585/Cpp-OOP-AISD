#include "class.h"
#include <iostream>
#include <limits>

using namespace std;

template<typename Vertex>
Vertex find_optimal_warehouse(const Graph<Vertex>& graph)
{
    vector<Vertex> vertices = graph.vertices();
    
    if (vertices.empty())
        return Vertex();
    
    Vertex best = vertices[0];
    double min_average = numeric_limits<double>::max();
    
    for (size_t i = 0; i < vertices.size(); ++i)
    {
        Vertex candidate = vertices[i];
        
        double total_distance = 0.0;      
        size_t reachable_count = 0;        
        
        for (size_t j = 0; j < vertices.size(); ++j)
        {
            Vertex target = vertices[j];
            
            if (candidate == target)
                continue;
            

            vector<typename Graph<Vertex>::Edge> path = graph.shortest_path(candidate, target);
            
            if (!path.empty())
            {
                double path_distance = 0.0;
                for (size_t k = 0; k < path.size(); ++k)
                {
                    path_distance = path_distance + path[k].distance;
                }
                
                total_distance = total_distance + path_distance;
                reachable_count = reachable_count + 1;
            }
        }
        
        if (reachable_count > 0)
        {
            double average = total_distance / (double)reachable_count;
            
            if (average < min_average)
            {
                min_average = average;
                best = candidate;
            }
        }
    }
    
    cout << "\n" << endl;
    cout << "Optimal warehouse location: " << best << endl;
    cout << "Average distance = " << min_average << endl;    
    return best;
}

int main()
{
    cout << "Laboratory Work #3: Graphs (Variant 9)" << endl;
    
    Graph<string> trade_graph;
    
    trade_graph.add_vertex("A");
    trade_graph.add_vertex("B");
    trade_graph.add_vertex("C");
    trade_graph.add_vertex("D");
    trade_graph.add_vertex("E");

    trade_graph.add_edge("A", "B", 4.0);
    trade_graph.add_edge("A", "C", 2.0);
    trade_graph.add_edge("B", "C", 1.0);
    trade_graph.add_edge("B", "D", 5.0);
    trade_graph.add_edge("C", "D", 8.0);
    trade_graph.add_edge("C", "E", 3.0);
    trade_graph.add_edge("D", "E", 2.0);
    trade_graph.add_edge("E", "A", 7.0);
    
    cout << "\n Graph visualization:" << endl;
    trade_graph.print();
    
    
    find_optimal_warehouse(trade_graph);
}