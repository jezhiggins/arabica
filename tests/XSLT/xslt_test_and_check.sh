#!/bin/sh

./xslt_test -table > test-run.csv
MISMATCH=`diff test.csv test-run.csv | wc -l `

if [ 0 -eq $MISMATCH ]
then
  exit 0
fi

echo "TEST OUTPUT HAS CHANGED"
diff test.csv test-run.csv
exit 1
