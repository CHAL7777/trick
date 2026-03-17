#!/bin/bash

# List your 13 dates here (YYYY-MM-DD)
dates=(
"2025-07-23"
"2025-08-01"
"2025-08-02"
"2025-08-03"
"2025-08-04"
"2025-08-05"
"2025-08-10"
"2025-08-12"
"2025-08-15"
"2025-08-18"
"2025-08-20"
"2025-08-22"
"2025-08-25"
)

for date in "${dates[@]}"
do
  # Add a small change
  echo "update for $date" >> README.md
  
  # Backdate commit
  GIT_AUTHOR_DATE="${date}T12:00:00" \
  GIT_COMMITTER_DATE="${date}T12:00:00" \
  git add . && git commit -m "commit for $date"
done

# Push all commits at once
git push