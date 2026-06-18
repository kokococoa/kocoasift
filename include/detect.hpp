#pragma once

#include "common.hpp"
#include "parameters.hpp"

namespace kocoasift {

class KocoaSIFTDetector {
public:
    KocoaSIFTDetector();
    explicit KocoaSIFTDetector(KocoaSIFTParameters* parameters);
    ~KocoaSIFTDetector();

    void process(const cv::Mat& image);

private:
    // Configure parameters
    KocoaSIFTParameters* parameters_;

    // Octave and layer parameters
    float sigma;
    int octaves;
    int gaussian_layers;
    std::vector<float> layer_sigmas;
    std::vector<int> layer_kernel_sizes;
    std::vector<std::vector<float>> layer_kernels;
    std::vector<std::vector<uint8_t>> layer_kernels_uint8;
    float uint8_scale_factor;

    // Gaussian and DoG pyramids
    std::vector<std::vector<cv::Mat>> gaussian_pyramid;
    std::vector<std::vector<cv::Mat>> dog_pyramid;

    // Functions
    void createImagePyramids(const cv::Mat& image);
    void createGaussianLayers();
    void createDoGLayers();

};


}  // namespace kocoasift
