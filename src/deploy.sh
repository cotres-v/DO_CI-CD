#!/bin/bash

S21_CAT_PATH="/home/gitlab-runner/builds/E_zamZut/0/students/DO6_CICD.ID_356283/vickonsl/DO6_CICD-1/src/cat/s21_cat"
S21_GREP_PATH="/home/gitlab-runner/builds/E_zamZut/0/students/DO6_CICD.ID_356283/vickonsl/DO6_CICD-1/src/grep/s21_grep"

REMOTE_USER="viktor"           
REMOTE_HOST="192.168.1.74"   
REMOTE_DIR="/usr/local/bin"  

chmod +x $S21_CAT_PATH $S21_GREP_PATH

scp $S21_CAT_PATH $S21_GREP_PATH $REMOTE_USER@$REMOTE_HOST:$REMOTE_DIR

if [ $? -eq 0 ]; then
    echo "Артефакты успешно скопированы на $REMOTE_HOST."
else
    echo "Ошибка при копировании артефактов."
    exit 1
fi