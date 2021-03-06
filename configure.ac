# Process this file with autoconf to produce a configure script.
#
# $Id: configure.in,v 1.15 2008/10/07 21:19:01 smolik Exp $

# autoconf requirement

AC_PREREQ([2.69])

AC_INIT([orte],[0.3.4],[orte@rtime.felk.cvut.cz],[],[http://orte.sf.net])
AC_CONFIG_AUX_DIR(admin)

###############################
# Package info
ORTE_MAJOR_VERSION=0
ORTE_MINOR_VERSION=3
ORTE_MICRO_VERSION=3
ORTE_VERSION=$ORTE_MAJOR_VERSION.$ORTE_MINOR_VERSION.$ORTE_MICRO_VERSION
AC_SUBST(ORTE_MAJOR_VERSION)
AC_SUBST(ORTE_MINOR_VERSION)
AC_SUBST(ORTE_MICRO_VERSION)
AC_SUBST(ORTE_VERSION)

# Libtool versioning (see libtool manual)

LT_CURRENT=1 # This will be part of SONAME
LT_REVISION=0
LT_AGE=0
AC_SUBST(LT_CURRENT)
AC_SUBST(LT_REVISION)
AC_SUBST(LT_AGE)
VERSION=$ORTE_VERSION
PACKAGE=orte

echo
echo "ORTE version $PACKAGE_VERSION"
echo "Configuring..."
echo

#Check for CPU / vendor / OS
AC_CANONICAL_HOST
AC_CANONICAL_TARGET
AC_CONFIG_HEADER(orte/include/orte/orte_config.h)
AM_INIT_AUTOMAKE(no-define)

AC_CONFIG_MACRO_DIR([admin])

# Activate maintainer mode
AM_MAINTAINER_MODE

DS_LINUX()

###############################
# target
WIN='no'
MINGW='no'
CYGWIN='no'
UNIX='no'
case "$target" in
  *-cygwin*)
    CFLAGS="$CFLAGS"
    WIN='yes'
    CYGWIN='yes'
    AC_DEFINE([CONFIG_ORTE_WIN],[1],[Define if is target windows])
    AC_DEFINE([CONFIG_ORTE_CYGWIN],[1],[Define if is target CYGWIN])
    ;;  
  *-mingw*)
    CFLAGS="$CFLAGS"
    WIN='yes'
    MINGW='yes'
    AC_DEFINE([CONFIG_ORTE_WIN],[1],[Define if is target windows])
    AC_DEFINE([CONFIG_ORTE_MINGW],[1],[Define if is target MINGW])
    AC_DEFINE([HAVE_GETPOT_LONG_ORTE],[1],[Define for ORTE getopt_long self implemetation])
    ;;
  *)
    # Assume a Unix.
    if test -z "${CONFIG_ORTE_RT}" -a "${CONFIG_ORTE_KERNEL}" ; then
      UNIX='yes'
      AC_DEFINE([CONFIG_ORTE_UNIX],[1],[Define if is target a unix system])
    fi
    ;;
esac
AM_CONDITIONAL(CONFIG_ORTE_WIN, test x$WIN = xyes)
AM_CONDITIONAL(CONFIG_ORTE_CYGWIN, test x$CIGWIN = xyes)
AM_CONDITIONAL(CONFIG_ORTE_MINGW, test x$MINGW = xyes)
AM_CONDITIONAL(CONFIG_ORTE_UNIX, test x$UNIX = xyes)

###############################
# modules
moduledir="\$(libdir)/modules/\$(LINUX_KERNELRELEASE)/orte"
modulePROGRAMS_INSTALL="\$(top_builddir)/modtool --install"
modulePROGRAMS_UNINSTALL="\$(top_builddir)/modtool --uninstall"
AC_SUBST(moduledir)
AC_SUBST(modulePROGRAMS_INSTALL)

###############################
# CFLAGS
CFLAGS="$CFLAGS -Wall"
if test ${USE_RTLINUX} == 'yes' ; then
  CFLAGS="$CFLAGS $RTLINUX_CFLAGS"
  CC="$RTLINUX_CC"
else
  if test ${USE_RTAI} == 'yes' ; then
    CFLAGS="$CFLAGS $RTAI_CFLAGS $LINUX_CFLAGS"
  else
    if test -n "${CONFIG_ORTE_KERNEL}" ; then
      CFLAGS="$CFLAGS $LINUX_CFLAGS"
    fi
  fi
fi

###############################
# Checks for programs.
# Initialize libtool
AC_PROG_CC
AM_PROG_CC_C_O
LT_INIT([win32-dll])
PKG_PROG_PKG_CONFIG()

###############################
# Checks for ability to compile ORTE_IDL
AM_ORTE_IDL

###############################
# Checks for ability to compile JORTE
AM_JORTE

