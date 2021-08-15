#!/usr/local/bin/python3

f=open("P.cpp","r")

of = open("mont.cpp","w")

list =f.readlines()

needed = [ ] # add here

cur = []
for line in list:
    wline=line.split()
    if len(wline)>=1 and wline[0]=='//#':
        cur = wline
    else:
        ok = False
        for x in needed:
            if cur.count(x) > 0:
                ok=True

        if ok:
            print(line,end='',file=of)