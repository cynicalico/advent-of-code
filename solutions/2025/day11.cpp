/* Day 11: Reactor
 * https://adventofcode.com/2025/day/11
 */

#include "solutions/prototypes.hpp"
#include "utils/utils.hpp"

struct Device {
    std::string name;
    std::vector<Device *> outputs{};

    explicit Device(const std::string_view name)
        : name(std::string(name)) {}
};
using Graph = std::unordered_map<std::string, std::unique_ptr<Device>>;

SOLUTION(2025, 11, (Graph), (std::uint64_t), (std::uint64_t))

Graph AOC_NS(2025, 11)::parse_input(const std::filesystem::path &input_path) {
    Graph graph;
    for (const auto &[_, src, all_outputs] : utils::iter_file_regex<R"((\w+): ([\w ]+))">(input_path)) {
        const auto outputs = utils::split(all_outputs, ' ') | std::ranges::to<std::vector>();
        Graph::iterator src_it;
        if (src_it = graph.find(std::string(src)); src_it == graph.end())
            src_it = graph.emplace_hint(src_it, std::string(src), std::make_unique<Device>(src));
        for (const auto &output : outputs) {
            Graph::iterator output_it;
            if (output_it = graph.find(std::string(output)); output_it == graph.end())
                output_it = graph.emplace_hint(output_it, std::string(output), std::make_unique<Device>(output));
            src_it->second->outputs.emplace_back(output_it->second.get());
        }
    }
    return graph;
}

std::uint64_t
count_paths_out(const Graph &graph, const Device *v, std::unordered_map<const Device *, std::uint64_t> &memo) {
    if (v->name == "out") return 1;

    auto it = memo.find(v);
    if (it == memo.end()) {
        std::uint64_t ans = 0;
        for (const auto &output : v->outputs) ans += count_paths_out(graph, output, memo);
        it = memo.emplace_hint(it, v, ans);
    }
    return it->second;
}

std::uint64_t AOC_NS(2025, 11)::p1(Graph &input) {
    std::unordered_map<const Device *, std::uint64_t> memo;
    return count_paths_out(input, input.at("you").get(), memo);
}

std::uint64_t AOC_NS(2025, 11)::p2(Graph &input) { return 0; }
