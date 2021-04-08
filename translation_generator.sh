#!/bin/bash

# Create translation files
# .po files in po/
# Convert them to qm
LANGS="en zh_CN zh_TW"
mkdir -p mobileData/translations/stellarium
mkdir -p mobileData/translations/stellarium-skycultures
for lang in $LANGS; do
    "G:\Qt\5.15.2\android\bin\lconvert.exe" -i po/stellarium/$lang.po \
             -o mobileData/translations/stellarium/$lang.qm
    "G:\Qt\5.15.2\android\bin\lconvert.exe" -i po/stellarium-skycultures/$lang.po \
             -o mobileData/translations/stellarium-skycultures/$lang.qm
done
