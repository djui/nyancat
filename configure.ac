AC_INIT(nyancat, 1.0, uwe@dauernheim.net)

AC_PROG_CC

AC_CHECK_HEADER(stdio.h)
AC_CHECK_HEADER(termios.h)
AC_CHECK_HEADER(sys/time.h)
AC_CHECK_HEADER(string.h)
AC_CHECK_HEADER(unistd.h)
AC_CHECK_HEADER(mikmod.h, , AC_MSG_ERROR(libmikmod not found))

AC_CHECK_LIB(mikmod, MikMod_Init, , AC_MSG_ERROR(libmikmod not found))

AC_SUBST(CFLAGS, $(libmikmod-config --cflags))
AC_SUBST(LFLAGS, $(libmikmod-config --libs))

AC_CONFIG_FILES(Makefile)

AC_OUTPUT
