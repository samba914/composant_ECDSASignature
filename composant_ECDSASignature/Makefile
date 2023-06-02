CPPFLAGS += `python3-config --includes`
CPPFLAGS += -I./cryptopp/
CPPFLAGS += -std=c++11
LIBS = `python3-config --ldflags`
LIBS += -L./cryptopp/ -lcryptopp

COMPOSANT = composant_ECDSASignature

LIBSO = ${COMPOSANT}.so
LIBSO_OBJS = ${COMPOSANT}.o

cryptopp/libcryptopp.a: 
	$(MAKE) -C cryptopp/ CXXFLAGS=-fPIC

all: cryptopp/libcryptopp.a $(LIBSO)

include ../gcc.mk
include ../pybind11.mk

test: $(LIBSO)
	echo "execution du test"
	python3 test.py
	
clean:
	rm -f ${LIBSO} ${LIBSO_OBJS}
	$(MAKE) -C cryptopp/ clean

${DESTINATION_LIBSO}: ${LIBSO}
	cp $< $@

${COMPOSANT}.o: ${COMPOSANT}.cpp
	g++ -fPIC ${CPPFLAGS} -c $< -o $@
