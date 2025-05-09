# Variables

HEADDIR = include/
HEADERS = ${wildcard ${HEADDIR}*.h}

SRCDIR = src/
SRCS = ${wildcard ${SRCDIR}*.cpp}

OBJS = ${wildcard *.o}

TARGET = kernel.elf

LINKFLAGS = -I./include
CXXFLAGS += -O2 --target=x86_64-elf -fno-exceptions -ffreestanding -mno-red-zone -fno-rtti -std=c++17
LDFLAGS += --entry KernelMain -z norelro --image-base 0x100000 --static -z separate-code

.PHONY: all
all: ${TARGET}

.PHONY: clean
clean:
	rm ${TARGET}
	rm ${filter-out hankaku.o, ${OBJS}}

# Build commands

${TARGET}: ${OBJS}
	ld.lld ${LDFLAGS} -o $@ ${OBJS}

${OBJS}: ${SRCS}
	clang++ ${CPPFLAGS} ${CXXFLAGS} ${LINKFLAGS} -c $^
