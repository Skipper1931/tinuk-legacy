#!/bin/sh
#if echo "$1" | grep -Eq 'i[[:digit:]]86-'; then
if echo "$1" | grep -Eq 'x86_64-'; then
  echo x86_64
else
  echo "$1" | grep -Eo '^[[:alnum:]_]*'
fi

#echo x86_64
