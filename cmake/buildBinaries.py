#!/usr/bin/python
# Builds jsbsim binaries for Linux, Mac OS X, and Windows (via mingw)
# Notes: 
#   This script must be located one directory deeper than CMakeLists.txt
#   For Linux cross-compiling, mingw must be installed
#    and cmake-mingw must be in path (e.g. a shell script)

# Lenna X. Peterson

import os # for os stuff
import sys # for determining os
import inspect # for finding current directory
import subprocess # for calling processes

### Path handling ###
# __file__ doesn't work consistently on windows
scriptDir = os.path.abspath(os.path.split(inspect.getfile(inspect.currentframe()))[0])
buildDir = os.path.normpath(os.path.join(scriptDir, "../build"))
#print buildDir
def createDir(_dir):
    if not os.path.exists(_dir):
        print "Creating build directory"
        os.mkdir(_dir)
    try:
        os.chdir(_dir)
    except OSError:
        print "Could not move to build directory."
        print "This script is probably in the wrong directory."
        raise SystemExit

createDir(buildDir)

### Functions for building and packaging ###
cmakeArgs = [".."] 
marker = "***"
status2 = "%s Running `%s`"
try: 
    def callCMake(mingw=False, *args):
        _cmakeCall = list(cmakeArgs)
        # Sets DWITH_GUI default to y
        if "-DWITH_GUI=n" not in args:
            _cmakeCall.append("-DWITH_GUI=y")
        for a in args:
            _cmakeCall.append(a)
        if mingw:
            _cmakeCall.insert(0, "cmake-mingw")
        else:
            _cmakeCall.insert(0, "cmake")
        print status2 % ( marker, " ".join(_cmakeCall) )
        subprocess.check_call("rm -f CMakeCache.txt", shell=True)
        subprocess.check_call(_cmakeCall) 
        print status2 % ( marker, "make" )
        subprocess.check_call("make") 

    def callCPack(*args):
        _cpackCall = ["cpack"]
        for a in args:
            _cpackCall.append(a)
        print status2 % ( marker, " ".join(_cpackCall) )
        subprocess.check_call(_cpackCall)
     
### Main code to build and package ###
    if sys.platform.startswith('darwin'):
        print "Building for Darwin"
        # WITH_OSXBUNDLE defaults to ON
        callCMake()
        callCPack()
        print "OS X app bundle built"
        # Current setup requires remaking to change paths
        callCMake("-DWITH_OSXBUNDLE=n")
        callCPack()
        print "OS X pkg installer built" 
    elif sys.platform.startswith('linux'):
        print "Building for Linux"
        callCMake()
        callCPack()
        print "Linux Debian package built"
        callCPack("-G","STGZ")
        print "Generic Linux package built"
        # Change to directory to cross-compile for windows
        mingwDir = os.path.normpath(os.path.join(buildDir, "../build-mingw"))
        createDir(mingwDir)
        #print os.getcwd()
        callCMake("mingw=True")
        callCPack()
        print "Windows (mingw) package built"
    else:
        print "Nothing to do on %s" % sys.platform
        raise SystemExit

except KeyboardInterrupt:
    print "\n",
