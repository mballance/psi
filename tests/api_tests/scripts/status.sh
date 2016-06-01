#!/bin/sh
#****************************************************************************
#* status.sh
#*
#* Checks the run status of the test. 
#* - If the test passes, display PASS: <name>
#* - If the test fails, display FAIL: <name> - reason
#****************************************************************************


if test ! -f "model.xml"; then
  echo "FAILED: $1 - no model.xml"
  exit 0
fi

#if test ! -f "model2.xml"; then
#  echo "FAILED: $1 - no model2.xml"
#  exit 0
#fi

#diff model.xml model2.xml > model_xml.diff
#diff_l=`cat model_xml.diff | wc -l`

#if test $diff_l -eq 0; then
#  rm -f model_xml.diff
#else
#  echo "FAILED: $1 - differences in model.xml"
#fi

# Check against the reference file
if test -f ${SIM_DIR}/tests/${1}.xml; then
  diff ${SIM_DIR}/tests/${1}.xml model.xml > model_ref.diff
  diff_l=`cat model_ref.diff | wc -l`
  
  if test $diff_l -eq 0; then
    rm -f model_ref.diff
  else
    echo "FAILED: $s - differences against reference file"
  fi
fi

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
