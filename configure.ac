AC_INIT(re2-c, 0.1, markiyan.kushnir@gmail.com)
if test -n "$USE_GCC"
then
    probe="gcc${USE_GCC}"
    if which $probe >/dev/null
    then
        CC="gcc${USE_GCC}"
        CXX="c++${USE_GCC}"
        CPP="cpp"
    else
        if which gcc >/dev/null
        then
            CC="gcc"
            CXX="g++"
            CPP="cpp"
        else
            echo "Cannot find gcc"
            exit 1
        fi
    fi
else
    if which clang >/dev/null
    then
        CC="clang -Qunused-arguments -fcolor-diagnostics"
        CXX="clang++ -Qunused-arguments -fcolor-diagnostics"
        CPP="clang-cpp"
        clang_version=`clang --version | grep version | awk '{print $4;}'`
        clang_version_mjr=`echo $clang_version | awk -F. '{print $1;}'`
        clang_version_mnr=`echo $clang_version | awk -F. '{print $2;}'`
        if test "$clang_version_mjr" = "3" -a "$clang_version_mnr" -lt 3
        then
            AC_SUBST(CLANG_DEBUG, ['-ftrapv'])
        else
            # we assume all others are 3.3+, add here options if needed
            AC_SUBST(CLANG_DEBUG, ['-ftrapv'])
        fi
    else
        CC="cc"
        CXX="c++"
        CPP="cpp"
    fi
fi

AC_CONFIG_MACRO_DIR([m4])

AC_LANG(C++)

AC_PROG_CC
AC_PROG_CXX
AM_PROG_AR
AC_PROG_RANLIB
AC_PROG_INSTALL

LT_INIT
AM_INIT_AUTOMAKE

dnl AM_MAINTAINER_MODE

AC_CONFIG_FILES([Makefile src/Makefile src/test/Makefile man/Makefile])
AC_CONFIG_HEADERS(config.h)

AC_CHECK_HEADERS([syslog.h])

AC_C_CONST
AC_C_INLINE
AC_TYPE_SIZE_T

AC_FUNC_MALLOC
AC_FUNC_REALLOC

AC_FUNC_ERROR_AT_LINE

AC_PRESERVE_HELP_ORDER

AC_ARG_ENABLE(debug,
              AC_HELP_STRING([--enable-debug],
                             [Enable debug build (default=no)]),
              [AM_CONDITIONAL([DEBUG], [enable_debug=yes])],
              [AM_CONDITIONAL([DEBUG], [test "$enable_debug" = "yes"])])

# pass LDFLAGS=-L${LOCALBASE}/lib in the environment
AC_CHECK_LIB(re2, _fini, [], [AC_MSG_FAILURE(libre2.so is required. Please find it at https://code.google.com/p/re2/)])
AC_CHECK_LIB(mrkcommon, _fini, [], [AC_MSG_FAILURE(libmrkcommon.so is required. Please find it at git@github.com:mkushnir/mrkcommon.git)])

AC_OUTPUT
