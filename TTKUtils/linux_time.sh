#!/bin/sh  
find . -exec touch -c -m -d "2024-12-05 12:00" {} \;
