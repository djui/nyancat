autoconf &&\
./configure &&\
sed -i 's/main.c/main.c `libmikmod-config --cflags` `libmikmod-config --libs`/g' Makefile &&\
make
