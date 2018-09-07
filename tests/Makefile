OPTFLAGS = \
  -O2

DBGFLAGS = \
  -g       \
  -fsanitize=address

CXXFLAGS =          \
  -std=c++11        \
  -pedantic         \
  -Wall             \
  -Wextra           \
  -Wconversion      \
  -Wsign-conversion \
  -Wshadow          \
  $(OPTFLAGS)       \
  $(DBGFLAGS)       \
  $(INCLUDES)

MAIN = run_test

OBJECTS =          \
  main.o           \
  data_size_test.o \
  array_view_test.o

ARTIFACTS =  \
  $(MAIN)    \
  $(OBJECTS) \
  *.dSYM

.SUFFIXES: .cc
.PHONY: test clean

test: $(MAIN)
	@./$(MAIN)

clean:
	rm -rf $(ARTIFACTS)

$(MAIN): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $@ $(OBJECTS)

.cc.o:
	$(CXX) $(CXXFLAGS) -c -o $@ $<

data_size_test.o: ../include/array_view.hpp
array_view_test.o: ../include/array_view.hpp
