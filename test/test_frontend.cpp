#include "common.hpp"
#include "frontend.hpp"

int main(int argc, char** argv) {
    std::vector<bool> test_results;

    std::cout << "Running KocoaSIFT frontend test..." << std::endl;

    kocoasift::KocoaSIFT app;
    try {
        app.configure(600, 4, 3, 1.60f);
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


    std::cout << "KocoaSIFT initialized with parameters:" << std::endl;
    std::cout << "  nFeatures: " << app.parameters().nFeatures() << std::endl;
    std::cout << "  nOctaves: " << app.parameters().nOctaves() << std::endl;
    std::cout << "  nLayers: " << app.parameters().nLayers() << std::endl;
    std::cout << "  sigma: " << app.parameters().sigma() << std::endl;

    if (std::all_of(test_results.begin(), test_results.end(), [](bool result) { return result; })) {
        std::cout << "All tests passed successfully." << std::endl;
        return 0;
    } else {
        std::cerr << "Some tests failed." << std::endl;
        return 1;
    }

    return 1;
}