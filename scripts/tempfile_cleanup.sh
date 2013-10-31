#!/bin/bash -e
# Ref: http://stackoverflow.com/questions/3469705/how-to-run-script-commands-from-variables
#

usage() {
cat << EOF
usage: $0 options
This script use to clean up tempfile/dir

options:
    --dir                   cleanup dir(required)
    --delta                 delta days
    -k, --keyword           keyword
    -r, --recursive         recursive clean up tempfile, otherwise only clean files with depth=1
    -f, --force             force delete without confirm
    -v, --verbose           show all deleted files/dir if verbose is on
    --dry-run               just dump conf, no run
    -h, --help              show help message
EOF
}


dump_conf() {
cat << EOF
conf = 
    DIR=$DIR
    DELTA=$DELTA
    KEYWORD=$KEYWORD
    RECURSIVE=$RECURSIVE
    VERBOSE=$VERBOSE
    FORCE=$FORCE
    DRY_RUN=$DRY_RUN

COMMAND=
LIST_CMD=$LIST_CMD
CLEAN_CMD=$CLEAN_CMD
EOF
}

DIR=
DELTA=30
KEYWORD=""
RECURSIVE="-maxdepth 1 -type f"
VERBOSE=
FORCE=
DRY_RUN=

while [ $# -gt 0 ]; do
    case "$1" in
        --dir)
            shift
            DIR=$1
            shift
            ;;
        --delta)
            shift
            DELTA=$1
            shift 
            ;;
        --recursive|-r)
            shift
            RECURSIVE=""
            ;;
        --keyword|-k)
            shift
            KEYWORD=" -name '*$1*' "
            shift 
            ;;
        --force|-f)
            shift
            FORCE=1 
            ;;
        --verbose|-v)
            shift
            VERBOSE=1
            ;;
        --dry-run)
            shift 1
            DRY_RUN=1
            ;;
        --help|-h)
            help
            exit 0
            ;;
        *)
            echo "Unsupported param $1"
            exit 1
            ;;
    esac
done

if [[ -z $DIR ]]; then
    usage
    exit 1
fi

LIST_CMD="cd $DIR && find . $KEYWORD $RECURSIVE -mtime +$DELTA -exec echo '{}' \;"
CLEAN_CMD="cd $DIR && find . $KEYWORD $RECURSIVE -mtime +$DELTA -delete;"

if [[ $DRY_RUN == 1 ]]; then
    dump_conf
    exit 0
fi

if [[ $VERBOSE == 1 ]] ; then
    echo " Files to be deleted: "
    bash -c "$LIST_CMD | cat"
else
    echo " Files to be deleted(top 50): "
    bash -c "$LIST_CMD | head -n 50"
fi

#check 
if [[ $FORCE != 1 ]]; then
    while true; do
        read -p "Do you want to delete above files(yes or no) ?" yn
        case $yn in
            [Yy]* ) break;;
            [Nn]* ) echo "No files are deleted, exit..."; exit;;
            * ) echo "Please answer yes or no.";;
        esac
    done
fi

#apply
bash -c "$CLEAN_CMD"
