#!/bin/sh
aclocal
autoheader
autoconf
automake -a --foreign
./configure
