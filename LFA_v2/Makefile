JFLAGS = -g
JC = javac
JVM = java
JFLEX = ./jflex-1.6.1.jar

all: build

lexer.java: lexer.flex
	$(JVM) -jar $(JFLEX) $<

sources = $(wildcard *.java)
classes = $(sources:.java=.class)

build: lexer.java $(classes)

run: build
	$(JVM) Main $(arg)

.PHOONY: clean
clean :
	rm -f *.class lexer.java *~
%.class : %.java
	$(JC) $(JFLAGS) $<
