#!/bin/bash

#stdlib
echo "*** This is the current set of standart library functions that are imported at runtime."
echo cat ds.uu
cat ds.uu

#fixed point combinator
echo "*** The following shows that the my pretty printer is a fixed point combinator for valid input."
echo "dpl -pp sample.uu > ppTest.uu"
dpl -pp sample.uu > ppTest.uu
echo "dpl sample.uu > out"
dpl sample.uu > out
echo "dpl ppTest.uu > ppTestOut.uu"
dpl ppTest.uu > ppTestOut.uu
echo "diff out ppTestOut.uu"
diff out ppTestOut.uu
