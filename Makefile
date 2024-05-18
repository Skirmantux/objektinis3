CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -O2
SRC_DIR_DEQUE = v1.0_deque
SRC_DIR_LIST = v1.0_list
SRC_DIR_VECTOR = v1.0_vector
OBJ_DIR = build
EXECUTABLE_DEQUE = deque
EXECUTABLE_LIST = list
EXECUTABLE_VECTOR = vector

SRCS_DEQUE = $(wildcard $(SRC_DIR_DEQUE)/*.cpp)
SRCS_LIST = $(wildcard $(SRC_DIR_LIST)/*.cpp)
SRCS_VECTOR = $(wildcard $(SRC_DIR_VECTOR)/*.cpp)
OBJS_DEQUE = $(patsubst $(SRC_DIR_DEQUE)/%.cpp,$(OBJ_DIR)/deque_%.o,$(SRCS_DEQUE))
OBJS_LIST = $(patsubst $(SRC_DIR_LIST)/%.cpp,$(OBJ_DIR)/list_%.o,$(SRCS_LIST))
OBJS_VECTOR = $(patsubst $(SRC_DIR_VECTOR)/%.cpp,$(OBJ_DIR)/vector_%.o,$(SRCS_VECTOR))

.PHONY: all clean

all: $(EXECUTABLE_DEQUE) $(EXECUTABLE_LIST) $(EXECUTABLE_VECTOR)

$(EXECUTABLE_DEQUE): $(OBJ_DIR) $(OBJS_DEQUE)
	$(CXX) $(CXXFLAGS) $(OBJS_DEQUE) -o $@

$(EXECUTABLE_LIST): $(OBJ_DIR) $(OBJS_LIST)
	$(CXX) $(CXXFLAGS) $(OBJS_LIST) -o $@

$(EXECUTABLE_VECTOR): $(OBJ_DIR) $(OBJS_VECTOR)
	$(CXX) $(CXXFLAGS) $(OBJS_VECTOR) -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/deque_%.o: $(SRC_DIR_DEQUE)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR)/list_%.o: $(SRC_DIR_LIST)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR)/vector_%.o: $(SRC_DIR_VECTOR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)/*.o $(EXECUTABLE_DEQUE) $(EXECUTABLE_LIST) $(EXECUTABLE_VECTOR)
