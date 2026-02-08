#pragma once
#include <string>
#include <vector>

struct EurocFramePair
{
    std::string left_path;
    std::string right_path;
    long long timestamp_ns;
};

std::vector<EurocFramePair> load_euroc_stereo_pairs(const std::string& euroc_sequence_root);
