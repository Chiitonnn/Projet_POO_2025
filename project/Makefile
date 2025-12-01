# Makefile
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2 -I./Core -I./Managers -I./Patterns


SRCS = main.cpp \
    Core/Task.cpp Core/User.cpp Core/ConcretePriorityStrategies/StandardPriority.cpp \
    Managers/TaskManager.cpp Managers/UserManager.cpp Managers/AssignmentManager.cpp \
    Patterns/Observer/NotificationCenter.cpp Patterns/Singleton/HistoryLogger.cpp \
    Patterns/Facade/SystemFacade.cpp

OBJS = $(SRCS:.cpp=.o)
TARGET = task_manager

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRCS)

clean:
	rm -f $(TARGET) $(OBJS)
