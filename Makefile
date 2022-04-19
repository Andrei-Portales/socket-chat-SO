CC		:= g++
CFLAGS	:= --std=c++11 -lstdc++
LIBS	:= -lpthread
RM		:= rm



TARGET_CLIENT = client
TARGET_SERVER = server

all: $(TARGET_CLIENT) $(TARGET_SERVER)

$(TARGET_CLIENT): 
	$(CC) $(CFLAGS) $(TARGET_CLIENT).cpp $(LIBS) -o $(TARGET_CLIENT) 

$(TARGET_SERVER):
	$(CC) $(CFLAGS) $(TARGET_SERVER).cpp $(LIBS) -o $(TARGET_SERVER)

clean:
	$(RM) $(TARGET_CLIENT)
	$(RM) $(TARGET_SERVER)