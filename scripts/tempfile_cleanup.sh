#!/bin/bash -e
# Ref:
# http://stackoverflow.com/questions/3469705/how-to-run-script-commands-from-variables
# http://superuser.com/questions/375011/bash-script-to-delete-files-older-than-x-days-with-subdirectories
# http://superuser.com/questions/152958/exclude-hidden-files-when-searching-with-unix-linux-find
# http://stackoverflow.com/questions/13525004/how-to-exclude-this-current-dot-folder-from-find-type-d

usage() {
cat << EOF
usage: $0 options
This script use to clean up tempfile/dir

options:
    --dir                   cleanup dir(required)
    -t, --type              clean type f -- file , d -- dir, default are both
    --delta                 delta days
    --delta-min             delta minutes
    -k, --keyword           keyword
    -r, --recursive         default will cleanup file/dir with maxdepth = 1, using -r one can recursive delete files with '-t f' together
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
    TYPE=$TYPE
    DELTA_MINUTE=$DELTA_MINUTE
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
TYPE=
DELTA_MINUTE=$((24*30*60))
KEYWORD=""
RECURSIVE="-maxdepth 1"
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
        --type|-t)
            shift
            TYPE=" -type $1 "
            shift
            ;;
        --delta)
            shift
            DELTA_MINUTE=$(($1*24*60))
            shift 
            ;;
        --delta-min)
            shift
            DELTA_MINUTE=$1
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
            usage
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

LIST_CMD="cd $DIR && find . $RECURSIVE \( ! -name '.*' \) $KEYWORD -mmin +$DELTA_MINUTE $TYPE -exec echo '{}' \;"
CLEAN_CMD="cd $DIR && find . $RECURSIVE \( ! -name '.*' \) $KEYWORD -mmin +$DELTA_MINUTE $TYPE -exec rm -r '{}' '+'"

echo "tempfile cleanup at $DIR on `date`"

total=$(echo `bash -c "$LIST_CMD | wc -l"`)
echo "$total files will be deleted."

if [[ $DRY_RUN == 1 ]]; then
    dump_conf
    echo "dry run, nothing happened"
    exit 0
fi


if [[ $VERBOSE == 1 ]] ; then
    echo " Files to be deleted: "
    bash -c "$LIST_CMD | cat"
fi

#check 
if [[ $FORCE != 1 ]]; then
    while true; do
        read -p "Do you want to delete above $total files(yes or no) ?" yn
        case $yn in
            [Yy]* ) break;;
            [Nn]* ) echo "No files are deleted, exit..."; exit;;
            * ) echo "Please answer yes or no.";;
        esac
    done
fi

#apply
bash -c "$CLEAN_CMD"
echo "$total files have been deleted"
