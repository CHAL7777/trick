#!/bin/bash

# List your 13 dates here (YYYY-MM-DD)
dates=(
"2026-01-29"
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