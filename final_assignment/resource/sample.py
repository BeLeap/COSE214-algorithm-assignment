#!/usr/bin/python3

f = open("./words.txt", 'r')
lst = []
for i in range(0, 4000000):
    f.readline()
    if i % 100000 == 0:
        lst.append(f.readline())

f = open("./test.txt", 'w')
for elem in lst:
    f.write(elem)