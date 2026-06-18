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
    
    // Variable calls
    const std::vector<std::vector<cv::Mat>>& getAllGaussianPyramid() const;
    const std::vector<std::vector<cv::Mat>>& getAllDoGPyramid() const;

private:
    // Configure parameters
    KocoaSIFTParameters* parameters_;

    // Octave and layer parameter
    int image_width_;
    int image_height_;
    int octaves;
    std::vector<std::vector<int>> octave_resolutions;
    float sigma;
    int gaussian_layers;
    std::vector<float> layer_sigmas;
    std::vector<int> layer_kernel_sizes;
    std::vector<std::vector<float>> layer_kernels;
    std::vector<std::vector<uint8_t>> layer_kernels_uint8;
    float uint8_scale_factor;

    // Gaussian and DoG pyramids
    cv::Mat image_;
    cv::Mat grey_image;
    std::vector<cv::Mat> scale_pyramid;
    std::vector<std::vector<cv::Mat>> gaussian_pyramid;
    std::vector<std::vector<cv::Mat>> gaussian_pyramid_dog;

    // Functions
    void createImagePyramids(const cv::Mat& image);
    void createGaussianLayersAndDoG();
    cv::Mat convolute(const cv::Mat& input, const std::vector<float>& kernel, int kernel_size);

};


}  // namespace kocoasift
