#settings
CC=clang
LD=ld.lld
VERSION = v0.14u
SRCDIR ?= ../..
VSOUND_HEADER_DIR = $(SRCDIR)/../vsound
BUILDDIR = $(SRCDIR)
CLEANFILES = $(PROGS) *.o
PROGS	=	aoe aoebridge aoebridge-gen

CLI_FLAGS += -DLOG
#CLI_FLAGS += -DPACKET_LOSS_EMULATION

SVR_FLAGS += -DSERVER_STATS
SVR_FLAGS += -DLOG

WARN_FLAGS = -Werror -Wall -Wunused-function
WARN_FLAGS += -Wextra
WARN_FLAGS += -Wshadow

CFLAGS  = -DAOE_VERSION=\"$(VERSION)\"
CFLAGS += -O3 -pipe -g
CFLAGS += -mcpu=cortex-a72 -march=armv8-a+crc -mtune=cortex-a72
CFLAGS += -fno-stack-protector
CFLAGS += -fno-semantic-interposition
CFLAGS += -fno-math-errno
CFLAGS += -I $(VSOUND_HEADER_DIR)
LDLIBS += -lm -lrt -lasound
LDFLAGS = -L./
#LDLIBS += -lgcov

# coverage (GCC)
#CFLAGS += --coverage -O0
#CFLAGS += -I/usr/lib/gcc/aarch64-unknown-linux-gnu/10.1.0/include/
#LDFLAGS += -L/usr/lib/gcc/aarch64-unknown-linux-gnu/10.1.0/


# coverage (LLVM)
# build and run,
# mv /default.profraw .
# llvm-profdata merge -o output.prof ./default.profraw
# llvm-cov show ./aoe -instr-profile=./output.prof > cov.log
#
#CFLAGS += -fprofile-instr-generate -fcoverage-mapping
#LDFLAGS += -fprofile-instr-generate -fcoverage-mapping

# asm
#CFLAGS += -g -save-temps=obj

all: clean aoe
	size -G aoe
	strip aoe
	ls -al aoe
	md5sum aoe

clean:
	-@rm -rf $(CLEANFILES)

# aoebridge (PGO generate)
gen: CFLAGS += -fprofile-generate -fprofile-correction
gen: CFLAGS += -ffunction-sections -fdata-sections -fomit-frame-pointer -flto
gen: LDFLAGS += -Wl,-flto -Wl,--gc-sections -Wl,--no-as-needed
gen: clean aoebridge

# aoebridge (PGO use)
use: CFLAGS += -fprofile-use -fprofile-correction
use: CFLAGS += -ffunction-sections -fdata-sections -fomit-frame-pointer -flto
use: LDFLAGS += -Wl,-flto -Wl,--gc-sections -Wl,--no-as-needed
use: clean aoebridge
	size -G aoebridge
	strip aoebridge
	ls -al aoebridge
	md5sum aoebridge

# aoe
aoe: CFLAGS += -ffunction-sections -fdata-sections -fomit-frame-pointer -flto
aoe: LDFLAGS += -flto
aoe: aoe.o
aoe.o: aoecli.c
	$(CC) $(CFLAGS) $(WARN_FLAGS) $(CLI_FLAGS) -c $^ -o $@

# aoebridge
aoebridge: CFLAGS += -ffunction-sections -fdata-sections -fomit-frame-pointer -flto
aoebridge: CFLAGS += -I $(SRCDIR)/sys -I $(SRCDIR)/apps/include -I $(SRCDIR)/libnetmap
aoebridge: LDFLAGS += -flto
aoebridge: aoebridge.o nmctx.o  nmctx-pthreads.o  nmport.o  nmreq.o
aoebridge.o: aoebridge.c
	$(CC) $(CFLAGS) $(WARN_FLAGS) $(SVR_FLAGS) -c $^ -o $@
