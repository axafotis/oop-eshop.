# Ορισμός μεταβλητών
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Iinclude -Itests
SRC_DIR = src
BUILD_DIR = build
TEST_DIR = tests
BIN = oop24
TEST_BIN = oop24_tests

# Κατάλογος αρχείων
SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SRC_FILES))
TEST_SRC = $(TEST_DIR)/unit_tests.cpp

# Κανόνας για τη μεταγλώττιση του κύριου προγράμματος
$(BIN): $(OBJ_FILES) main.cpp
	@echo "Building main program..."
	$(CXX) $(CXXFLAGS) -o $@ $^

# Κανόνας για τη μεταγλώττιση των tests
$(TEST_BIN): $(OBJ_FILES) $(TEST_SRC)
	@echo "Building test executable..."
	$(CXX) $(CXXFLAGS) -o $@ $^

# Κανόνας για τη μεταγλώττιση των .o αρχείων
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(BUILD_DIR)
	@echo "Compiling $<..."
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Κανόνας για την εκτέλεση των unit tests
test: $(TEST_BIN)
	@echo "Running unit tests..."
	@./$(TEST_BIN)

# Alias για τον κανόνα "test" ώστε να μπορείς να χρησιμοποιείς "make tests"
tests: test

# Κανόνας για την εκτέλεση tests με input αρχείο
test_with_input: $(BIN)
	@echo "Running tests with input files..."
	@./$(BIN) files/categories.txt files/products.txt files/users.txt < $(TEST_DIR)/admin_insert.txt

# Καθαρισμός των μεταγλωττισμένων αρχείων
clean:
	@echo "Cleaning up..."
	@rm -rf $(BUILD_DIR) $(BIN) $(TEST_BIN)
