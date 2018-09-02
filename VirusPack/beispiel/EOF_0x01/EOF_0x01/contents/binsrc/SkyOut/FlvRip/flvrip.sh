#!/bin/sh
#
# This program is still considered Beta.
# It has been tested on OpenBSD 4.0 with the Kornshell!
#
# With this tool you can download a file either from YouTube
# or GoogleVideo, by giving the URL the file will be automatically
# downloaded and converted into Mpeg video format (using ffmpeg).
#
# Example: http://youtube.com/watch?v=XXX myfilename
#
# Author: SkyOut
# Date: December 2006
#
# Comment: This tool is for all the ones using a system, that has
# no Flash installed, may it be because the user does not like
# binary (and the many Flash bugs) or just because it is not
# supported on the system.
#

#
# Parameters, that are used by the program.
# Filename is optional (default: "youtube.mpg" or "googlevideo.mpg")
#

site=$1
url=$2
filename=$3

#
# Download a file from the YouTube website!
#

function youtube {
	wget $url -O youtube.htm
	line=`less youtube.htm | grep 'player2.swf?video_id=' | awk '{print $5}'`
	rm youtube.htm
	name=`echo $line | cut -c 25-`
	numofchar=`echo $name | wc -c | sed 's/ //g'`
	numofchar=`expr $numofchar - 3`
	name=`echo $name | cut -c 1-$numofchar`
	name=http://youtube.com/get_video?$name
	wget $name -O youtube.flv
	ffmpeg -i youtube.flv -ab 56 -ar 22050 -b 500 -s 320x240 youtube.mpg
	if [ "$filename" != "" ]
	then
		filename=$filename.mpg
		mv youtube.mpg $filename
	fi
	rm youtube.flv
	exit 0
}

#
# Download a file from the GoogleVideo website!
#

function googlevideo {
	wget $url -O googlevideo.htm
	line=`less googlevideo.htm | grep 'googleplayer.swf' | awk '{print $7}'`
	rm googlevideo.htm
	name=`echo $line | cut -c 45-`
	numofchar=`echo $name | wc -c | sed 's/ //g'`
	numofchar=`expr $numofchar - 161`
	name=`echo $name | cut -c 1-$numofchar`
	name=`echo $name | sed 's/%3A/:/g'`
	name=`echo $name | sed 's/%2F/\//g'`
	name=`echo $name | sed 's/%3F/?/g'`
	name=`echo $name | sed 's/%3D/=/g'`
	name=`echo $name | sed 's/%26/\&/g'`
	wget $name -O googlevideo.flv
	ffmpeg -i googlevideo.flv -ab 56 -ar 22050 -b 500 -s 320x240 googlevideo.mpg
	if [ "$filename" != "" ]
	then
		filename=$filename.mpg
		mv googlevideo.mpg $filename
	fi
	rm googlevideo.flv
	exit 0
}

#
# Display the usage dialogue!
#

function usage {
	echo ""
	echo "#	Usage: flvrip.sh -yt|gv|h [filename]"
	echo "#"
	echo "#	-yt	Rip a YouTube file"
	echo "#		Example: http://youtube.com/watch?v=XXX"
	echo "#	-gv	Rip a GoogleVideo file"
	echo "#		Example: http://video.google.com/videoplay?docid=XXX"
	echo "#	-h	Help (this one)"
	echo "#"
	echo "#	If you don't set a filename default names will be chosen"
	echo "#	Important: For the URL use the syntax as shown above!"
	echo ""
	exit 0
}

#
# Main code, check for the first argument...
#

case "$site" in
	-yt)	if [ "$url" = "" ]
		then
			usage
			exit 0
		fi
		check=`echo $url | cut -c 1-24`
		if [ "$check" != "http://youtube.com/watch" ]
		then
			usage
			exit 0
		fi
		youtube
		;;
	-gv)	if [ "$url" = "" ]
		then
			usage
			exit 0
		fi
		check=`echo $url | cut -c 1-33`
		if [ "$check" != "http://video.google.com/videoplay" ]
		then
			usage
			exit 0
		fi
		googlevideo
		;;
	-h)	usage
		;;
	*)	usage
		;;
esac