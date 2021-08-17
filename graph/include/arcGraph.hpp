#pragma once

#include "iGraph.hpp"

struct Node {
    size_t from;
    size_t to;
    Node(const size_t l_from, const size_t l_to) :
            from(l_from),
            to(l_to) {}

    Node() :
            from(0),
            to(0) {}
};

class ArcGraph : public IGraph {
public:
    ArcGraph(size_t num_vertices);
    virtual ~ArcGraph() = default;
    ArcGraph(const IGraph& l_graph);

    void AddEdge(size_t from, size_t to) override;
    size_t VerticesCount() const override;

    std::vector<size_t> GetNextVertices(size_t vertex) const override;
    std::vector<size_t> GetPrevVertices(size_t vertex) const override;

private:
    std::vector<Node> _vertices;
};
