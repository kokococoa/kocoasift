#include "common.hpp"
#include "frontend.hpp"

#include <filesystem>

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

    const std::string output_dir = "test/dog";
    std::filesystem::create_directories(output_dir);

    const auto& dog_images = app.detector().getAllDoGPyramid();
    cv::imwrite(output_dir + "/test_image.png", test_image);

    for (size_t o = 0; o < dog_images.size(); ++o) {
        for (size_t l = 0; l < dog_images[o].size(); ++l) {
            const std::string filename = output_dir + "/dog_pyramid_octave_" +
                                         std::to_string(o) + "_layer_" +
                                         std::to_string(l) + ".png";
            cv::Mat image_to_save;
            cv::normalize(dog_images[o][l], image_to_save, 0, 255, cv::NORM_MINMAX, CV_8UC1);
            cv::imwrite(filename, image_to_save);
        }
    }
    std::cout << "Saved all DoG pyramid images to disk at " << output_dir << "/" << std::endl;

    if (std::all_of(test_results.begin(), test_results.end(), [](bool result) { return result; })) {
        std::cout << "All tests passed successfully." << std::endl;
        return 0;
    } else {
        std::cerr << "Some tests failed." << std::endl;
        return 1;
    }

    return 1;
}
