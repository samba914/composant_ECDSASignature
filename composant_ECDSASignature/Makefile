CPPFLAGS += `python3-config --includes`
CPPFLAGS += -I/usr/include/openssl
CPPFLAGS += -I/usr/local/include/bitcoin

LIBS=`python3-config --ldflags`
LIBS += -lssl -lcrypto

COMPOSANT = composant_BIP39Converter 
LIBSO = ${COMPOSANT}.so
LIBSO_OBJS = ${COMPOSANT}.o

all: test $(LIBSO)

# Compilation du fichier source en un fichier objet
composant_BIP39Converter.o: composant_BIP39Converter.cpp
	g++ -c $(CPPFLAGS) -o $@ $<

# Génération du fichier .so
composant_BIP39Converter.so: composant_BIP39Converter.o
	g++ -shared composant_BIP39Converter.o $(LIBS) -o $@

# Inclusion des fichiers supplémentaires
include ../gcc.mk
include ../pybind11.mk

test: $(LIBSO)
	echo "execution du test"
	python3 test.py

clean:
	rm -f ${LIBSO} ${LIBSO_OBJS}

${DESTINATION_LIBSO}: ${LIBSO}
	cp $< $@
