CPPFLAGS += `python3-config --includes`
CPPFLAGS += -I/usr/include/openssl
CPPFLAGS += -I/usr/local/include/bitcoin

LIBS=`python3-config --ldflags`
LIBS += -lssl -lcrypto

COMPOSANT = composant_BIP39Converter

LIBSO = ${COMPOSANT}.so
LIBSO_OBJS = ${COMPOSANT}.o ../trezor-crypto/bip39.o

all: test $(LIBSO)

include ../gcc.mk
include ../pybind11.mk


test: $(LIBSO)
	echo "execution du test"
	python3 test.py
	
clean:
	rm -f ${LIBSO} ${LIBSO_OBJS}

${DESTINATION_LIBSO}: ${LIBSO}
	cp $< $@
