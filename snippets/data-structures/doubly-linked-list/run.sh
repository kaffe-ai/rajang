#!/bin/bash


# run the app with this file as input
FPATH_INPUT=""

# binary target(s)
BIN_TARGET="app"
BIN_DEBUG="bin/debug/$BIN_TARGET"
BIN_RELEASE="bin/release/$BIN_TARGET"

SELF_NAME="$(basename "$0")"

if [ -f $BIN_RELEASE ]; then
    if [ -f $BIN_DEBUG ]; then
        echo "$SELF_NAME: Found multiple binary targets. Defaulting to release build at $BIN_RELEASE."
    fi
    echo "$SELF_NAME: Running release build with $FPATH_INPUT as input."
    # exec $BIN_RELEASE --fpath=$FPATH_INPUT
    exec $BIN_RELEASE
elif [ -f $BIN_DEBUG ]; then
    echo "$SELF_NAME: Running development build with tests enabled and $FPATH_INPUT as input."
    # exec $BIN_DEBUG --test --fpath=$FPATH_INPUT
    exec $BIN_DEBUG
else
  echo "$SELF_NAME: Error - No binary target found. Compile with make before running this script."
  exit 1
fi
