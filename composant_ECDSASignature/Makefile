CPPFLAGS += `python3-config --includes`
CPPFLAGS += -I/usr/include/openssl
CPPFLAGS += -I/usr/local/include/bitcoin

LIBS=`python3-config --ldflags`
LIBS += -lssl -lcrypto

COMPOSANT = composant_ECDSASignature

LIBSO = ${COMPOSANT}.so
LIBSO_OBJS = ${COMPOSANT}.o

all: test $(LIBSO)

$(COMPOSANT).o: $(COMPOSANT).cpp
	g++ -c $(CPPFLAGS) -o $@ $<

$(LIBSO): $(LIBSO_OBJS)
	g++ -shared $(LIBSO_OBJS) $(LIBS) -o $(LIBSO)

include ../gcc.mk
include ../pybind11.mk
include ../trezor-crypto/bip39.h

test: $(LIBSO)
	echo "execution du test"
	python3 test.py
	
clean:
	rm -f ${LIBSO} ${LIBSO_OBJS}

${DESTINATION_LIBSO}: ${LIBSO}
	cp $< $@
