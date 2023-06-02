%.o : %.c
	gcc -fPIC ${CFLAGS} -c $< -o $@

%.o : %.cpp
	g++ -fPIC ${CPPFLAGS} -c $< -o $@

${EXE} : ${OBJS}
	g++ ${OBJS} ${LDFLAGS} -o $@ ${LIBS}

${LIBSO} : ${LIBSO_OBJS}
	g++ -o $@ -shared ${LDFLAGS} $^ ${LIBS}

${LIB} : ${LIB_OBJS}
	ar -cr $@ $^

