#!/bin/bash
TIME_BEGIN=$( date -u +%s )

CMAKE_BUILD_TYPE=Release
BUILD_DIR="./build"
SRC_DIR="$(pwd)"
JOBS=`getconf _NPROCESSORS_ONLN`

printf "%s\\n" "$( date -u )"
printf "User: %s\\n" "$( whoami )"

ARCH=$( uname )
printf "\\nARCHITECTURE: %s\\n" "${ARCH}"
printf "\\nNumber of cores detected: %s\\n" "${JOBS}"

# Find and use existing CMAKE
export CMAKE=$(command -v cmake 2>/dev/null)

printf "\\n========================================================================\\n"
printf "## CMAKE_BUILD_TYPE=%s\\n" "${CMAKE_BUILD_TYPE}"

mkdir $BUILD_DIR
cd $BUILD_DIR

make clean
$CMAKE ${SRC_DIR} -G "Unix Makefiles" -DCMAKE_BUILD_TYPE="${CMAKE_BUILD_TYPE}" -DBUILD_DOXYGEN="${DOXYGEN}"

if [ $? -ne 0 ]; then exit -1; fi
 make -j"${JOBS}"
if [ $? -ne 0 ]; then exit -1; fi

TIME_END=$(( $(date -u +%s) - $TIME_BEGIN ))
