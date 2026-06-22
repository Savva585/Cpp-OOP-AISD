#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <queue>
#include <unordered_set>
#include <unordered_map>
#include <functional>
#include <limits>
#include <fstream>
#include <string>
using namespace std;
template <typename Vertex>
class Graph
{
public:
    struct Edge
    {
        Vertex from;
        Vertex to;
        double distance;
        
        Edge() : from(), to(), distance(0.0) {}
        Edge(const Vertex& f, const Vertex& t, double d)
            : from(f), to(t), distance(d) {}
    };

private:
    list<pair<Vertex, list<Edge> > > adj_list;
    
    pair<Vertex, list<Edge> >* findVertex(const Vertex& v)
    {
        for (auto& item : adj_list)
        {
            if (item.first == v)
                return &item;
        }
        return nullptr;
    }
    
    const pair<Vertex, list<Edge> >* findVertexConst(const Vertex& v) const
    {
        for (const auto& item : adj_list)
        {
            if (item.first == v)
                return &item;
        }
        return nullptr;
    }

public:
    
    bool has_vertex(const Vertex& v) const
    {
        return findVertexConst(v) != nullptr;
    }
    
    bool add_vertex(const Vertex& v)
    {
        if (has_vertex(v))
            return false;
        
        pair<Vertex, list<Edge> > new_pair;
        new_pair.first = v;
        adj_list.push_back(new_pair);
        return true;
    }
    
    bool remove_vertex(const Vertex& v)
    {
        for (auto it = adj_list.begin(); it != adj_list.end(); ++it)
        {
            if (it->first == v)
            {
                adj_list.erase(it);
                break;
            }
        }
        
        for (auto& item : adj_list)
        {
            for (auto edge_it = item.second.begin(); edge_it != item.second.end();)
            {
                if (edge_it->to == v)
                    edge_it = item.second.erase(edge_it);
                else
                    ++edge_it;
            }
        }
        return true;
    }
    
    vector<Vertex> vertices() const
    {
        vector<Vertex> result;
        for (const auto& item : adj_list)
        {
            result.push_back(item.first);
        }
        return result;
    }
    
    
    void add_edge(const Vertex& from, const Vertex& to, double d)
    {
        if (!has_vertex(from))
            add_vertex(from);
        if (!has_vertex(to))
            add_vertex(to);
        
        pair<Vertex, list<Edge> >* vertex = findVertex(from);
        if (vertex != nullptr)
        {
            Edge new_edge(from, to, d);
            vertex->second.push_back(new_edge);
        }
    }
    
    bool remove_edge(const Vertex& from, const Vertex& to)
    {
        pair<Vertex, list<Edge> >* vertex = findVertex(from);
        if (vertex == nullptr)
            return false;
        
        for (auto& edge : vertex->second)
        {
            if (edge.to == to)
            {
                vertex->second.remove(edge);
                return true;
            }
        }
        return false;
    }
    
    bool remove_edge(const Edge& e)
    {
        pair<Vertex, list<Edge> >* vertex = findVertex(e.from);
        if (vertex == nullptr)
            return false;
        
        for (auto& edge : vertex->second)
        {
            if (edge.to == e.to && edge.distance == e.distance)
            {
                vertex->second.remove(edge);
                return true;
            }
        }
        return false;
    }
    
    bool has_edge(const Vertex& from, const Vertex& to) const
    {
        const pair<Vertex, list<Edge> >* vertex = findVertexConst(from);
        if (vertex == nullptr)
            return false;
        
        for (const auto& edge : vertex->second)
        {
            if (edge.to == to)
                return true;
        }
        return false;
    }
    
    bool has_edge(const Edge& e) const
    {
        const pair<Vertex, list<Edge> >* vertex = findVertexConst(e.from);
        if (vertex == nullptr)
            return false;
        
        for (const auto& edge : vertex->second)
        {
            if (edge.to == e.to && edge.distance == e.distance)
                return true;
        }
        return false;
    }
    
    vector<Edge> edges(const Vertex& vertex) const
    {
        vector<Edge> result;
        const pair<Vertex, list<Edge> >* vertex_data = findVertexConst(vertex);
        if (vertex_data == nullptr)
            return result;
        
        for (const auto& edge : vertex_data->second)
        {
            result.push_back(edge);
        }
        return result;
    }
    
    
    size_t order() const
    {
        return adj_list.size();
    }
    
    size_t degree(const Vertex& v) const
    {
        const pair<Vertex, list<Edge> >* vertex = findVertexConst(v);
        if (vertex == nullptr)
            return 0;
        size_t out_degree = vertex->second.size();
        size_t in_degree = 0;
        for (const auto& item : adj_list)
        {
            for (const auto& edge : item.second)
            {
                if (edge.to == v)
                {
                    in_degree++;
                }
            }
        }
        return out_degree + in_degree;
    }
        
