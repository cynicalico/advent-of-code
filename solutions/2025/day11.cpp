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

namespace AOC_NS(2025, 11) {
std::uint64_t
count_paths_between(const Device *src, const Device *dst, const std::vector<const Device *> &required_visits = {}) {
    assert(required_visits.size() <= 64);

    std::map<std::pair<const Device *, std::uint64_t>, std::uint64_t> memo;
    auto inner = [&](this auto &&self, const Device *v, std::uint64_t required_flags) -> std::uint64_t {
        if (v == dst && required_flags == (1u << required_visits.size()) - 1) return 1;

        auto it = memo.find({v, required_flags});
        if (it == memo.end()) {
            if (const auto r_it = std::ranges::find(required_visits, v); r_it != required_visits.end())
                required_flags |= 1 << std::distance(required_visits.begin(), r_it);

            std::uint64_t ans = 0;
            for (const auto &output : v->outputs) ans += self(output, required_flags);
            it = memo.emplace_hint(it, std::pair{v, required_flags}, ans);
        }
        return it->second;
    };
    return inner(src, 0);
}
}

std::uint64_t AOC_NS(2025, 11)::p1(Graph &input) { return count_paths_between(input["you"].get(), input["out"].get()); }

std::uint64_t AOC_NS(2025, 11)::p2(Graph &input) {
    const std::vector<const Device *> required_visits = {input["fft"].get(), input["dac"].get()};
    return count_paths_between(input["svr"].get(), input["out"].get(), required_visits);
}
