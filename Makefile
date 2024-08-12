SOURCES=$(wildcard ./*.c)
TARGET=test
REL=$(SOURCES:.c=.rel)
LST=$(SOURCES:.c=.lst)
ASM=$(SOURCES:.c=.asm)
RST=$(SOURCES:.c=.rst)
SYM=$(SOURCES:.c=.sym)

all: load

load: $(TARGET).ihx
	stm8flash -c stlinkv2 -p stm8s003?3 -w $(TARGET).ihx

$(TARGET).ihx: $(REL)
	sdcc -lstm8 -mstm8 --out-fmt-ihx $(REL) -o $(TARGET).ihx

%.rel: %.c
	sdcc -lstm8 -mstm8 -c $<

clean:
	rm -f $(REL)
	rm -f $(LST)
	rm -f $(ASM)
	rm -f $(RST)
	rm -f $(SYM)
	rm -f $(TARGET).lk
	rm -f $(TARGET).map
	rm -f $(TARGET).ihx
