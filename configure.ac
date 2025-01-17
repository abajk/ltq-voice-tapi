#
#
#  Copyright (c) 2001-2015 Lantiq Deutschland GmbH
#  Copyright (c) 2015-2016 Lantiq Beteiligungs-GmbH & Co.KG
#  Copyright 2016-2017, Intel Corporation.
#
#  For licensing information, see the file 'LICENSE' in the root folder of
#  this software module.
#
#

AC_PREREQ(2.59)
AC_COPYRIGHT([Copyright (C) 2001-2017, Lantiq Beteiligungs-GmbH & Co.KG
For licensing information please see the file 'LICENSE' in the root folder of
this software module.])

AC_REVISION($Revision: 1.9 $)

AC_INIT([TAPI v4 - The Common Voice API], [4.18.1.0], [Lantiq Beteiligungs-GmbH & Co.KG], [drv_tapi])
AC_CONFIG_SRCDIR(src/drv_tapi.h)
AM_INIT_AUTOMAKE([-Wno-portability tar-pax subdir-objects])

m4_pattern_allow([^AM_ACLOCAL_INCLUDE$])dnl
AM_ACLOCAL_INCLUDE(m4)

# save the configure arguments
# remove the install dir from the distcheck configure line to avoid that the
# installed binaries are deleted on distcheck. The regex will remove
# --prefix and all subsequent "non-space" chars from the configure options
# as well as the internal features.
# Note: The escaped \' are important.
# Note: Don't lin* - it would match also --enable-linux-26 (!)
CONFIGURE_OPTIONS=''
for c_arg in $ac_configure_args; do
   case $c_arg in
      \'--prefix=*)
         #echo "skipping configure option for distcheck: $c_arg"
         ;;
      *)
         CONFIGURE_OPTIONS="$CONFIGURE_OPTIONS $c_arg"
         ;;
   esac
done
AC_SUBST(CONFIGURE_OPTIONS)

AC_CONFIG_HEADER(include/drv_tapi_autoconf.h)

if [[ "$CFLAGS" == "" ]]; then
   CFLAGS="-O2"
fi

AC_PROG_CC
AM_PROG_CC_C_O
AC_PROG_RANLIB

AH_TOP(
[/******************************************************************************

  Copyright (c) 2001-2015 Lantiq Deutschland GmbH
  Copyright (c) 2015-2016 Lantiq Beteiligungs-GmbH & Co.KG
  Copyright 2016-2017, Intel Corporation.

  For licensing information, see the file 'LICENSE' in the root folder of
  this software module.

******************************************************************************/
#ifndef _DRV_CONFIG_H_
#define _DRV_CONFIG_H_]
)

AH_BOTTOM([
#endif /* _DRV_CONFIG_H_ */
])

AC_DEFINE_UNQUOTED([DRV_TAPI_CONFIGURE_STR], ["$ac_configure_args"], [configure options string])

## Target host specific compilation flags
AM_CONDITIONAL(PPC_6xx, false)
case "${host}" in
   "")
      SYS=unknown
      ;;
   mips*-linux*)
      AC_SUBST([CROSS_COMPILE],[${host}-])
      SYS=linux
      ;;
   powerpc*-linux*)
      AC_SUBST([CROSS_COMPILE],[${host}-])
      SYS=linux
      ;;
   ppc_6xx)
      AC_SUBST([CROSS_COMPILE],[ppc_6xx-])
      AM_CONDITIONAL(PPC_6xx, true)
      SYS=linux
      ;;
   powerpc-linux)
      AC_SUBST([CROSS_COMPILE],[powerpc-linux-])
      AM_CONDITIONAL(PPC_6xx, true)
      SYS=linux
      ;;
   i[[3456789]]86-*-linux*)
      SYS=linux
      ;;
   i[[3456789]]86-*-mingw32*)
      SYS=mingw32
      ;;
   *)
      SYS="${host_os}"
      ;;
