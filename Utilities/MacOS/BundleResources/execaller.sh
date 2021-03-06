#!/bin/sh
#
# This script calls the ITK-SNAP inside of its bundle in the Applications directory. 
# It was modeled after the mvim script that comes with MacVim
#
# The script looks for the ITK-SNAP binary in a list of directories. If you want to
# tell the script where to look, set the environment variable ITKSNAP_APP_DIR, e.g.:
#
# ITKSNAP_APP_DIR=/Applications
#

# Try to find the ITK-SNAP application somewhere
if [ -z "$ITKSNAP_APP_DIR" ]
then
 	myDir="`dirname "$0"`"
	myAppDir="$myDir/../Applications"
	for i in ~/Applications $myDir $myAppDir /Applications; do
    if [ -x "$i/ITK-SNAP.app" ]; then
			ITKSNAP_APP_DIR="$i"
			break
		fi
  done
fi

# Try to find the ITK-SNAP application somewhere
if [ -z "$ITKSNAP_APP_DIR" ]
then
	echo "Cannot find ITK-SNAP.app. Try setting the ITKSNAP_APP_DIR environment variable to the directory containing ITK-SNAP.app"
	exit 1
fi

# Try to find the binary to launch
binary="$ITKSNAP_APP_DIR/ITK-SNAP.app/Contents/@EXENAME@"

# Call the binary
exec $binary @EXEOPTS@ ${1:+"$@"}







