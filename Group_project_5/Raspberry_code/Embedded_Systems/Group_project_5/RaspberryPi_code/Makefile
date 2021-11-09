   	INC_DIR = include
   	SRC_DIR = src
   	OBJ_DIR = build/bin
   
	CC= g++
   	CFLAGS = -pthread -I.
    
	SRCS = $(SRC_DIR)/main.cpp $(SRC_DIR)/modbus.cpp 
  	OBJS = $(OBJ_DIR)/main.o $(OBJ_DIR)/modbus.o 
  	DEPS = $(INC_DIR)/modbus.h
   
  	all: $(OBJS)
	  $(CC) $(CFLAGS) -o main $(OBJS) 
	  touch all 
   
  	$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cpp 	
	  $(CC) -Wall -o $@ -c $< 
  
  	$(OBJ_DIR)/main.o: $(DEPS)
  
  	clean:
	  rm -f main $(OBJ_DIR)/*.o