esac
AM_CONDITIONAL(LINUX, test "${SYS}" = "linux")
AM_CONDITIONAL(WIN32, test "${SYS}" = "mingw32")
AM_CONDITIONAL(BUILD_SHARED_LIB, test "${SYS}" = "mingw32")

AS_IF([test "$SYS" = linux],[
   dnl check for Linux kernel 2.6.x support
   KERNEL_2_6_CHECK
   dnl Build of the Kernel modules under LINUX
   WITH_KERNEL_MODULE_CHECK
   LIBIFXOS_CHECK_CONFIG_INCL
   PROC_CHECK(TAPI_USE_PROC)
   LINUX_SMP_CHECK
], [
   AM_CONDITIONAL(KERNEL_2_6, false)
   AM_CONDITIONAL(WITH_KERNEL_MODULE, false)
])

TAPI_VERSION_CHECK

DISTRIBUTION_TYPE_CHECK

WARNINGS_CHECK
WERROR_CHECK
DEBUG_CHECK
TRACE_CHECK(
    AC_DEFINE([RUNTIME_TRACE],[1],[enable runtime traces as register access])
)
EVENT_COUNTER_CHECK

dnl Set project base directory path
DEFAULT_PRJ_BASE_PATH=''
AC_ARG_ENABLE(prjbase,
   AS_HELP_STRING(
      [--enable-prjbase=x],
      [Set the project base directory path (default is ~/project)]
   ),
   [
    if test -n $enableval; then
       AC_MSG_RESULT([Set the project base directory path $enableval])
       DEFAULT_PRJ_BASE_PATH=$enableval
       AC_SUBST([PRJ_BASE_PATH],[$DEFAULT_PRJ_BASE_PATH])
    else
       AC_MSG_RESULT([Set the default project base directory path $DEFAULT_PRJ_BASE_PATH])
       AC_SUBST([PRJ_BASE_PATH],[$DEFAULT_PRJ_BASE_PATH])
    fi
   ],
   [AC_SUBST([PRJ_BASE_PATH],[$DEFAULT_PRJ_BASE_PATH])]
)

dnl use linux bufferpool alloc
AC_MSG_CHECKING(for linux generic bufferpool allocation)
AC_ARG_WITH(linux-alloc,
    AS_HELP_STRING(
        [--with-linux-alloc],
        [use linux generic bufferpool allocation]
    ),
    [
        AC_MSG_RESULT([yes])
        AC_DEFINE([USE_LINUX_ALLOC],[1],[use linux bufferpool allocation])
    ],
    [
        AC_MSG_RESULT([no, set with --with-linux-alloc])
    ]
)

dnl check TAPI Calibration support
TAPI_CALIBRATION_CHECK([enable])

dnl enable TAPI Analog Line Network Line Testing support
TAPI_NLT_CHECK([disable])

dnl enable TAPI Analog Line Continuous Measurement support
TAPI_CONT_MEAS_CHECK([disable])

dnl enable TAPI Analog Line Capacitance Measurement support
TAPI_CAP_MEASUREMENT_CHECK([disable], [TAPI])

dnl enable TAPI HDLC support
TAPI_HDLC_CHECK([disable])

dnl enable TAPI Voice support
TAPI_VOICE_CHECK([enable])

dnl enable TAPI pulse dial/hook support and hook state machine
TAPI_DIAL_CHECK([enable], [TAPI_HSM_CHECK([enable])],)

dnl check TAPI DTMF support
TAPI_DTMF_CHECK([enable])

dnl check TAPI Tone Level Peak Detector support
TAPI_PEAKD_CHECK([enable])

dnl check TAPI MF R2 Tone Detector support
TAPI_MF_R2_CHECK([enable])

dnl check TAPI CID support
TAPI_CID_CHECK([enable])

dnl enable TAPI METERING support
TAPI_METERING_CHECK([disabled])

dnl check TAPI FAX support - old implementation
TAPI_FAX_CHECK([disable])

