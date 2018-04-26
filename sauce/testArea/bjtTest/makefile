# This Makefile requires the /usr/share/arduino.mk file to exist
# It is a collections of paths you need to set up
# Edited by Julio B. Figueroa
#
#######################################################################
# for MAC IDE 1.0
# ARDUINO_DIR = /Applications/Arduino.app/Contents/Resources/Java
# ARDMK_DIR = /usr/local

# for MAC IDE 1.5 try these:
# ARDUINO_DIR = /APPLICATIONS/Arduino.app/Contents/Java
# ARDMK_DIR = /usr/local
# ####################################################################

# for linux users the general paths should be:
# ####################################################################
# ARDUINO_DIR = /usr/share/arduino
# ARDMK_DIR = /usr/share/arduino
# AVR_TOOLS_DIR = /usr
# ###################################################################

# ARDUINO_SKETCHBOOK
ARDUINO_SKETCHBOOK = ~/sketchbook

# PROJECT_DIR
# This is the path to where you have created/cloned your project
# PROJECT_DIR        = ~/sketchbook/JCMS

# ARDMK_DIR
# Path to the Arduino-Makefile director
# Directory where the *.mk files are stored.
# ARDMK_DIR         = $(PROJECT_DIR)/Arduino-Makefile
# actually it's path to arduino IDE and/r core files are stored
ARDMK_DIR	= /usr/share/arduino

# ARDUINO_DIR
# e.g. boards.txt, libraries, etc.
# Path to the Arduino application and resources directory.
ARDUINO_DIR       = /usr/share/arduino

# ARDUINO_PREFERENCES_PATH
ARDUINO_PREFERENCES_PATH	= ~/sketches/preferences.txt

# USER_LIB_PATH, optional, default to user's sketchbook
# Path to where the your project's libraries are stored.
# USER_LIB_PATH    :=  $(PROJECT_DIR)/libraries
USER_LIB_PAT	= ~/sketchbook/libraries/
# ~/sketchbook/libraries/armadillo

# BOARD_TAG
# Please consult /usr/share/arduino/hardware/arduino/boards.txt to verify fuses
# try lower case tags, in this same folder type 'make board_boards'
# BOARD_TAG     = nano328
# the nano v3 is the 328 one
#BOARD_TAG		=	nano
# the nano v2 should be the regular nano
# BOARD_TAG		=	mega2560
#BOARD_TAG		=	atmega328
BOARD_TAG	    =   uno

# MONITOR_BAUDRATE
# It must be set to Serial baudrate value you are using.
MONITOR_BAUDRATE  = 9600

# AVR_TOOLS_DIR
# Path to the AVR tools directory such as avr-gcc, avr-g++, etc.
# On OS X with `homebrew`:
# AVR_TOOLS_DIR     = /usr/local
# or on Linux: (remove the one you don't want)
# AVR_TOOLS_DIR     = /usr
AVR_TOOLS_DIR	  = /usr/share/arduino/hardware/tools/avr

# AVRDUDE
# Path to avrdude directory.
# On OS X with `homebrew`:
# AVRDUDE          = /usr/local/bin/avrdude
# or on Linux: (remove the one you don't want)
AVRDUDE           = /usr/bin/avrdude

# CFLAGS_STD
CFLAGS_STD        = -std=gnu11

# CXXFLAGS_STD
CXXFLAGS_STD      = -std=gnu++11

# CXXFLAGS
# Flags you might want to set for debugging purpose. Comment to stop.
CXXFLAGS         += -pedantic -Wall -Wextra

# MONITOR_PORT
# The port your board is connected to. Using an '*' tries all the ports and finds the right one.
# MONITOR_PORT    = /dev/tty.usbmodem*
# MONITOR_PORT	  = /dev/ttyUSB*
MONITOR_PORT	  = /dev/ttyUSB3
BT_MONITOR_PORT   = /dev/rfcomm5	#or rfcomm1 check "ls /dev/rfcomm*"
# CURRENT_DIR
# Do not touch - used for binaries path
CURRENT_DIR       = $(shell basename $(CURDIR))

# OBJDIR
# This is where you put the binaries you just compile using 'make'
OBJDIR            = $(PROJECT_DIR)/bin/$(BOARD_TAG)/$(CURRENT_DIR)

# Do not touch - the path to Arduino.mk, inside the ARDMK_DIR
include $(ARDMK_DIR)/Arduino.mk

# A few make commands to make life easier
#DATE = '%Y%m%d %h:%m:%s'
#DATE = %Y%m%d%h%m%s
#DATE = '%Y%m%d%H'
D = `date +"%Y_%m_%d_%H_%m_%s"`
screen:
	screen -L $D.txt $(MONITOR_PORT) $(MONITOR_BAUDRATE)

screen2:
	screen -L $D.txt $(BT_MONITOR_PORT) $(MONITOR_BAUDRATE)
