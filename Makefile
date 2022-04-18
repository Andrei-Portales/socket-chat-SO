CC = gcc

CFLAGS  = -std=c++11 -lstdc++

TARGET_CLIENT = client

all: $(TARGET_CLIENT)

$(TARGET_CLIENT): $(TARGET_CLIENT).cpp
	$(CC) -o $(TARGET_CLIENT) $(TARGET_CLIENT).cpp $(CFLAGS)

clean:
	$(RM) $(TARGET_CLIENT)