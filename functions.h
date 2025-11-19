#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <iostream>
#include <Eigen/Dense>
#include <cmath>

using namespace Eigen;

namespace functions
{
    // Sigmoid activation function
    VectorXd sigmoid(const VectorXd &v)
    {
        return 1.0 / (1.0 + (-v.array()).exp());
    }

    // Derivative of sigmoid
    VectorXd sigmoid_derivative(const VectorXd &v)
    {
        VectorXd sig = sigmoid(v);
        return sig.array() * (1.0 - sig.array());
    }

    // ReLU activation function - FIX for vanishing gradient
    VectorXd relu(const VectorXd &v)
    {
        return v.array().max(0.0);
    }

    // Derivative of ReLU
    VectorXd relu_derivative(const VectorXd &v)
    {
        VectorXd result(v.size());
        for (int i = 0; i < v.size(); i++)
        {
            result(i) = v(i) > 0 ? 1.0 : 0.0;
        }
        return result;
    }

    // Softmax activation - BETTER for output layer
    VectorXd softmax(const VectorXd &v)
    {
        VectorXd exp_values = v.array().exp();
        double sum = exp_values.sum();
        return exp_values / sum;
    }

    // Derivative of softmax (simplified for cross-entropy)
    VectorXd softmax_derivative(const VectorXd &v)
    {
        // For cross-entropy loss, this simplifies significantly
        VectorXd soft = softmax(v);
        return soft.array() * (1.0 - soft.array());
    }

    // Mean Squared Error - current error function
    double error_function(const VectorXd &output, const VectorXd &target)
    {
        return 0.5 * (output - target).squaredNorm();
    }

    // Derivative of MSE error
    VectorXd error_function_derivative(const VectorXd &output, const VectorXd &target)
    {
        return output - target;
    }

    // Cross-Entropy Loss - BETTER for classification
    double cross_entropy_loss(const VectorXd &output, const VectorXd &target)
    {
        double loss = 0.0;
        for (int i = 0; i < output.size(); i++)
        {
            // Add small epsilon to avoid log(0)
            loss += target(i) * std::log(output(i) + 1e-15);
        }
        return -loss;
    }

    // Derivative of cross-entropy with softmax (simplified)
    VectorXd cross_entropy_derivative(const VectorXd &output, const VectorXd &target)
    {
        return output - target;
    }

    // Leaky ReLU - avoids "dead neurons" issue
    VectorXd leaky_relu(const VectorXd &v, double alpha = 0.01)
    {
        VectorXd result(v.size());
        for (int i = 0; i < v.size(); i++)
        {
            result(i) = v(i) > 0 ? v(i) : alpha * v(i);
        }
        return result;
    }

    // Derivative of Leaky ReLU
    VectorXd leaky_relu_derivative(const VectorXd &v, double alpha = 0.01)
    {
        VectorXd result(v.size());
        for (int i = 0; i < v.size(); i++)
        {
            result(i) = v(i) > 0 ? 1.0 : alpha;
        }
        return result;
    }

    // Tanh activation - alternative to sigmoid
    VectorXd tanh_activation(const VectorXd &v)
    {
        return v.array().tanh();
    }

    // Derivative of tanh
    VectorXd tanh_derivative(const VectorXd &v)
    {
        VectorXd tanh_val = v.array().tanh();
        return 1.0 - tanh_val.array().square();
    }
}

#endif // FUNCTIONS_H