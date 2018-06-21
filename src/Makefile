IDIR=../include
CXXFLAGS=-std=c++11
OBJECTS=main.cpp connection.cpp
INCFLAGS+= -I$(IDIR)
LDFLAGS+= -lcurl

RGB_LIB_DISTRIBUTION=../rpi-rgb-led-matrix
RGB_INCDIR=$(RGB_LIB_DISTRIBUTION)/include
RGB_LIBDIR=$(RGB_LIB_DISTRIBUTION)/lib
RGB_LIBRARY_NAME=rgbmatrix
RGB_LIBRARY=$(RGB_LIBDIR)/lib$(RGB_LIBRARY_NAME).a
INCFLAGS+= -I$(RGB_INCDIR)
LDFLAGS+= -L$(RGB_LIBDIR) -l$(RGB_LIBRARY_NAME) -lrt -lm -lpthread

server: $(OBJECTS) $(RGB_LIBRARY)
	g++ $(CXXFLAGS) $(OBJECTS) -o ../led_server $(INCFLAGS) $(LDFLAGS)
	chmod +x ../led_server

$(RGB_LIBRARY):
	$(MAKE) -C $(RGB_LIB_DISTRIBUTION)
