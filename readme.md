# MNIST Digit Recognizer (Minimal Neural Network)

Small C++ project that trains and evaluates a simple feed‑forward neural network on MNIST-like PNG images. The code uses Eigen for linear algebra, OpenCV for image I/O, and SQLite for a simple console login check.

---

## Features

- Two-layer neural network (one hidden layer + output layer)
- Custom activation functions and training loop (forward / backward)
- Loads PNG images with OpenCV and converts to normalized Eigen vectors
- Simple console login backed by SQLite (`users.db`)
- Train and test routines with accuracy reporting

---

## Requirements (macOS)

- C++17 capable compiler (g++ / clang++)
- Homebrew (recommended) to install deps:
  - Eigen3
  - OpenCV 4
  - sqlite3
  - openssl (used by linker flags in Makefile)
  - pkg-config

Install with Homebrew:

```bash
brew install eigen opencv sqlite openssl pkg-config
```

---

## 🛠️ Project Structure

'''
Neural Network C++/
├─ main.cpp # Entry point of the program
├─ neural_network.cpp
├─ neural_network.h
├─ utils.cpp
├─ utils.h
├─ data/
└─ .gitignore # Files and folders ignored by Git
'''

---

## 📂 Dataset

This project uses the **MNIST handwritten digits dataset**.

---

### How to Download

1. Go to the Kaggle dataset page: [MNIST Dataset](https://www.kaggle.com/datasets/hojjatk/mnist-dataset)
2. Download the dataset as a ZIP file.
3. Extract the contents into the project folder under: data/MNIST/raw directory of project

---

## ⚡ How to Compile and Run

The project comes with a **Makefile** for easy compilation. Open terminal in the project folder and run:

```bash
# Compile the project
make

# Run the executable
./minst
```
