CC = g++
BUILD_DIR = build
SRC_DIR = src
INCLUDE_DIR = include
CFLAGS = -std=c++11 -I$(INCLUDE_DIR)

EXECUTABLE_FILE = switch.out

OBJECTS = \
	$(BUILD_DIR)/Main.o \
	$(BUILD_DIR)/Switch.o \
	$(BUILD_DIR)/System.o \
	$(BUILD_DIR)/Manager.o \

SwitchSensitivityList = \
	$(SRC_DIR)/Switch.cpp \
	$(INCLUDE_DIR)/Switch.hpp \

SystemSensitivityList = \
	$(SRC_DIR)/System.cpp \
	$(INCLUDE_DIR)/System.hpp \

ManagerSensitivityList = \
	$(SRC_DIR)/Manager.cpp \
	$(INCLUDE_DIR)/Manager.hpp \
	$(INCLUDE_DIR)/Switch.hpp \
	$(INCLUDE_DIR)/System.hpp \

MainSensitivityList = \
	$(SRC_DIR)/Main.cpp \
	$(INCLUDE_DIR)/Manager.hpp \

all: $(BUILD_DIR) $(EXECUTABLE_FILE)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/Switch.o: $(SwitchSensitivityList)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/Switch.cpp -o $(BUILD_DIR)/Switch.o

$(BUILD_DIR)/System.o: $(SystemSensitivityList)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/System.cpp -o $(BUILD_DIR)/System.o

$(BUILD_DIR)/Manager.o: $(ManagerSensitivityList)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/Manager.cpp -o $(BUILD_DIR)/Manager.o

$(BUILD_DIR)/Main.o: $(MainSensitivityList)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/Main.cpp -o $(BUILD_DIR)/Main.o

$(EXECUTABLE_FILE): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(EXECUTABLE_FILE)

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR) *.o *.out  System* Switch*

.PHONY: cleandir
cleandir:
	rm -rf System* Switch*