# Compiler
CXX = g++
CXXFLAGS = -std=c++17 -O2 \
           -I /opt/homebrew/include/eigen3 \
           -I /opt/homebrew/include \
           -I /opt/homebrew/include/opencv4 \
           -I /opt/homebrew/opt/openssl/include

# Linker flags
LDFLAGS = -L /opt/homebrew/lib \
          -L /opt/homebrew/opt/openssl/lib \
          -lsqlite3 -lssl -lcrypto `pkg-config --libs opencv4`

# Target executable
TARGET = minst

# Source files
SRC = main.cpp

# Header dependencies
HEADERS = layer.h neural_network.h functions.h utils.h login.h

all: $(TARGET)

$(TARGET): $(SRC) $(HEADERS)
	$(CXX) $(CXXFLAGS) $(SRC) $(LDFLAGS) -o $(TARGET)

clean:
	rm -f $(TARGET)
