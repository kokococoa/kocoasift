#include "common.hpp"
#include "frontend.hpp"

int main(int argc, char** argv) {
    std::vector<bool> test_results;

    std::cout << "Running KocoaSIFT frontend test..." << std::endl;

    // Test KocoaSIFT frontend initialization and parameter configuration
    kocoasift::KocoaSIFT app;
    try {
        app.configure(640, 400, 600, 5, 3, 1.60f);
        app.initialize();
        test_results.push_back(true);  // If no exception, test passed
    }
    catch (const std::exception& e) {
        std::cerr << "Exception occurred during KocoaSIFT frontend test: " << e.what() << std::endl;
        test_results.push_back(false);
    }
    catch (...) {
        std::cerr << "Unknown exception occurred during KocoaSIFT frontend test." << std::endl;
        test_results.push_back(false);
    }

    // Test KocoaSIFT Processing
    // load an image from disk
    cv::Mat test_image = cv::imread("test/test_image_ref.png", cv::IMREAD_GRAYSCALE);
    try {
        // Insert random noise into the image for testing
        std::cout << "Processing" << std::endl;
        app.process(test_image);  // Currently a placeholder; no actual processing implemented
        test_results.push_back(true);  // If no exception, test passed
    }
    catch (const std::exception& e) {
        std::cerr << "Exception occurred during KocoaSIFT processing test: " << e.what() << std::endl;
        test_results.push_back(false);
    }
    catch (...) {
        std::cerr << "Unknown exception occurred during KocoaSIFT processing test." << std::endl;
        test_results.push_back(false);
    }


    std::cout << "KocoaSIFT initialized with parameters:" << std::endl;
    std::cout << "  image_width: " << app.parameters().imageWidth() << std::endl;
    std::cout << "  image_height: " << app.parameters().imageHeight() << std::endl;
    std::cout << "  nFeatures: " << app.parameters().nFeatures() << std::endl;
    std::cout << "  nOctaves: " << app.parameters().nOctaves() << std::endl;
    std::cout << "  nLayers: " << app.parameters().nLayers() << std::endl;
    std::cout << "  sigma: " << app.parameters().sigma() << std::endl;

    // Get all images
    auto all_images =app.detector().getAllGaussianPyramid();
    // Save test image
    cv::imwrite("test/gaussian/test_image.png", test_image);
    // Save all images to disk for inspection
    for (size_t o = 0; o < all_images.size(); ++o) {
        for (size_t l = 0; l < all_images[o].size(); ++l) {
            std::string filename = "test/gaussian/gaussian_pyramid_octave_" + std::to_string(o) + "_layer_" + std::to_string(l) + ".png";
            cv::Mat image_to_save;
            all_images[o][l].convertTo(image_to_save, CV_8UC1, 1.0);  // Convert to 8-bit for saving
            cv::imwrite(filename, image_to_save);
        }
    }
    std::cout << "Saved all Gaussian pyramid images to disk at test/gaussian/" << std::endl;

    if (std::all_of(test_results.begin(), test_results.end(), [](bool result) { return result; })) {
        std::cout << "All tests passed successfully." << std::endl;
        return 0;
    } else {
        std::cerr << "Some tests failed." << std::endl;
        return 1;
    }

    return 1;
}