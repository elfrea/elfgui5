

OUT_BIN = main
PIXDIR = ../pix5



CLSS = 

####################################################################
HDRS = game.h
HDRS+= elfgui5.h elfgui5_enums.h elfgui5_drawing.h elfgui5_theme.h elfgui5_dragpacket.h elfgui5_event.h elfgui5_anchor.h elfgui5_clipboard.h
HDRS+= elfgui5_kshortcut.h elfgui5_kshortcuts.h elfgui5_actions.h
HDRS+= elfgui5_element.h
HDRS+= eBase.h eWindow.h ePanel.h eButton.h eCheckbox.h eLabel.h eGroupbox.h eRadiobutton.h ePushbutton.h eRadiopush.h eTimer.h eSpinner.h
HDRS+= eTexturebox.h eScrollbar.h ePercentbar.h eEditbox.h eTrackbar.h eTabbox.h eTab.h eKeybox.h
####################################################################



####################################################################
SRCS = main.cc game.cc
SRCS+= elfgui5.cc elfgui5_drawing.cc elfgui5_theme.cc elfgui5_dragpacket.cc elfgui5_event.cc elfgui5_anchor.cc elfgui5_clipboard.cc
SRCS+= elfgui5_kshortcut.cc elfgui5_kshortcuts.cc elfgui5_actions.cc

SRCS+= elfgui5_element.cc
SRCS+= eBase.cc eWindow.cc ePanel.cc eButton.cc eCheckbox.cc eLabel.cc eGroupbox.cc eRadiobutton.cc ePushbutton.cc eRadiopush.cc eTimer.cc eSpinner.cc
SRCS+= eTexturebox.cc eScrollbar.cc ePercentbar.cc eEditbox.cc eTrackbar.cc eTabbox.cc eTab.cc eKeybox.cc
####################################################################


PIXLIBS = core input gfx




include $(PIXDIR)/Rules.make


