#
# NetCallback - forwarding TCP ports behind a firewall
# Copyright (C) 2001 Alexander V. Konstantinou <akonstan@acm.org>
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA
#
# $Id: Makefile,v 1.2 2004/02/16 01:46:24 akonstan Exp $

export JAVAC=$(JAVA_HOME)/bin/javac
export JFLAGS=
export CLASSPATH=../../..


all: FORCE
	$(JAVAC) $(JFLAGS) -classpath $(CLASSPATH) *.java

clean: FORCE
	/bin/rm -f *.class *~ netcallback.jar

jar: FORCE
	make clean
	make all
	(cd ../../..; jar cvfm net/sourceforge/netcallback/netcallback.jar net/sourceforge/netcallback/manifest net/sourceforge/netcallback/*.class)

FORCE:


