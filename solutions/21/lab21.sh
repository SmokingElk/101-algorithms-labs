#!/bin/bash

prefix="new_"
suffix=".txt"

for file in *"$suffix"; do
  if [[ -f "$file" ]]; then
    mv "$file" "${prefix}${file}"
  fi
done
