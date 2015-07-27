PIXDIR = ../pix5/src
TARGET = main



####################################################################
HDRS = game.h
HDRS+= elfgui5.h elfgui5_enums.h elfgui5_drawing.h elfgui5_theme.h elfgui5_dragpacket.h elfgui5_event.h elfgui5_anchor.h
HDRS+= elfgui5_element.h
HDRS+= eBase.h eWindow.h ePanel.h eButton.h eCheckbox.h eLabel.h eGroupbox.h eRadiobutton.h ePushbutton.h eRadiopush.h
####################################################################



####################################################################
SRCS = main.cc game.cc
SRCS+= elfgui5.cc elfgui5_drawing.cc elfgui5_theme.cc elfgui5_dragpacket.cc elfgui5_event.cc elfgui5_anchor.cc
SRCS+= elfgui5_element.cc
SRCS+= eBase.cc eWindow.cc ePanel.cc eButton.cc eCheckbox.cc eLabel.cc eGroupbox.cc eRadiobutton.cc ePushbutton.cc eRadiopush.cc
####################################################################



 
DEPS = Makefile $(HDRS) $(PIXDIR)/libpix5_d.so 
OBJS = $(patsubst %.cc,%.o,$(SRCS))
 
.PHONY: all clean
 
all: $(TARGET)
 
clean:
	@rm -f $(OBJS) $(TARGET)
 
 
$(TARGET): $(OBJS) $(DEPS)
	g++ -o $(TARGET) $(OBJS) -L$(PIXDIR) -lpix5_d -Wl,-rpath=$(PIXDIR)
 
$(OBJS): %.o: %.cc $(DEPS)
	g++ -c -o $@ -I$(PIXDIR) -Wall -Werror -DDBG $<
