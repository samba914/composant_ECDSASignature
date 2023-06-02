%.o : %.c
	gcc -fPIC ${CFLAGS} -c $< -o $@

%.o : %.cpp
	g++ -fPIC ${CPPFLAGS} -c $< -o $@

${EXE} : ${OBJS}
	g++ ${OBJS} ${LDFLAGS} -o $@

${LIBSO} : ${LIBSO_OBJS} cryptopp/libcryptopp.a
	g++ -o $@ -shared ${LDFLAGS} $^ ${LIBS}

${LIB} : ${LIB_OBJS}
	ar -cr $@ $^
