CXX := g++
CXX_FLAGS := -std=c++11

BIN := bin
INCLUDE := include
SRC := src

folders = exp tensor utils
all_header_files  = $(foreach folder, $(folders), $(wildcard $(INCLUDE)/$(folder)/*.h))
all_src_files     = $(foreach folder, $(folders), $(wildcard $(SRC)/$(folder)/*.cpp))
all_src_basenames = $(basename $(notdir $(all_src_files)))
all_objects       = $(addprefix $(BIN)/, $(addsuffix .o, $(all_src_basenames)))

test: $(BIN)/test.o $(all_objects)
	$(CXX) $(CXX_FLAGS) -I $(INCLUDE) -o $(BIN)/test $^

$(BIN)/test.o: test.cpp $(all_header_files)
	$(CXX) $(CXX_FLAGS) -I $(INCLUDE) -c -o $(BIN)/test.o test.cpp 


.PHONY : clean run

run:
	./bin/test.exe

clean:
	rm $(BIN)/*.o
	rm $(BIN)/*.exe

# The following content is automatically generated by update_makefile.py


$(BIN)/shape.o: src\tensor\shape.cpp include/tensor/shape.h \
 include/utils/base_config.h include/utils/allocator.h \
 include/utils/array.h
	$(CXX) $(CXX_FLAGS) -I $(INCLUDE) -c -o $(BIN)/shape.o src\tensor\shape.cpp

$(BIN)/storage.o: src\tensor\storage.cpp include/tensor/storage.h \
 include/utils/base_config.h include/utils/allocator.h
	$(CXX) $(CXX_FLAGS) -I $(INCLUDE) -c -o $(BIN)/storage.o src\tensor\storage.cpp

$(BIN)/tensor.o: src\tensor\tensor.cpp include/tensor/tensor.h include/exp/exp.h \
 include/utils/allocator.h include/utils/base_config.h \
 include/tensor/tensor_impl.h include/tensor/storage.h \
 include/tensor/shape.h include/utils/array.h
	$(CXX) $(CXX_FLAGS) -I $(INCLUDE) -c -o $(BIN)/tensor.o src\tensor\tensor.cpp

$(BIN)/tensor_impl.o: src\tensor\tensor_impl.cpp include/tensor/tensor_impl.h \
 include/exp/exp.h include/utils/allocator.h include/utils/base_config.h \
 include/tensor/storage.h include/tensor/shape.h include/utils/array.h \
 include/utils/exception.h
	$(CXX) $(CXX_FLAGS) -I $(INCLUDE) -c -o $(BIN)/tensor_impl.o src\tensor\tensor_impl.cpp

$(BIN)/allocator.o: src\utils\allocator.cpp include/utils/allocator.h \
 include/utils/base_config.h include/utils/exception.h
	$(CXX) $(CXX_FLAGS) -I $(INCLUDE) -c -o $(BIN)/allocator.o src\utils\allocator.cpp

$(BIN)/exception.o: src\utils\exception.cpp include/utils/exception.h
	$(CXX) $(CXX_FLAGS) -I $(INCLUDE) -c -o $(BIN)/exception.o src\utils\exception.cpp

