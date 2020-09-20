#ifndef STRUCTURES_SKEL_GRAPH_H
#define STRUCTURES_SKEL_GRAPH_H

#include <algorithm>
#include <iterator>
#include <unordered_map>
#include <unordered_set>
#include "utility/tuple_hash.h"

template<typename Vertex, typename... EdgeTypes>
class Graph {
    using Edge = std::tuple<Vertex, EdgeTypes...>;
    using EdgeSet = std::unordered_set<Edge, std::hash<Edge>>;

    using Graph_t = std::unordered_map<Vertex, EdgeSet>;

public:
    Graph() = default;

    std::unordered_set<Vertex> vertexes() const
    {
        std::unordered_set<Vertex> ret;
        for (const auto& v : graph) {
            ret.insert(v.first);
        }
        return ret;
    }

    bool add(const Vertex& vertex)
    {
        return graph.emplace(vertex, EdgeSet()).second;
    }

    void remove(const Vertex& vertex)
    {
        graph.erase(vertex);
        for (auto& p : graph) {
            auto& edges = p.second;
            auto it = std::begin(edges);
            while (it != std::end(edges)) {
                auto current = it++;
                if (std::get<0>(*current) == vertex) {
                    edges.erase(current);
                }
            }
        }
    }

    bool connect(const Vertex& a, const Vertex& b, EdgeTypes&& ... edge)
    {
        if (graph.find(b) != graph.end()) {
            return graph.at(a).emplace(std::make_tuple(b, edge...)).second;
        }
        throw std::out_of_range("");
    }

    const EdgeSet& connections(const Vertex& vertex) {
        return graph.at(vertex);
    }

    //void disconnect(const Graph_t::iterator& a, const Graph_t::iterator& b);

private:
    Graph_t graph;
};

#endif //STRUCTURES_SKEL_GRAPH_H
