#
#  Punch BOOT bootloader cli
#
# Copyright (C) 2018 Jonas Persson <jonpe960@gmail.com>
#
# SPDX-License-Identifier: BSD-3-Clause
#
#


# Makefile for Punch BOOT

TARGET  = punchboot
PREFIX ?= /usr

CC=$(CROSS_COMPILE)gcc
LD=$(CROSS_COMPILE)ld
AR=$(CROSS_COMPILE)ar
SIZE=$(CROSS_COMPILE)size
OBJCOPY=$(CROSS_COMPILE)objcopy

ifeq (,$(shell which pkg-config))
$(error "No pkg-config found")
endif

GIT_VERSION = $(shell git describe --abbrev=4 --dirty --always --tags)
PKG_CONFIG ?= pkg-config

USB_PID ?= 0x2019
USB_VID ?= 0x1209

CFLAGS  += -Wall -O2 -I ../../include/
CFLAGS  += -I. -I include/  -I ../../
CFLAGS  += -DVERSION=\"$(GIT_VERSION)\"
CFLAGS  += -DPB_USB_VID=$(USB_VID) -DPB_USB_PID=$(USB_PID)
CFLAGS  += $(shell $(PKG_CONFIG) --cflags libusb-1.0 uuid)

LIBS     = $(shell $(PKG_CONFIG) --libs libusb-1.0 uuid)

ASM_SRCS =
C_SRCS   = $(TARGET).c
C_SRCS  += crc.c
C_SRCS  += utils.c
C_SRCS  += recovery_protocol.c

ifndef TRANSPORT
		TRANSPORT = usb
endif

ifeq ($(TRANSPORT), socket)
	TRANSPORT = socket
else ifeq ($(TRANSPORT), usb)
	TRANSPORT = usb
else
$(error Invalid transport selected)
endif

ifdef CODE_COV
	CFLAGS += -fprofile-arcs -ftest-coverage
endif

C_SRCS  += $(TRANSPORT)_transport.c

OBJS     = $(ASM_SRCS:.S=.o) $(C_SRCS:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	@echo LINK $@ $(LDFLAGS)
	@$(CC) $(LDFLAGS) $(CFLAGS) $(OBJS) $(LIBS) -o $@

%.o: %.S
	@echo CC $<
	@$(CC) -c $(CFLAGS) $< -o $@
%.o: %.c
	@echo CC $<
	@$(CC) -c $(CFLAGS) $< -o $@

install:
	@install -m 755 $(TARGET) $(PREFIX)/bin

clean: 
	@-rm -rf *.o $(TARGET)  *.map out
reallyclean: clean
	$(MAKE) -C 3pp/libtomcrypt clean
	$(MAKE) -C 3pp/libtommath clean
	$(MAKE) -C 3pp/tinyprintf clean

