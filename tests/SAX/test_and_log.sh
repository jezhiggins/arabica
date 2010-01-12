#!/bin/sh

for x in filter_test filter_test_silly filter_test_wide
do
  ./$x -xml -log ../$x
done
