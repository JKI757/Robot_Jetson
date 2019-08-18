#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=GNU-Linux
CND_DLIB_EXT=so
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/_ext/8bd51d73/GpioHandler.o \
	${OBJECTDIR}/EventHandler.o \
	${OBJECTDIR}/Robot.o \
	${OBJECTDIR}/i2cInterface.o \
	${OBJECTDIR}/main.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=-L/usr/local/lib -levdev /usr/local/lib/libgpiod.a -li2c

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/robot_libevdev

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/robot_libevdev: /usr/local/lib/libgpiod.a

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/robot_libevdev: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/robot_libevdev ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/_ext/8bd51d73/GpioHandler.o: ../gpio_test/GpioHandler.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/8bd51d73
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/local/lib -include /usr/local/include/libevdev-1.0/libevdev/libevdev.h -include /usr/local/include/gpiod.h -include /usr/local/include/i2c.h -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/8bd51d73/GpioHandler.o ../gpio_test/GpioHandler.cpp

${OBJECTDIR}/EventHandler.o: EventHandler.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/local/lib -include /usr/local/include/libevdev-1.0/libevdev/libevdev.h -include /usr/local/include/gpiod.h -include /usr/local/include/i2c.h -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/EventHandler.o EventHandler.cpp

${OBJECTDIR}/Robot.o: Robot.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/local/lib -include /usr/local/include/libevdev-1.0/libevdev/libevdev.h -include /usr/local/include/gpiod.h -include /usr/local/include/i2c.h -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Robot.o Robot.cpp

${OBJECTDIR}/i2cInterface.o: i2cInterface.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/local/lib -include /usr/local/include/libevdev-1.0/libevdev/libevdev.h -include /usr/local/include/gpiod.h -include /usr/local/include/i2c.h -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/i2cInterface.o i2cInterface.cpp

${OBJECTDIR}/main.o: main.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/local/lib -include /usr/local/include/libevdev-1.0/libevdev/libevdev.h -include /usr/local/include/gpiod.h -include /usr/local/include/i2c.h -std=c++11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main.o main.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
