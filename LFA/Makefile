JFLAGS = -g
JC = javac
JVM = java
JFLEX = ./jflex-1.6.1.jar

all: build

Flexer.java: Flexer.flex
	$(JVM) -jar $(JFLEX) $<

sources = $(wildcard *.java)
classes = $(sources:.java=.class)

build: Flexer.java $(classes)

run: build
	$(JVM) Main $(arg)

.PHOONY: clean
clean :
	rm -f *.class Flexer.java *~
%.class : %.java
	$(JC) $(JFLAGS) $<