###############################
# Checks for libraries and init libtools
if test -z "${CONFIG_ORTE_RT}" ; then
  AC_CHECK_LIB([ws2_32], [main])
  AC_CHECK_LIB([socket], [main])
  AC_CHECK_LIB([nsl], [main])
  dnl Check for pthreads
  AC_CHECK_LIB(pthread, pthread_create, ,
         AC_CHECK_LIB(c_r, pthread_create, ,
              if test ${MINGW} == 'yes' ; then
                     INTERNAL_PTHREAD_LIBS=' -L$(top_srcdir)/orte/contrib/win_pthread/ -lpthread'
                     AC_MSG_NOTICE([Using internal version of pthreads!!!])
              else
                     AC_MSG_ERROR([Can't compile without pthreads!!!])
              fi       
         )
  )
fi

AC_CHECK_FUNCS([pthread_condattr_setclock])
AC_CHECK_LIB([rt], [clock_gettime])
AC_CHECK_DECLS([CLOCK_MONOTONIC], [], [], [[#include <time.h>]])

###############################
# enable GNU source
AH_VERBATIM([_GNU_SOURCE],[
#ifndef _GNU_SOURCE
  #define _GNU_SOURCE
#endif
]) 

###############################
# Checks for header files.
# user space
if test ${UNIX} == 'yes' -o ${WIN} == 'yes' ; then
    AC_HEADER_STDC
    AC_CHECK_HEADERS([\
    arpa/inet.h fcntl.h stdio.h netdb.h stdlib.h \
    string.h sys/ioctl.h sys/stat.h sys/time.h unistd.h pthread.h \
    sys/types.h sys/sockio.h stdarg.h byteswap.h getopt.h \
    ctype.h signal.h stdint.h errno.h],,,[[]])
    AC_CHECK_HEADERS([sys/socket.h], [], [],
          [#ifdef HAVE_SYS_TYPES_H
	     #include <sys/types.h>
           #endif])
    AC_CHECK_HEADERS([netinet/in.h], [], [],
          [#ifdef HAVE_SYS_TYPES_H
	     #include <sys/types.h>
           #endif])
    AC_CHECK_HEADERS([net/if.h], [], [],
          [#ifdef HAVE_SYS_TYPES_H
	     #include <sys/types.h>
           #endif
           #ifdef HAVE_SYS_SOCKET_H
	     #include <sys/socket.h>
           #endif])
fi
# win32
if test ${WIN} == 'yes' ; then
    AC_CHECK_HEADERS([\
    winsock2.h ws2tcpip.h windows.h w32api/windows.h],,,[[]])
    AC_CHECK_FUNCS([gettimeofday])
fi
# kernel
if test "${CONFIG_ORTE_KERNEL}" == 'yes' ; then
    AC_CHECK_HEADERS([\
    asm/byteorder.h linux/ctype.h linux/string.h \
    linux/module.h linux/if.h linux/socket.h \
    linux/time.h linux/types.h],,,[[]])
    AC_CHECK_HEADERS([linux/in.h],,,[
    #ifdef HAVE_LINUX_SOCKET_H
      #include <linux/socket.h>
    #endif
    ])
fi
# RTLinux
if test ${USE_RTLINUX} == 'yes' ; then
    AC_CHECK_HEADERS([\
    string.h pthread.h \
    rtl.h rtl_malloc.h udp.h nic.h time.h],,,[[]])
    AC_CHECK_HEADERS([nictab.h],,,[
    #ifdef HAVE_UDP_H
      #include <udp.h>
    #endif
    #ifdef HAVE_NIC_H
      #include <nic.h>
    #endif
    ])
    AC_CHECK_HEADERS([onetd.h],,,[
    #ifdef HAVE_LINUX_IF_H
      #include <linux/if.h>
    #endif
    #ifdef HAVE_LINUX_IN_H
      #include <linux/in.h>
    #endif
    #ifdef HAVE_PTHREAD_H
      #include <pthread.h>
    #endif
    ])
fi
# RTAI
if test ${USE_RTAI} == 'yes' ; then
    AC_CHECK_HEADERS([\
    rtnet.h],,,[[]])
fi

###############################
# includes
INCLUDES='-I$(top_srcdir)/orte/include -I$(top_builddir)/orte/include'
AC_SUBST(INCLUDES)

###############################
# Checks for typedefs, structures, and compiler characteristics.

AC_CHECK_MEMBERS([struct sockaddr.sa_len],,,[#ifdef HAVE_SYS_TYPES_H
                   #include <sys/types.h>
                 #endif
                 #ifdef HAVE_SYS_SOCKET_H
                   #include <sys/socket.h>
                 #endif
                 #ifdef HAVE_WINSOCK2_H
                   #include <winsock2.h>
                 #endif])


AC_CHECK_HEADERS([ifaddrs.h],,,[#ifdef HAVE_SYS_TYPES_H
	     #include <sys/types.h>
           #endif])

###############################
# Endianness support attempts to allow build with same configure
# for both cases on recent systems

need_endian_test=yes
AC_CHECK_HEADERS([endian.h sys/param.h], [], [],[])

if test "$ac_cv_header_sys_param_h" == 'yes' ; then
    AC_MSG_CHECKING([whether BYTE_ORDER defined in sys/param.h])
    AC_COMPILE_IFELSE([AC_LANG_PROGRAM([#include <sys/param.h>], [
                        unsigned int a=BYTE_ORDER;
                        unsigned int b=BIG_ENDIAN;
                        unsigned int c=LITTLE_ENDIAN;])],
                      [AC_MSG_RESULT([yes])
                       need_endian_test=no],[AC_MSG_RESULT([no])])

    if test "$need_endian_test" == 'yes' ; then
        AC_MSG_CHECKING([whether __BYTE_ORDER defined in sys/param.h])
        AC_COMPILE_IFELSE([AC_LANG_PROGRAM([#include <sys/param.h>], [
                        unsigned int a=__BYTE_ORDER;
                        unsigned int b=__BIG_ENDIAN;
                        unsigned int c=__LITTLE_ENDIAN;])],
                      [AC_MSG_RESULT([yes])
                       need_endian_test=no],[AC_MSG_RESULT([no])])
    fi
fi
if test "$ac_cv_header_endian_h" == 'yes' ; then
    if test "$need_endian_test" == 'yes' ; then
        AC_MSG_CHECKING([whether endian can be determined from endian.h])
        AC_COMPILE_IFELSE([AC_LANG_PROGRAM([#include <endian.h>], [
                        unsigned int a=__BYTE_ORDER;
                        unsigned int b=__BIG_ENDIAN;
                        unsigned int c=__LITTLE_ENDIAN;])],
                      [AC_MSG_RESULT([yes])
                       need_endian_test=no],[AC_MSG_RESULT([no])])
    fi
fi

if test "$need_endian_test" == 'yes' ; then
  AC_C_BIGENDIAN
fi

AH_BOTTOM([
#if defined(HAVE_ENDIAN_H) || defined(HAVE_SYS_PARAM_H)
  #ifdef HAVE_SYS_PARAM_H
    #include <sys/param.h>
  #endif
  #if defined(HAVE_ENDIAN_H) && !defined(BYTE_ORDER) && !defined(__BYTE_ORDER)
    #include <endian.h>
  #endif
  #if defined(__BYTE_ORDER)
    #if __BYTE_ORDER == __BIG_ENDIAN
      #define WORDS_BIGENDIAN 1
    #endif
  #elif defined(BYTE_ORDER)
    #if BYTE_ORDER == BIG_ENDIAN
      #define WORDS_BIGENDIAN 1
    #endif
  #endif
#endif
])

AC_C_CONST
AC_C_INLINE

###############################
# Checks for library functions.
AC_PROG_GCC_TRADITIONAL
if test -z "${CONFIG_ORTE_RT}" ; then
AC_CHECK_FUNCS([gethostbyname getopt_long sigwaitinfo])
fi

AC_CONFIG_FILES([Makefile
                 orte/Makefile
		 orte/liborte/Makefile
		 orte/liborte/rtl/Makefile
		 orte/examples/Makefile
		 orte/examples/hello/Makefile
		 orte/examples/multicast/Makefile
		 orte/examples/reliable/Makefile
		 orte/examples/ping/Makefile
		 orte/examples/spy/Makefile
		 orte/examples/schneider/Makefile
		 orte/examples/mpo/Makefile
		 orte/idl-compiler/Makefile
		 orte/libjorte/Makefile
                 orte/manager/Makefile])

LIBS="$LIBS$INTERNAL_PTHREAD_LIBS"

AC_CONFIG_FILES([
modtool
])
AC_OUTPUT
chmod +x modtool

# ======================================================================
#		generate orte/include/orte/orte_config.h
# ======================================================================

AC_MSG_NOTICE([fixing orte/include/orte/orte_config.h])
sed -e "s/ PACKAGE/ ORTE_PACKAGE/" -e "s/ VERSION/ ORTE_VERSION/" \
    orte/include/orte/orte_config.h >orte/include/orte/orte_config.h.new
if cmp -s orte/include/orte/orte_config.h.new orte/include/orte/orte_config.h; then
	rm orte/include/orte/orte_config.h.new
	AC_MSG_NOTICE([orte/include/orte/orte_config.h is unchanged])
else
	mv orte/include/orte/orte_config.h.new orte/include/orte/orte_config.h
fi

echo \
"------------------------------------------------------------------------
Configuration ORTE:

  Source code location:       ${srcdir}
  Compiler:                   ${CC}
  Compiler flags:             ${CFLAGS}
  Host System Type:           ${host}
  
  See orte_config.h for future configuration information.
  
  Now you can run
  make  
  
------------------------------------------------------------------------"
	    
