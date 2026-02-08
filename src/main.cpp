#include "euroc_io.hpp"

#include <opencv2/opencv.hpp>
#include <chrono>
#include <iostream>
#include <string>

static double now_ms()
{
    using clock = std::chrono::steady_clock;
    return std::chrono::duration<double, std::milli>(clock::now().time_since_epoch()).count();
}

int main(int argc, char** argv)
{
    if (argc < 2)
    {
        std::cerr << "Usage:\n";
        std::cerr << "  euroc_demo <path_to_euroc_sequence>\n";
        std::cerr << "Example:\n";
        std::cerr << "  euroc_demo data/euroc/MH_01_easy\n";
        return 1;
    }

    const std::string seq_root = argv[1];
    auto pairs = load_euroc_stereo_pairs(seq_root);

    if (pairs.empty())
    {
        std::cerr << "No frames found. Check your dataset path.\n";
        return 1;
    }

    cv::Ptr<cv::ORB> orb = cv::ORB::create(1000);

    double t_prev = now_ms();
    double fps_smooth = 0.0;

    for (size_t i = 0; i < pairs.size(); ++i)
    {
        const auto& p = pairs[i];

        cv::Mat left = cv::imread(p.left_path, cv::IMREAD_GRAYSCALE);
        if (left.empty())
        {
            std::cerr << "Failed to read: " << p.left_path << "\n";
            continue;
        }

        std::vector<cv::KeyPoint> kps;
        cv::Mat desc;
        orb->detectAndCompute(left, cv::noArray(), kps, desc);

        cv::Mat vis;
        cv::cvtColor(left, vis, cv::COLOR_GRAY2BGR);
        cv::drawKeypoints(left, kps, vis, cv::Scalar(0, 255, 0));

        const double t_now = now_ms();
        const double dt = (t_now - t_prev) / 1000.0;
        t_prev = t_now;

        const double fps = (dt > 0.0) ? (1.0 / dt) : 0.0;
        fps_smooth = (fps_smooth == 0.0) ? fps : (0.9 * fps_smooth + 0.1 * fps);

        const std::string text =
            "Frame " + std::to_string(i) +
            "  kp " + std::to_string((int)kps.size()) +
            "  fps " + std::to_string((int)fps_smooth);

        cv::putText(vis, text, cv::Point(20, 30), cv::FONT_HERSHEY_SIMPLEX, 0.8, cv::Scalar(255, 255, 255), 2);

        cv::imshow("EuRoC ORB demo", vis);
        const int key = cv::waitKey(1);
        if (key == 27) break;
    }

    return 0;
}
