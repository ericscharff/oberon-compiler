#!/usr/bin/env python3

import fileinput

for line in fileinput.input():
  line = line.strip()
  if line.startswith('Err!'):
    _, file_name, pos, message = line.split('!')
    pos = int(pos)
    line_num = 1
    with open(file_name, 'r') as f:
      contents = f.read()
      for i in range(pos):
        if contents[i] == '\n':
          line_num += 1
    print(f'{file_name}:{line_num}:{message}')
