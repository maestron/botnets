#!/bin/sh
SOURCE_DIR="/mnt/ago/d/MyProjects/agobot3_current"
DAOLDPWD=`pwd`
cd $SOURCE_DIR

NUM_FILES=`for file in \`cat files.txt\` ; do echo $file ; done | wc -l`
NUM_LINES=`for file in \`cat files.txt\` ; do cat $file ; done | wc -l`
NUM_WORDS=`for file in \`cat files.txt\` ; do cat $file ; done | wc -w`
NUM_CHARS=`for file in \`cat files.txt\` ; do cat $file ; done | wc -c`

echo "$NUM_FILES $NUM_LINES $NUM_WORDS $NUM_CHARS"

cd $DAOLDPWD
