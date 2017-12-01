#!/usr/bin/env bash
CWD_DIFF=".."
PARSER_PATH=${CWD_DIFF}/../parser
PARSER_PATH="$(cd "$PARSER_PATH"; pwd)"
FTRANSFORM_PATH=${CWD_DIFF}/..
FTRANSFORM_PATH="$(cd "$FTRANSFORM_PATH"; pwd)"
PARSER_EXEC=${PARSER_PATH}/parser
FTRANSFORM_EXEC=${FTRANSFORM_PATH}/ftransform
export PARSER_EXEC
export FTRANSFORM_EXEC
if [ ! -f ${FTRANSFORM_EXEC} ]; then
    echo "Need to build ftransform"
    (cd ${FTRANSFORM_PATH}; ./rebuild.sh)
fi
if [ ! -f ${PARSER_EXEC} ]; then
    echo "Need to build parser"
    (cd ${PARSER_PATH}; ./rebuild.sh)
fi