# https://leetcode.com/problems/transpose-file/

awk '{for(fn=1;fn<=NF;fn++) a[fn][length(a[fn])+1] = $fn} END {for(i=1;i<=length(a);++i) { if(length(a[i])>0) printf("%s", a[i][1]); for(j=2;j<=length(a[i]);++j) printf(" %s",a[i][j]); printf("\n"); } }' file.txt
