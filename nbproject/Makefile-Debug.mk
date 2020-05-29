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
	${OBJECTDIR}/EventHandler.o \
	${OBJECTDIR}/L298N_Jetson.o \
	${OBJECTDIR}/Motor.o \
	${OBJECTDIR}/Robot.o \
	${OBJECTDIR}/Servo.o \
	${OBJECTDIR}/lidar_driver.o \
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
LDLIBSOPTIONS=-L/usr/local/lib -L/usr/include/hal -L/usr/include/i2c -L/usr/include/linux -levdev -lrplidar_sdk -lpthread -li2c -lJetsonGPIO

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/r_l

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/r_l: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/r_l ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/EventHandler.o: EventHandler.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/i2c -I/usr/include -I/usr/local/include -I/usr/include/libevdev-1.0/libevdev -I/usr/include/hal -include /usr/include/rplidar.h -include /usr/include/linux/i2c-dev.h -include /usr/include/libevdev-1.0/libevdev/libevdev.h -include /usr/include/hal/types.h -include /usr/local/include/JetsonGPIO.h -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/EventHandler.o EventHandler.cpp

${OBJECTDIR}/L298N_Jetson.o: L298N_Jetson.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/i2c -I/usr/include -I/usr/local/include -I/usr/include/libevdev-1.0/libevdev -I/usr/include/hal -include /usr/include/rplidar.h -include /usr/include/linux/i2c-dev.h -include /usr/include/libevdev-1.0/libevdev/libevdev.h -include /usr/include/hal/types.h -include /usr/local/include/JetsonGPIO.h -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/L298N_Jetson.o L298N_Jetson.cpp

${OBJECTDIR}/Motor.o: Motor.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/i2c -I/usr/include -I/usr/local/include -I/usr/include/libevdev-1.0/libevdev -I/usr/include/hal -include /usr/include/rplidar.h -include /usr/include/linux/i2c-dev.h -include /usr/include/libevdev-1.0/libevdev/libevdev.h -include /usr/include/hal/types.h -include /usr/local/include/JetsonGPIO.h -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Motor.o Motor.cpp

${OBJECTDIR}/Robot.o: Robot.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/i2c -I/usr/include -I/usr/local/include -I/usr/include/libevdev-1.0/libevdev -I/usr/include/hal -include /usr/include/rplidar.h -include /usr/include/linux/i2c-dev.h -include /usr/include/libevdev-1.0/libevdev/libevdev.h -include /usr/include/hal/types.h -include /usr/local/include/JetsonGPIO.h -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Robot.o Robot.cpp

${OBJECTDIR}/Servo.o: Servo.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/i2c -I/usr/include -I/usr/local/include -I/usr/include/libevdev-1.0/libevdev -I/usr/include/hal -include /usr/include/rplidar.h -include /usr/include/linux/i2c-dev.h -include /usr/include/libevdev-1.0/libevdev/libevdev.h -include /usr/include/hal/types.h -include /usr/local/include/JetsonGPIO.h -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/Servo.o Servo.cpp

${OBJECTDIR}/lidar_driver.o: lidar_driver.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/i2c -I/usr/include -I/usr/local/include -I/usr/include/libevdev-1.0/libevdev -I/usr/include/hal -include /usr/include/rplidar.h -include /usr/include/linux/i2c-dev.h -include /usr/include/libevdev-1.0/libevdev/libevdev.h -include /usr/include/hal/types.h -include /usr/local/include/JetsonGPIO.h -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/lidar_driver.o lidar_driver.cpp

${OBJECTDIR}/main.o: main.cpp
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.cc) -g -I/usr/include/i2c -I/usr/include -I/usr/local/include -I/usr/include/libevdev-1.0/libevdev -I/usr/include/hal -include /usr/include/rplidar.h -include /usr/include/linux/i2c-dev.h -include /usr/include/libevdev-1.0/libevdev/libevdev.h -include /usr/include/hal/types.h -include /usr/local/include/JetsonGPIO.h -std=c++14 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main.o main.cpp

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
