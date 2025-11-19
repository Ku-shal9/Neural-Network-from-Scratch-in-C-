#include <iostream>
#include <Eigen/Dense>
#include <ctime> // needed for time(0) used with srand

#include "layer.h"
#include "functions.h"
#include "neural_network.h"
#include "utils.h"
#include "login.h"

// Use Eigen types without prefixing with Eigen::
using namespace Eigen;
// Keep function pointers from functions namespace handy
using namespace functions;

int main()
{
    // Simple login retry loop: allow up to 3 attempts to authenticate against users.db.
    // This is intentionally rudimentary (no backoff, no lockout except after 3 failures).
    int attempts = 0;
    while (attempts < 3)
    {
        // login_database returns true if credentials are valid.
        if (login_database("users.db"))
            break; // success -> continue to program
        attempts++;
        if (attempts == 3)
        {
            std::cout << "Too many failed login attempts. Exiting.\n";
            return 0; // exit early on repeated failures
        }
    }

    // Greeting for the user. Minimal UI here — just console messages.
    std::cout << "Welcome to MNIST Digit Recognizer!\n";

    // Seed the random number generator for weight initialization / random choices.
    // Using time(0) gives a different seed each run; include <ctime> above for portability.
    srand(time(0));

    // Containers for image data and one-hot labels.
    // Each VectorXd represents flattened image pixels or a one-hot label vector.
    std::vector<Eigen::VectorXd> train_data, train_labels;
    std::vector<Eigen::VectorXd> test_data, test_labels;

    // Paths to reorganized PNG folders (adjust these if your dataset is elsewhere).
    // These should contain subfolders named by digit (0-9) if utils::read_mnist_images expects that.
    std::string train_folder = "/Users/kushalthapa/Desktop/Neural Network - Dataset/data/MNIST/raw/mnist_png/train";
    std::string test_folder = "/Users/kushalthapa/Desktop/Neural Network - Dataset/data/MNIST/raw/mnist_png/test";

    std::cout << "Loading training images...\n";
    // Read images and labels into the vectors above. Implementation details live in utils::read_mnist_images.
    utils::read_mnist_images(train_folder, train_data, train_labels);

    std::cout << "Loading test images...\n";
    utils::read_mnist_images(test_folder, test_data, test_labels);

    // Quick sanity output so we know how many images were loaded.
    std::cout << "Number of training images: " << train_data.size() << std::endl;
    std::cout << "Number of testing images: " << test_data.size() << std::endl;

    // Construct network layers:
    // - hidden_layer: input size 784 (28x28 flattened), 64 neurons in hidden layer.
    //   Uses sigmoid activation and its derivative for both forward and backward passes.
    // - output_layer: 64 inputs (from hidden layer), 10 outputs (digits 0-9).
    // Note: using sigmoid everywhere is simple but not necessarily optimal for deep nets.
    Layer hidden_layer(784, 64, sigmoid, sigmoid_derivative);
    Layer output_layer(64, 10, sigmoid, sigmoid_derivative);

    // Build the network from the layers above. The NeuralNetwork constructor should
    // take ownership/copy of the layer objects and prepare any required internal state.
    NeuralNetwork nn({hidden_layer, output_layer});

    // Train the network:
    // - training data and labels,
    // - learning rate 0.01,
    // - 10 epochs.
    // Depending on implementation, training may be batch/mini-batch/stochastic; check nn.train.
    nn.train(train_data, train_labels, 0.01, 10);

    // Evaluate on test set and print results (accuracy, confusion, etc. depending on nn.test impl).
    nn.test(test_data, test_labels);

    return 0;
}
