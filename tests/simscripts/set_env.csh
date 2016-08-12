#!/bin/csh

#****************************************************************************
#* simscripts set_env.csh
#****************************************************************************

# Small modification
set rootdir=`pwd`

while ("x$rootdir" != "x")
  set runtest=`find $rootdir -maxdepth 4 -name runtest.pl` 
  if ("x$runtest" != "x") then
    break;
  endif
  set rootdir=`dirname $rootdir`
end


if ("x$runtest" == "x") then
  echo "Error: Failed to find root directory"
else
  set n_runtest=`echo $runtest | wc -w`
if ($n_runtest > 1) then
    echo "Note: found multiple runtest.pl scripts: $runtest"
    foreach rt ($runtest)
      set rt_dir=`dirname $rt`
      set rt_dir=`dirname $rt_dir`
if (-d $rt_dir/mkfiles) then
       echo "Note: selecting $rt"
       set real_rt=$rt
       break
     endif
    end
    set runtest=$real_rt
 endif
   
  if ("x$runtest" == "x") then
    echo "Error: Failed to disambiguate runtest.pl"
  else
    set SIMSCRIPTS_DIR=`dirname $runtest`
    setenv SIMSCRIPTS_DIR `dirname $SIMSCRIPTS_DIR`
    echo "SIMSCRIPTS_DIR=$SIMSCRIPTS_DIR"
    # TODO: check whether the PATH already contains the in directory
    setenv PATH ${SIMSCRIPTS_DIR}:$PATH

    # Environment-specific variables
if (-f $SIMSCRIPTS_DIR/../env/env.sh) then
       . $SIMSCRIPTS_DIR/../env/env.sh
   endif
  endif
endif

