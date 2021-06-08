AC_DEFUN([AX_CHECK_ACL],[

#Check if an ACL implementation is installed.
AC_ARG_WITH(acl,
[AS_HELP_STRING([--with-acl,--with-acl=PATH],
                [search in system directories or specify prefix directory for installed ACL package])])
AC_ARG_WITH(acl-include,
[AS_HELP_STRING([--with-acl-include=PATH],
                [specify directory for installed ACL include files])])
AC_ARG_WITH(acl-lib,
[AS_HELP_STRING([--with-acl-lib=PATH],
                [specify directory for the installed ACL library])])

# Search for ACL by default
AS_IF([test "$with_acl" != yes],[
  aclinc="-I$with_acl/include"
  AS_IF([test -d $with_acl/lib64/stub],
    [olibdir=$with_acl/lib64/stub],
    [olibdir=$with_acl/lib/stub])

  acllib="-L$olibdir -Wl,-rpath,$olibdir"
])

AS_IF([test "x$with_acl_include" != x],[
  aclinc="-I$with_acl_include"
])
AS_IF([test "x$with_acl_lib" != x],[
  acllib="-L$with_acl_lib -Wl,-rpath,$with_acl_lib"
])

# Tests if provided headers and libraries are usable and correct
AX_VAR_PUSHVALUE([CPPFLAGS],[$CPPFLAGS $aclinc])
AX_VAR_PUSHVALUE([CFLAGS])
AX_VAR_PUSHVALUE([LDFLAGS],[$LDFLAGS $acllib])
AX_VAR_PUSHVALUE([LIBS],[])


AC_CHECK_HEADERS([acl/acl.h acl/ops/acl_cblas.h], [acl=yes], [acl=no])
search_libs="ascendcl acl_cblas"
required_libs=""

m4_foreach([function],
           [aclInit,
            aclrtCreateStream,
            aclopExecute,
            aclblasGemmEx],
           [
             AS_IF([test "$acl" = "yes"],[
               AC_SEARCH_LIBS(function,
                              [$search_libs],
                              [acl=yes],
                              [acl=no],
                              [$required_libs])dnl
             ])
           ])dnl

acllibs=$LIBS

AX_VAR_POPVALUE([CPPFLAGS])
AX_VAR_POPVALUE([CFLAGS])
AX_VAR_POPVALUE([LDFLAGS])
AX_VAR_POPVALUE([LIBS])

AS_IF([test "$acl" != "yes"],[
    AC_MSG_ERROR([
------------------------------
ACL path was not correctly specified.
Please, check that the provided directories are correct.
------------------------------])
])

AC_SUBST([acl])
AC_SUBST([aclinc])
AC_SUBST([acllib])
AC_SUBST([acllibs])

])dnl AX_CHECK_ACL

