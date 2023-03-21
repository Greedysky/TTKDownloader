#!/bin/sh  
find . -exec touch -c -m -d "2022-11-14 12:00" {} \;
