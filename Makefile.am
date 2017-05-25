HDR_DIR=include
SRC_DIR=src
OBJ_DIR=build
TST_DIR=tests

HDRS=$(shell find include/ -name "*.h*" -type f)
SRCS=$(shell find src/ -name "*.cpp" -type f -not -name "main.cpp")
TSTS_SRCS=$(shell find tests/ -name "*.cpp" -type f -not -name "tests.cpp" )

OBJS=$(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRCS)) 
TSTS_OBJS=$(patsubst $(TST_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(TSTS_SRCS))

LINKDIR=-Ldependencies/googletest/build/googlemock -Ldependencies/googletest/build/googlemock/gtest 
INCLUDEDIR=-Idependencies/googletest/googlemock/include -Idependencies/googletest/googletest/include -Iinclude

CXX_FLAGS=$(INCLUDEDIR) -Wall -std=c++11
LD_FLAGS=$(LINKDIR) -lpthread
LD_FLAGS_TESTS=$(LD_FLAGS) -lgtest #-lgtest_main -lgmock -lgmock_main -lpthreads

.PHONY: all clean 

all: Makefile $(OBJ_DIR) $(OBJ_DIR)/tests


#$(OBJ_DIR)/%.o: $(HDR_DIR)/%.h
#	@echo "Compile $@ from { $^ }"
#	$(CXX) $(CXX_FLAGS) -o $@ -c $^
  
$(OBJ_DIR)/%.o: $(TST_DIR)/%.cpp
	@echo "Compile $@ from { $^ }"
	$(CXX) $(CXX_FLAGS) -o $@ -c $^
  
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@echo "Compile $@ from { $^ }"
	$(CXX) $(CXX_FLAGS) -o $@ -c $^

$(OBJ_DIR)/tests: $(TSTS_OBJS) $(OBJS) 
	@echo "Link $@ from { $< }"
	$(CXX) $(CXX_FLAGS) $(LD_FLAGS) -o $@ $<
 
$(OBJ_DIR): ; 
	mkdir	-p		$(OBJ_DIR)

clean:
	rm build/*

