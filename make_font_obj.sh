#!/usr/bin/zsh

tools/makefont.py -o hankaku.bin font/hankaku.txt
objcopy -I binary -O elf64-x86-64 -B i386:x86-64 hankaku.bin hankaku.o
