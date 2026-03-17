for i in {1..30}
do
  DATE=$(date -d "2025-08-01 +$i days" +"%Y-%m-%d")
  echo "auto $DATE" >> README.md

  GIT_AUTHOR_DATE="$DATE T12:00:00" \
  GIT_COMMITTER_DATE="$DATE T12:00:00" \
  git add . && git commit -m "auto commit $DATE"
done

git push