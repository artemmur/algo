#pragma once

#include "iGraph.hpp"

class MatrixGraph : public IGraph {
public:
    MatrixGraph(size_t l_verticesNum);
    virtual ~MatrixGraph() = default;
    MatrixGraph(const IGraph& l_graph);

    void AddEdge(size_t l_from, size_t l_to) override;
    size_t VerticesCount() const override;

    std::vector<size_t> GetNextVertices(size_t l_vertex) const override;
    std::vector<size_t> GetPrevVertices(size_t l_vertex) const override;

private:
    std::vector<std::vector<bool>> _vertices;
};