    vector<Vertex> walk(const Vertex& start_vertex,
                        function<void(const Vertex&)> action) const
    {
        if (!has_vertex(start_vertex))
            return vector<Vertex>();
        
        unordered_set<Vertex> visited;
        queue<Vertex> q;
        vector<Vertex> result;
        
        q.push(start_vertex);
        visited.insert(start_vertex);
        
        while (!q.empty())
        {
            Vertex current = q.front();
            q.pop();
            
            action(current);
            result.push_back(current);
            
            const pair<Vertex, list<Edge> >* vertex = findVertexConst(current);
            if (vertex != nullptr)
            {
                for (const auto& edge : vertex->second)
                {
                    if (visited.find(edge.to) == visited.end())
                    {
                        visited.insert(edge.to);
                        q.push(edge.to);
                    }
                }
            }
        }
        return result;
    }
    
    
    vector<Edge> shortest_path(const Vertex& from, const Vertex& to) const
    {
        if (!has_vertex(from) || !has_vertex(to))
            return vector<Edge>();
        unordered_map<Vertex, double> dist;
        unordered_map<Vertex, Edge> prev;
        unordered_set<Vertex> unvisited;
        
        vector<Vertex> verts = vertices();
        for (const auto& v : verts)
        {
            dist[v] = numeric_limits<double>::max();
            unvisited.insert(v);
        }
        dist[from] = 0.0;
        
        while (!unvisited.empty())
        {
            Vertex current;
            double min_dist = numeric_limits<double>::max();
            bool first = true;
            
            for (const auto& v : unvisited)
            {
                if (first || dist[v] < min_dist)
                {
                    min_dist = dist[v];
                    current = v;
                    first = false;
                }
            }
            
            if (min_dist == numeric_limits<double>::max() || current == to)
                break;
            
            unvisited.erase(current);
            
            const pair<Vertex, list<Edge> >* vertex = findVertexConst(current);
            if (vertex != nullptr)
            {
                for (const auto& edge : vertex->second)
                {
                    if (unvisited.find(edge.to) != unvisited.end())
                    {
                        double new_dist = dist[current] + edge.distance;
                        if (new_dist < dist[edge.to])
                        {
                            dist[edge.to] = new_dist;
                            prev[edge.to] = edge;
                        }
                    }
                }
            }
        }
        
        vector<Edge> path;
        if (dist[to] == numeric_limits<double>::max())
            return path;
        
        Vertex current = to;
        while (!(current == from))
        {
            auto it = prev.find(current);
            if (it == prev.end())
                return vector<Edge>();
            path.push_back(it->second);
            current = it->second.from;
        }
        reverse(path.begin(), path.end());
        return path;
    }
    
    
    bool is_connected() const
    {
        if (order() == 0)
            return true;
        
        vector<Vertex> verts = vertices();
        if (verts.empty())
            return true;
        
        unordered_set<Vertex> visited;
        queue<Vertex> q;
        q.push(verts[0]);
        visited.insert(verts[0]);
        
        while (!q.empty())
        {
            Vertex v = q.front();
            q.pop();
            
            const pair<Vertex, list<Edge> >* vertex = findVertexConst(v);
            if (vertex != nullptr)
            {
                for (const auto& e : vertex->second)
                {
                    if (visited.find(e.to) == visited.end())
                    {
                        visited.insert(e.to);
                        q.push(e.to);
                    }
                }
            }
        }
        
        if (visited.size() != order())
            return false;
        
        Graph<Vertex> reversed;
        for (const auto& v : verts)
        {
            reversed.add_vertex(v);
        }
        for (const auto& item : adj_list)
        {
            for (const auto& e : item.second)
            {
                reversed.add_edge(e.to, e.from, e.distance);
            }
        }
        
        unordered_set<Vertex> rev_visited;
        queue<Vertex> rev_q;
        rev_q.push(verts[0]);
        rev_visited.insert(verts[0]);
        
        while (!rev_q.empty())
        {
            Vertex v = rev_q.front();
            rev_q.pop();
            
            for (const auto& e : reversed.edges(v))
            {
                if (rev_visited.find(e.to) == rev_visited.end())
                {
                    rev_visited.insert(e.to);
                    rev_q.push(e.to);
                }
            }
        }
        
        return rev_visited.size() == order();
    }
    
    

    void export_to_json() const
    {
        ofstream json_file("graph_data.json");
        if (!json_file.is_open())
        {
            cout << "Error: cannot create graph_data.json\n";
            return;
        }
        
        vector<Vertex> verts = vertices();
        
        json_file << "{\n";
        json_file << "  \"vertices\": [\n";
        
        for (size_t i = 0; i < verts.size(); ++i)
        {
            json_file << "    \"" << verts[i] << "\"";
            if (i < verts.size() - 1) json_file << ",";
            json_file << "\n";
        }
        
        json_file << "  ],\n";
        json_file << "  \"edges\": [\n";
        
        bool first_edge = true;
        for (const auto& item : adj_list)
        {
            for (const auto& e : item.second)
            {
                if (!first_edge) json_file << ",\n";
                json_file << "    {\n";
                json_file << "      \"from\": \"" << e.from << "\",\n";
                json_file << "      \"to\": \"" << e.to << "\",\n";
                json_file << "      \"weight\": " << e.distance << "\n";
                json_file << "    }";
                first_edge = false;
            }
        }
        
        json_file << "\n  ]\n}\n";
        json_file.close();
        
        cout << "Exported graph to JSON: graph_data.json\n";
    }

    void call_python_visualization() const
    {
        export_to_json();
        
        int result = system("python visualize_graph.py");
        
        if (result != 0)
        {
            cout << " Error: cannot run Python script (make sure Python is installed)\n";
        }
    }
    void print() const
    {
        vector<Vertex> verts = vertices();
        if (verts.empty())
        {
            cout << "Graph is empty\n";
            return;
        }
        
        cout << "\n";
        cout << "                    GRAPH               \n";
        cout << "\n";
        
        cout << "Vertices: ";
        for (const auto& v : verts)
        {
            cout << "[" << v << "] ";
        }
        cout << "\n\n";
        
        cout << "Edges:\n";
        cout << "------\n\n";
        
        for (const auto& item : adj_list)
        {
            if (item.second.empty())
            {
                cout << "  " << item.first << " -> (no outgoing edges)\n";
            }
            else
            {
                for (const auto& e : item.second)
                {
                    cout << "  " << item.first << " ---" << e.distance << "---> " << e.to << "\n";
                }
            }
        }
        cout << "\n";
        
        call_python_visualization();
    }
};

#endif