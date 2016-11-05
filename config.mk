# Included by Makefile

INCLUDE_DIR   =$(ROOTDIR)/code

INSTALL_DIR   =$(ROOTDIR)/code/bin
PLUGINS_DIR   =$(INSTALL_DIR)/plugins
UNITTESTS_DIR =$(INSTALL_DIR)/tests
SWIGOUT_DIR   =$(INSTALL_DIR)/python
SWIGOUT_EXT   =.pyc

OS           ?=$(shell uname -s)
IS_WIN       :=$(shell echo $(OS)|grep -i Windows)

CC          = g++
CFLAGS     += -g
C_FLAGS    += -Wall -g
CFLAGS_SO   = $(CFLAGS) -fPIC
C_FLAGS_SO  = $(C_FLAGS) -shared -fPIC
SWIG        = swig -c++ -python

ifdef IS_WIN
LIBS         += -lshlwapi
else
LIBS         += -ldl
endif
