#!/bin/sh

if test -f status.log; then
  wc_f=`grep "FAILED: $1" status.log | wc -l`
  wc_p=`grep "PASSED: $1" status.log | wc -l`

  if test $wc_f -eq 0 && test $wc_p -gt 0; then
    echo "PASSED: $1"
  else
    echo "FAILED: $1"
  fi
else
  echo "FAILED: $1 - no status.log"
fi