dnl check TAPI T38 Stack support - new implementation in FW
TAPI_FAXSTACK_CHECK([enable])

dnl enable TAPI FXS Phone Detection Support
TAPI_PHONE_DET_CHECK([disable])

dnl enable Power Management Control Support
TAPI_PMC_CHECK([disable], [TAPI_PMC_IF_CHECK()])

dnl enable TAPI FXO Support
TAPI_FXO_CHECK([enable])

dnl check TAPI Announcements support
TAPI_ANNOUNCEMENTS_CHECK([enable])

dnl check TAPI SRTP support
TAPI_SRTP_CHECK([disable])

dnl check TAPI Tonegen support
TAPI_TONE_GENERATOR_CHECK([enable], [TAPI])

dnl check TAPI MFTD support
TAPI_MFTD_CHECK([enable])

dnl check TAPI CPTD support
TAPI_CPTD_CHECK([enable])

dnl check TAPI MWL support
TAPI_MWL_CHECK([enable])

EVENT_LOGGER_CHECK_CONFIG
AS_IF([test "$SYS" = mingw32],[
   LIBIFXOS_CHECK_CONFIG
   EVENT_LOGGER_LIB_CHECK
])

dnl enable QoS Mode
TAPI_QOS_CHECK([disable])

dnl check KPI tasklet support
TAPI_KPI_TASKLET_CHECK([enable])

dnl enable Kernel Packet Interface (KPI)
TAPI_KPI_CHECK([disable])

dnl PCM channel support
TAPI_PCM_CHECK([enable])

dnl enable DECT channel support
TAPI_DECT_CHECK([disable])

dnl enable read/write packet interface
TAPI_PACKET_CHECK

dnl enable Package statistic support
TAPI_PKG_STAT_CHECK

dnl enable owner id for packet interface.
dnl DEBUG feature to tag buffers on their way through the system to detect leakages
TAPI_PKG_OWNER_ID_CHECK

dnl enable hotplug events support
TAPI_HOTPLUG_CHECK

dnl enable MOS-LQE calculation support
TAPI_MOSLQE_CHECK([disable])

dnl enable ring-engine support
TAPI_RINGENGINE_CHECK([enable])

dnl enable Linux kernelspace API support
TAPI_KERNEL_API_CHECK([enable], [TAPI])

dnl enable SmartSLIC support
TAPI_SSLIC_CHECK([enable])

dnl enable LEC support
TAPI_LEC_CHECK([enable])

WITH_CFLAGS_CHECK

AC_DEFINE_UNQUOTED([WITH_CLFAGS_CONFIGURE_OPTION],[$CFLAGS],[environment and device specific CFLAGS passed to configure])

AC_CONFIG_COMMANDS_PRE([])

AC_CONFIG_FILES([Makefile])
AC_CONFIG_FILES([src/Makefile])
AC_CONFIG_FILES([xml/Makefile])

AC_OUTPUT

echo \
"------------------------------------------------------------------------
drv_tapi configuration:

  TAPI API version               ${cached_tapi_version}

  Source code location:          ${srcdir}
  CROSS_COMPILE:                 ${CROSS_COMPILE}
  Compiler:                      ${CC}
  Compiler flags:                ${CFLAGS}
  Host System Type:              ${host}
  Install path:                  ${prefix}

  KERNEL_INCL_PATH:              ${KERNEL_INCL_PATH}
  KERNEL_BUILD_PATH:             ${KERNEL_BUILD_PATH}
  IFXOS includes path:           ${IFXOS_INCL_PATH}
  IFXOS library path:            ${IFXOS_LIBRARY_PATH}
  Event logger includes path:    ${EVENT_LOGGER_INCL_PATH}
  Event logger library path:     ${EVENT_LOGGER_LIBRARY_PATH}
  SRTP library includes path:    ${SRTP_INCL_PATH}
------------------------------------------------------------------------"
