

OUT_BIN = main
PIXDIR = ../pix5



####################################################################
CLSS = game
CLSS+= elfgui5 elfgui5_drawing elfgui5_theme elfgui5_dragpacket elfgui5_event elfgui5_anchor elfgui5_clipboard
CLSS+= elfgui5_kshortcut elfgui5_kshortcuts elfgui5_actions

CLSS+= elfgui5_element
CLSS+= eBase eWindow ePanel eButton eCheckbox eLabel eGroupbox eRadiobutton ePushbutton eRadiopush eTimer eSpinner
CLSS+= eTexturebox eScrollbar ePercentbar eEditbox eTrackbar eTabbox eTab eKeybox eItem eListbox
####################################################################



####################################################################
HDRS+= elfgui5_enums.h
####################################################################



####################################################################
SRCS = main.cc
####################################################################



PIXLIBS = core input gfx

include $(PIXDIR)/Rules.make


