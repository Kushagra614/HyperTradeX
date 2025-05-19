CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -I.
LDFLAGS = -lcurl

SRCS = JSONdata.cpp TechnicalAnalysis.cpp Backtester.cpp
OBJS = $(SRCS:.cpp=.o)

all: test_backtest

test_backtest: test_backtest.cpp $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<

clean:
	rm -f $(OBJS) test_backtest

.PHONY: all clean 