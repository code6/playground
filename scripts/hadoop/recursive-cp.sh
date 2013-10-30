#!/bin/bash -e

usage() {
cat << EOF
usage: $0 options
This script use to recursive cherry-pick commits which affect target commits from current branch.

options:
    -h              show help message
    -t sha          target commit sha
    -v              verbose
EOF
}

TARGET_SHA=
VERBOSE=

while getopts "ht:v" OPTION
do
    case $OPTION in
        h)
            usage
            exit 1
            ;;
        t)
            TARGET_SHA=$OPTARG
            ;;
        v)
            VERBOSE=1
            ;;
        ?)
            usage
            exit
            ;;
    esac
done

if [[ $VERBOSE == 1 ]] ; then
  set -x
fi

if [[ -z $TARGET_SHA ]]; then
    usage
    exit 1
fi

## Check target sha exist
