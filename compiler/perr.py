#!/usr/bin/env python3

import fileinput

for line in fileinput.input():
  line = line.strip()
  if line.startswith('Err!'):
    _, fileName, pos, message = line.split('!')
    pos = int(pos)
    linenum = 1
    with open(fileName, 'r') as f:
      contents = f.read()
      for i in range(pos):
        if contents[i] == '\n':
          linenum += 1
    print('%s:%d:%s' % (fileName, linenum, message))
