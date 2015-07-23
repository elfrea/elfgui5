PIXDIR = /home/elfrea/dev/pix5/src
TARGET = main



####################################################################
HDRS = game.h
HDRS+= elfgui5.h elfgui5_drawing.h elfgui5_theme.h elfgui5_dragpacket.h elfgui5_element.h
HDRS+= eBase.h ePanel.h
####################################################################



####################################################################
SRCS = main.cc game.cc
SRCS+= elfgui5.cc elfgui5_drawing.cc elfgui5_theme.cc elfgui5_dragpacket.cc elfgui5_element.cc
SRCS+= eBase.cc ePanel.cc
####################################################################



 
DEPS = Makefile $(HDRS)
OBJS = $(patsubst %.cc,%.o,$(SRCS))
 
.PHONY: all clean
 
all: $(TARGET)
 
clean:
	@rm -f $(OBJS) $(TARGET)
 
 
$(TARGET): $(OBJS) $(DEPS)
	g++ -o $(TARGET) $(OBJS) -L$(PIXDIR) -lpix5_d -Wl,-rpath=$(PIXDIR)
 
$(OBJS): %.o: %.cc $(DEPS)
	g++ -c -o $@ -I$(PIXDIR) -Wall -Werror -DDBG $<
