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
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/src/main.o \
	${OBJECTDIR}/src/file/PosixFileImpl.o \
	${OBJECTDIR}/src/sockets/SocketException.o \
	${OBJECTDIR}/src/file/md5.o \
	${OBJECTDIR}/src/file/AbstractFile.o \
	${OBJECTDIR}/src/sockets/Socket.o \
	${OBJECTDIR}/src/sockets/InputStream.o \
	${OBJECTDIR}/src/file/WinFileImpl.o \
	${OBJECTDIR}/src/sockets/OutputStream.o


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
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/yaxl

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/yaxl: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/yaxl ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/src/main.o: src/main.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/main.o src/main.cpp

${OBJECTDIR}/src/file/PosixFileImpl.o: src/file/PosixFileImpl.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/file
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/file/PosixFileImpl.o src/file/PosixFileImpl.cpp

${OBJECTDIR}/src/sockets/SocketException.o: src/sockets/SocketException.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/sockets
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/sockets/SocketException.o src/sockets/SocketException.cpp

${OBJECTDIR}/src/file/md5.o: src/file/md5.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/file
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/file/md5.o src/file/md5.cpp

${OBJECTDIR}/src/file/AbstractFile.o: src/file/AbstractFile.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/file
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/file/AbstractFile.o src/file/AbstractFile.cpp

${OBJECTDIR}/src/sockets/Socket.o: src/sockets/Socket.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/sockets
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/sockets/Socket.o src/sockets/Socket.cpp

${OBJECTDIR}/src/sockets/InputStream.o: src/sockets/InputStream.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/sockets
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/sockets/InputStream.o src/sockets/InputStream.cpp

${OBJECTDIR}/src/file/WinFileImpl.o: src/file/WinFileImpl.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/file
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/file/WinFileImpl.o src/file/WinFileImpl.cpp

${OBJECTDIR}/src/sockets/OutputStream.o: src/sockets/OutputStream.cpp 
	${MKDIR} -p ${OBJECTDIR}/src/sockets
	${RM} $@.d
	$(COMPILE.cc) -g -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/sockets/OutputStream.o src/sockets/OutputStream.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/yaxl

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
