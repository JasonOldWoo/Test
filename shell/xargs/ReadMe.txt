find ./ -maxdepth 1 -name "WTF*" -print0 | xargs -0 -I file 'bash -c echo "what the fxxk?" > file'
