#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <vector>
#include <string>
#include <filesystem>
#include <opencv2/opencv.hpp>
#include <Eigen/Dense>

namespace utils
{

    namespace fs = std::filesystem;

    // Read MNIST images from a folder
    void read_mnist_images(const std::string &folder_path,
                           std::vector<Eigen::VectorXd> &data,
                           std::vector<Eigen::VectorXd> &labels)
    {
        if (!fs::exists(folder_path))
        {
            std::cerr << "Folder does not exist: " << folder_path << std::endl;
            return;
        }

        for (const auto &entry : fs::directory_iterator(folder_path))
        {
            if (entry.is_regular_file())
            {
                std::string file_path = entry.path().string();
                std::string filename = entry.path().filename().string();

                // Extract label from filename (e.g., "0_2.png" -> label = 0)
                int label = filename[0] - '0';

                // Read image as grayscale
                cv::Mat img = cv::imread(file_path, cv::IMREAD_GRAYSCALE);
                if (img.empty())
                {
                    std::cerr << "Cannot read image: " << file_path << std::endl;
                    continue;
                }

                // Flatten image to a vector and normalize
                Eigen::VectorXd img_vec(img.rows * img.cols);
                for (int i = 0; i < img.rows; ++i)
                {
                    for (int j = 0; j < img.cols; ++j)
                    {
                        img_vec(i * img.cols + j) = img.at<uchar>(i, j) / 255.0;
                    }
                }

                // Create one-hot label vector
                Eigen::VectorXd label_vec = Eigen::VectorXd::Zero(10);
                label_vec(label) = 1.0;

                data.push_back(img_vec);
                labels.push_back(label_vec);
            }
        }

        std::cout << "Number of images loaded from " << folder_path << ": " << data.size() << std::endl;
    }

} // namespace utils

#endif // UTILS_H
