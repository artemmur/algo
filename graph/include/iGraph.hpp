#pragma once

#include <vector>

class IGraph {
public:
    virtual ~IGraph() {}

    virtual void AddEdge(size_t from, size_t to) = 0;
    virtual size_t VerticesCount() const  = 0;

    virtual std::vector<size_t> GetNextVertices(size_t vertex) const = 0;
    virtual std::vector<size_t> GetPrevVertices(size_t vertex) const = 0;
};
