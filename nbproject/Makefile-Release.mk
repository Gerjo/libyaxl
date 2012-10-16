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
CND_PLATFORM=GNU-Linux-x86
CND_DLIB_EXT=so
CND_CONF=Release
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/libyaxl/sockets/InputStream.o \
	${OBJECTDIR}/libyaxl/sockets/Socket.o \
	${OBJECTDIR}/libyaxl/sockets/OutputStream.o \
	${OBJECTDIR}/libyaxl/concurrency/Thread.o \
	${OBJECTDIR}/libyaxl/examples/examples.o \
	${OBJECTDIR}/libyaxl/file/WinFileImpl.o \
	${OBJECTDIR}/libyaxl/file/AbstractFile.o \
	${OBJECTDIR}/libyaxl/sockets/ServerSocket.o \
	${OBJECTDIR}/libyaxl/file/PosixFileImpl.o \
	${OBJECTDIR}/libyaxl/file/md5.o


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
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libyaxl

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libyaxl: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libyaxl ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/libyaxl/sockets/InputStream.o: libyaxl/sockets/InputStream.cpp 
	${MKDIR} -p ${OBJECTDIR}/libyaxl/sockets
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/libyaxl/sockets/InputStream.o libyaxl/sockets/InputStream.cpp

${OBJECTDIR}/libyaxl/sockets/Socket.o: libyaxl/sockets/Socket.cpp 
	${MKDIR} -p ${OBJECTDIR}/libyaxl/sockets
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/libyaxl/sockets/Socket.o libyaxl/sockets/Socket.cpp

${OBJECTDIR}/libyaxl/sockets/OutputStream.o: libyaxl/sockets/OutputStream.cpp 
	${MKDIR} -p ${OBJECTDIR}/libyaxl/sockets
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/libyaxl/sockets/OutputStream.o libyaxl/sockets/OutputStream.cpp

${OBJECTDIR}/libyaxl/concurrency/Thread.o: libyaxl/concurrency/Thread.cpp 
	${MKDIR} -p ${OBJECTDIR}/libyaxl/concurrency
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/libyaxl/concurrency/Thread.o libyaxl/concurrency/Thread.cpp

${OBJECTDIR}/libyaxl/examples/examples.o: libyaxl/examples/examples.cpp 
	${MKDIR} -p ${OBJECTDIR}/libyaxl/examples
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/libyaxl/examples/examples.o libyaxl/examples/examples.cpp

${OBJECTDIR}/libyaxl/file/WinFileImpl.o: libyaxl/file/WinFileImpl.cpp 
	${MKDIR} -p ${OBJECTDIR}/libyaxl/file
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/libyaxl/file/WinFileImpl.o libyaxl/file/WinFileImpl.cpp

${OBJECTDIR}/libyaxl/file/AbstractFile.o: libyaxl/file/AbstractFile.cpp 
	${MKDIR} -p ${OBJECTDIR}/libyaxl/file
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/libyaxl/file/AbstractFile.o libyaxl/file/AbstractFile.cpp

${OBJECTDIR}/libyaxl/sockets/ServerSocket.o: libyaxl/sockets/ServerSocket.cpp 
	${MKDIR} -p ${OBJECTDIR}/libyaxl/sockets
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/libyaxl/sockets/ServerSocket.o libyaxl/sockets/ServerSocket.cpp

${OBJECTDIR}/libyaxl/file/PosixFileImpl.o: libyaxl/file/PosixFileImpl.cpp 
	${MKDIR} -p ${OBJECTDIR}/libyaxl/file
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/libyaxl/file/PosixFileImpl.o libyaxl/file/PosixFileImpl.cpp

${OBJECTDIR}/libyaxl/file/md5.o: libyaxl/file/md5.cpp 
	${MKDIR} -p ${OBJECTDIR}/libyaxl/file
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/libyaxl/file/md5.o libyaxl/file/md5.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/libyaxl

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
