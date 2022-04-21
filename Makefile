CC		:= g++
CFLAGS	:= --std=c++11 -lstdc++
LIBS	:= -lpthread
RM		:= rm



TARGET_CLIENT = client
# TARGET_CLIENT_GUI = mainwindow
TARGET_SERVER = server

all: $(TARGET_CLIENT) $(TARGET_SERVER)

# $(TARGET_CLIENT): 
# 	$(CC) $(CFLAGS) $(TARGET_CLIENT).cpp $(LIBS) -o $(TARGET_CLIENT) 

$(TARGET_SERVER):
	$(CC) $(CFLAGS) $(TARGET_SERVER).cpp $(LIBS) -o $(TARGET_SERVER)

$(TARGET_CLIENT):
	g++ -c $(CFLAGS) -pipe -O2 -Wall -W -D_REENTRANT -fPIC -DQT_DEPRECATED_WARNINGS -DQT_NO_DEBUG -DQT_WIDGETS_LIB -DQT_GUI_LIB -DQT_CORE_LIB -I. -I. -isystem /usr/include/x86_64-linux-gnu/qt5 -isystem /usr/include/x86_64-linux-gnu/qt5/QtWidgets -isystem /usr/include/x86_64-linux-gnu/qt5/QtGui -isystem /usr/include/x86_64-linux-gnu/qt5/QtCore -I. -I/usr/lib/x86_64-linux-gnu/qt5/mkspecs/linux-g++ -o $(TARGET_CLIENT).o $(TARGET_CLIENT).cpp
	g++ -Wl,-O1 -o $(TARGET_CLIENT) $(TARGET_CLIENT).o   /usr/lib/x86_64-linux-gnu/libQt5Widgets.so /usr/lib/x86_64-linux-gnu/libQt5Gui.so /usr/lib/x86_64-linux-gnu/libQt5Core.so /usr/lib/x86_64-linux-gnu/libGL.so -lpthread $(CFLAGS)

clean:
	$(RM) $(TARGET_CLIENT)
	$(RM) $(TARGET_SERVER)