#include "matrixGraph.hpp"

MatrixGraph::MatrixGraph(size_t l_verticesNum) :
        _vertices(l_verticesNum, std::vector<bool>(l_verticesNum, false)) {}

MatrixGraph::MatrixGraph(const IGraph& l_graph) :
        _vertices(l_graph.VerticesCount(), std::vector<bool>(l_graph.VerticesCount(), false)) {

    for (size_t i = 0; i < _vertices.size(); ++i) {
        std::vector<size_t> nextVertices = l_graph.GetNextVertices(i);
        for (size_t& vert : nextVertices) {
            AddEdge(i, vert);
        }
    }
}

void MatrixGraph::AddEdge(size_t l_from, size_t l_to) {
    _vertices[l_from][l_to] = true;
}

size_t MatrixGraph::VerticesCount() const {
    return _vertices.size();
}

std::vector<size_t> MatrixGraph::GetNextVertices(size_t l_vertex) const {
    std::vector<size_t> nextVertices;
    const auto& line = _vertices[l_vertex];
    for (size_t i = 0; i < _vertices.size(); ++i) {
        if (line[i]) {
            nextVertices.push_back(i);
        }
    }
    return nextVertices;
}

std::vector<size_t> MatrixGraph::GetPrevVertices(size_t l_vertex) const {
    std::vector<size_t> preVertices;
    for (size_t i = 0; i < _vertices.size(); ++i) {
        if (_vertices[i][l_vertex]) {
            preVertices.push_back(i);
        }
    }
    return preVertices;
}
