#include "euroc_io.hpp"

#include <filesystem>
#include <fstream>
#include <sstream>
#include <stdexcept>

namespace fs = std::filesystem;

static std::vector<std::pair<long long, std::string>> load_cam_csv(const fs::path& csv_path, const fs::path& data_dir)
{
    std::ifstream f(csv_path);
    if (!f.is_open())
    {
        throw std::runtime_error("Could not open: " + csv_path.string());
    }

    std::vector<std::pair<long long, std::string>> out;
    std::string line;
    while (std::getline(f, line))
    {
        if (line.empty()) continue;
        if (line[0] == '#') continue;

        std::stringstream ss(line);
        std::string ts_str;
        std::string filename;

        std::getline(ss, ts_str, ',');
        std::getline(ss, filename, ',');

        if (ts_str.empty() || filename.empty()) continue;

        long long ts = std::stoll(ts_str);
        fs::path p = data_dir / filename;
        out.emplace_back(ts, p.string());
    }
    return out;
}

std::vector<EurocFramePair> load_euroc_stereo_pairs(const std::string& euroc_sequence_root)
{
    fs::path root(euroc_sequence_root);

    fs::path cam0_csv = root / "mav0" / "cam0" / "data.csv";
    fs::path cam1_csv = root / "mav0" / "cam1" / "data.csv";
    fs::path cam0_dir = root / "mav0" / "cam0" / "data";
    fs::path cam1_dir = root / "mav0" / "cam1" / "data";

    auto left = load_cam_csv(cam0_csv, cam0_dir);
    auto right = load_cam_csv(cam1_csv, cam1_dir);

    std::vector<EurocFramePair> pairs;
    const size_t n = std::min(left.size(), right.size());
    pairs.reserve(n);

    for (size_t i = 0; i < n; ++i)
    {
        EurocFramePair p;
        p.timestamp_ns = left[i].first;
        p.left_path = left[i].second;
        p.right_path = right[i].second;
        pairs.push_back(std::move(p));
    }
    return pairs;
}
