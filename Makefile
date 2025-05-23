TARGET = kernel.elf
# OBJS = mykernel.o graphics.o font.o hankaku.o newlib_support.o

SRCDIR = src/
SRCS = ${wildcard ${SRCDIR}*.*}

FILES = ${notdir ${basename ${SRCS}}}
OBJS = ${addsuffix .o, ${FILES}}
OBJS += hankaku.o # 別手段でのビルドで生成するため，直に追加

HEADDIR = include/
HEADERS = ${wildcard ${HEADDIR}*.h}

DEPENDS = $(join $(dir $(OBJS)),$(addprefix .,$(notdir $(OBJS:.o=.d))))

LINKFLAGS = -I./include
CFLAGS   += -O2 -Wall -g --target=x86_64-elf -ffreestanding -mno-red-zone
CXXFLAGS += -O2 -Wall -g --target=x86_64-elf -ffreestanding -mno-red-zone \
            -fno-exceptions -fno-rtti -std=c++17
LDFLAGS  += --entry KernelMain -z norelro --image-base 0x100000 --static


.PHONY: all
all: $(TARGET)

.PHONY: clean
clean:
	rm -rf *.o

kernel.elf: $(OBJS) Makefile
	ld.lld $(LDFLAGS) -o kernel.elf $(OBJS) -lc

%.o: ${SRCDIR}%.cpp Makefile
	clang++ $(CPPFLAGS) $(CXXFLAGS) ${LINKFLAGS} -c $<

.%.d: ${SRCDIR}%.cpp
	clang++ $(CPPFLAGS) $(CXXFLAGS) ${LINKFLAGS} -MM $< > $@
	$(eval OBJ = $(<:.cpp=.o))
	sed --in-place 's|$(notdir $(OBJ))|$(OBJ)|' $@

%.o: ${SRCDIR}%.c Makefile
	clang $(CPPFLAGS) $(CFLAGS) -c $<

.%.d: ${SRCDIR}%.c
	clang $(CPPFLAGS) $(CFLAGS) -MM $< > $@
	$(eval OBJ = $(<:.c=.o))
	sed --in-place 's|$(notdir $(OBJ))|$(OBJ)|' $@

hankaku.bin: font/hankaku.txt
	tools/makefont.py -o $@ $<

hankaku.o: hankaku.bin
	objcopy -I binary -O elf64-x86-64 -B i386:x86-64 $< $@

.%.d: %.bin
	touch $@

.PHONY: depends
depends:
	$(MAKE) $(DEPENDS)

-include $(DEPENDS)
