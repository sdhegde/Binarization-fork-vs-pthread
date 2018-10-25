#!/bin/bash

for i in {0..50}
do
  src="./test_0.jpg"
  dst="./test_"$i".jpg"
  cp "${src}" "${dst}"
done
