#!/bin/bash

dates=(
"2025-07-23"
"2025-08-18"
"2025-08-19"
"2025-08-20"
)

for date in "${dates[@]}"
do
  echo "update $date" >> README.md
  
  GIT_AUTHOR_DATE="$date T12:00:00" \
  GIT_COMMITTER_DATE="$date T12:00:00" \
  git add . && git commit -m "commit for $date"
done

git push
