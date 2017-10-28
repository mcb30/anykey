BOARD		= tiny8

HZ_tiny8	= 16500000
MCU_tiny8	= attiny85

HZ		= $(HZ_$(BOARD))
MCU		= $(MCU_$(BOARD))

CROSS		= avr-
CC		= $(CROSS)gcc
AS		= $(CROSS)as
LD		= $(CROSS)ld
OBJCOPY		= $(CROSS)objcopy
OBJDUMP		= $(CROSS)objdump
SIZE		= $(CROSS)size
CAT		= cat
HIDRD_CONVERT	= hidrd-convert
AVRDUDE		= avrdude

CFLAGS		+= -flto -Os -g -W -Wall -Wextra -Werror -I.
CFLAGS		+= -mmcu=$(MCU) -DF_CPU=$(HZ) -DBOARD=$(BOARD)
ASFLAGS		+=

HEADERS		:= $(wildcard *.h v-usb/usbdrv/*.h)
XMLS		:= $(wildcard *.xml)
BINS		:= $(patsubst %.xml,%.bin,$(XMLS))

all : $(BINS)

%.xml.inc : %.xml Makefile
	$(HIDRD_CONVERT) -i xml -o code $< $@

%.xml.inc.c : prefix.c %.xml.inc suffix.c Makefile
	$(CAT) $(filter-out Makefile,$^) > $@

%.o : %.c $(HEADERS) Makefile
	$(CC) $(CFLAGS) -o $@ -c $<

%.o : %.s $(HEADERS) Makefile
	$(AS) $(ASFLAGS) -o $@ $<

%.o : v-usb/usbdrv/%.c $(HEADERS) Makefile
	$(CC) $(CFLAGS) -o $@ -c $<

%.s : v-usb/usbdrv/%.S $(HEADERS) Makefile
	$(CC) -E $(CFLAGS) -o $@ $<

%.elf : %.xml.inc.o anykey.o $(BOARD).o usbdrv.o usbdrvasm.o Makefile
	$(CC) $(CFLAGS) -o $@ $(filter-out Makefile,$^)
	$(SIZE) $@

%.lst : %.elf Makefile
	$(OBJDUMP) -h -S $< > $@

%.p : %.lst Makefile
	$(PAGER) $<

%.bin : %.elf Makefile
	$(OBJCOPY) -j .text -j .data -O binary $< $@

%.install : %.bin Makefile
	$(AVRDUDE) -p $(MCU) -V -U $<

clean :
	$(RM) *.xml.inc *.xml.inc.c *.o *.elf *.bin *.lst
