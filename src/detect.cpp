#include "detect.hpp"

#include <numeric>

namespace kocoasift {

KocoaSIFTDetector::KocoaSIFTDetector() : parameters_(nullptr) {}

KocoaSIFTDetector::KocoaSIFTDetector(KocoaSIFTParameters* parameters)
    : parameters_(parameters) {
    // Store config
    this->sigma = parameters->sigma();
    this->octaves = parameters->nOctaves();
    this->gaussian_layers = parameters->nLayers()+3; // +3 for usable DoG layers

    // Resize kernel storage
    layer_sigmas.resize(gaussian_layers);
    layer_kernel_sizes.resize(gaussian_layers);
    layer_kernels.resize(gaussian_layers);
    layer_kernels_uint8.resize(gaussian_layers);

    // Compute sigma and kernel size
    for (int i = 0; i < gaussian_layers; ++i) {
        float layer_sigma = sigma * std::pow(std::pow(2.0f, 1/3.0f), static_cast<float>(i));
        int kernel_size = static_cast<int>((2*std::ceil(3 * layer_sigma))+1) | 1; // Ensure odd kernel size
        
        layer_sigmas[i] = layer_sigma;
        layer_kernel_sizes[i] = kernel_size;
    }

    // Generate Gaussian 1-D kernels for each layer
    for (int i = 0; i < gaussian_layers; ++i) {
        int ksize = layer_kernel_sizes[i];
        float sigma = layer_sigmas[i];
        std::vector<float>& kernel = layer_kernels[i];
        kernel.resize(ksize);
        float sum = 0.0f;
        int half_size = ksize / 2;
        for (int j = 0; j < ksize; ++j) {
            int x = j - half_size;
            kernel[j] = std::exp(-(x * x) / (2 * sigma * sigma));
            sum += kernel[j]; 
        }
        // Normalize kernel
        for (float& val : kernel) {
            val /= sum;
        }

        // Create uint8 version of the kernel
        std::vector<uint8_t>& kernel_uint8 = layer_kernels_uint8[i];
        kernel_uint8.resize(ksize);
        uint8_scale_factor = 256.0f; // Scale factor to convert float kernel to uint8
        for (int j = 0; j < ksize; ++j) {
            kernel_uint8[j] = static_cast<uint8_t>(std::round(kernel[j] * uint8_scale_factor));
        }

        // Adjust quantization error so the uint8 kernel sum is exactly 256.
        int uint8_sum = std::accumulate(kernel_uint8.begin(), kernel_uint8.end(), 0);
        int diff = 256 - uint8_sum;
        if (diff != 0) {
            std::vector<std::pair<float, int>> sorted_indices(ksize);
            for (int j = 0; j < ksize; ++j) {
                sorted_indices[j] = {kernel[j], j};
            }
            std::sort(sorted_indices.rbegin(), sorted_indices.rend());
            int remaining = std::abs(diff);
            for (int j = 0; remaining > 0; j = (j + 1) % ksize) {
                const int index = sorted_indices[j].second;
                if (diff > 0) {
                    ++kernel_uint8[index];
                    --remaining;
                } else if (kernel_uint8[index] > 0) {
                    --kernel_uint8[index];
                    --remaining;
                }
            }
        }
    }

    // Allocate Gaussian and DoG pyramids
    gaussian_pyramid.resize(octaves);
    dog_pyramid.resize(octaves);
    for (int o = 0; o < octaves; ++o) {
        gaussian_pyramid[o].resize(gaussian_layers);
        dog_pyramid[o].resize(gaussian_layers - 2); // DoG has 2 fewer layers than Gaussian
    }

    // Check kernel sums for each layer
    bool sum_check_passed = true;
    for (int i = 0; i < gaussian_layers; ++i) {
        const float kernel_sum = std::accumulate(
            layer_kernels[i].begin(), layer_kernels[i].end(), 0.0f);
        const int kernel_uint8_sum = std::accumulate(
            layer_kernels_uint8[i].begin(), layer_kernels_uint8[i].end(), 0);
        const float kernel_converted_sum =
            static_cast<float>(kernel_uint8_sum) / uint8_scale_factor;

        const bool kernel_sum_passed = std::abs(kernel_sum - 1.0f) < 1.0e-5f;
        const bool kernel_uint8_sum_passed = kernel_uint8_sum == 256;
        const bool kernel_converted_sum_passed =
            std::abs(kernel_converted_sum - 1.0f) < 1.0e-5f;

        if (!kernel_sum_passed) {
            std::cout << "[detect.cpp] kernel sum check failed: layer " << i
                      << " float kernel sum = " << kernel_sum
                      << ", expected 1" << std::endl;
        }
        if (!kernel_uint8_sum_passed) {
            std::cout << "[detect.cpp] kernel sum check failed: layer " << i
                      << " uint8 kernel sum = " << kernel_uint8_sum
                      << ", expected 256" << std::endl;
        }
        if (!kernel_converted_sum_passed) {
            std::cout << "[detect.cpp] kernel sum check failed: layer " << i
                      << " converted uint8 kernel sum = "
                      << kernel_converted_sum << ", expected 1" << std::endl;
        }

        sum_check_passed &= kernel_sum_passed;
        sum_check_passed &= kernel_uint8_sum_passed;
        sum_check_passed &= kernel_converted_sum_passed;
    }

    std::cout << "[detect.cpp] kernel sum check: "
              << (sum_check_passed ? "PASS" : "FAIL") << std::endl;
}

KocoaSIFTDetector::~KocoaSIFTDetector() = default;

void KocoaSIFTDetector::process(const cv::Mat& image) {
    // Placeholder for processing the image
    // This function will implement the SIFT detection algorithm
}

}  // namespace kocoasift
