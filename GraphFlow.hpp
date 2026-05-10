#ifndef GRAPHFLOW_LITE_GRAPHFLOW_HPP
#define GRAPHFLOW_LITE_GRAPHFLOW_HPP

#include <algorithm>
#include <limits>
#include <queue>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

namespace graphflow {

class Graph {
public:
    struct PathResult {
        double distance;
        std::vector<std::string> path;
    };

    void addNode(const std::string& node) {
        adjacency_[node];
    }

    void addEdge(const std::string& from, const std::string& to, double weight) {
        if (weight < 0.0) {
            throw std::invalid_argument("Dijkstra requires non-negative edge weights.");
        }
        adjacency_[from].push_back({to, weight});
        adjacency_[to];
    }

    void addUndirectedEdge(const std::string& a, const std::string& b, double weight) {
        addEdge(a, b, weight);
        addEdge(b, a, weight);
    }

    PathResult dijkstra(const std::string& source, const std::string& target) const {
        if (!hasNode(source) || !hasNode(target)) {
            throw std::invalid_argument("Source or target node does not exist in graph.");
        }

        const double inf = std::numeric_limits<double>::infinity();
        std::unordered_map<std::string, double> distance;
        std::unordered_map<std::string, std::string> previous;

        for (const auto& entry : adjacency_) {
            distance[entry.first] = inf;
        }
        distance[source] = 0.0;

        using QueueEntry = std::pair<double, std::string>;
        auto cmp = [](const QueueEntry& left, const QueueEntry& right) {
            return left.first > right.first;
        };
        std::priority_queue<QueueEntry, std::vector<QueueEntry>, decltype(cmp)> frontier(cmp);
        frontier.push({0.0, source});

        while (!frontier.empty()) {
            const auto [currentDistance, currentNode] = frontier.top();
            frontier.pop();

            if (currentDistance > distance[currentNode]) {
                continue;
            }
            if (currentNode == target) {
                break;
            }

            for (const auto& [neighbor, weight] : adjacency_.at(currentNode)) {
                const double candidate = currentDistance + weight;
                if (candidate < distance[neighbor]) {
                    distance[neighbor] = candidate;
                    previous[neighbor] = currentNode;
                    frontier.push({candidate, neighbor});
                }
            }
        }

        if (distance[target] == inf) {
            return {inf, {}};
        }

        std::vector<std::string> path;
        std::string step = target;
        while (step != source) {
            path.push_back(step);
            step = previous[step];
        }
        path.push_back(source);
        std::reverse(path.begin(), path.end());

        return {distance[target], path};
    }

private:
    bool hasNode(const std::string& node) const {
        return adjacency_.find(node) != adjacency_.end();
    }

    std::unordered_map<std::string, std::vector<std::pair<std::string, double>>> adjacency_;
};

}  // namespace graphflow

#endif  // GRAPHFLOW_LITE_GRAPHFLOW_HPP
