#include <set>

#include "arcGraph.hpp"

ArcGraph::ArcGraph(size_t l_verticesNum)
    : _vertices(l_verticesNum) {}

ArcGraph::ArcGraph(const IGraph& l_graph) {
    for (size_t i = 0; i < l_graph.VerticesCount(); ++i) {
        std::vector<size_t> nextVertices = l_graph.GetNextVertices(i);
        for (const size_t& vert : nextVertices) {
            AddEdge(i, vert);
        }
    }
}

void ArcGraph::AddEdge(size_t from, size_t to) {
    _vertices.emplace_back(from, to);
}

size_t ArcGraph::VerticesCount() const {
    std::set<size_t> vertices;
    for (const auto& node: _vertices) {
        vertices.emplace(node.from);
    }
    return vertices.size();
}

std::vector<size_t> ArcGraph::GetNextVertices(size_t l_vertex) const {
    std::vector<size_t> nextVert;
    for (const Node& node : _vertices) {
        if (node.from == l_vertex) {
            nextVert.push_back(node.to);
        }
    }
    return nextVert;
}

std::vector<size_t> ArcGraph::GetPrevVertices(size_t l_vertex) const {
    std::vector<size_t> preVert;
    for (const Node& node : _vertices) {
        if (node.to == l_vertex) {
            preVert.push_back(node.from);
        }
    }
    return preVert;
}
