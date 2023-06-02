CPPFLAGS += `python3-config --includes`
CPPFLAGS += -I./cryptopp/
CPPFLAGS += -std=c++11
LIBS=`python3-config --ldflags`
LIBS += -L./cryptopp/ -lcryptopp

COMPOSANT = ECDSASignature_component

LIBSO = ${COMPOSANT}.so
LIBSO_OBJS = ${COMPOSANT}.o cryptopp/eccrypto.o cryptopp/osrng.o cryptopp/oids.o cryptopp/hex.o

all: test $(LIBSO)

include ../gcc.mk
include ../pybind11.mk

cryptopp/%.o: ./cryptopp/%.cpp
	g++ -c -o $@ $< $(CPPFLAGS)

test: $(LIBSO)
	echo "execution du test"
	python3 test.py
	
clean:
	rm -f ${LIBSO} ${LIBSO_OBJS}

${DESTINATION_LIBSO}: ${LIBSO}
	cp $< $@
