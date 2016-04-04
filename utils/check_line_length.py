#!/usr/bin/env python

# Script by Robert Xiao (brx (at) cs.cmu.edu)
# found on StackOverflow : http://stackoverflow.com/a/27490530

import sys

TABSZ = 8
MAXLEN = 80

for fname in sys.argv[1:]:
    f = open(fname, 'r')
    for i, line in enumerate(f):
        if len(line.rstrip('\n').replace('\t', ' '*TABSZ)) > MAXLEN:
            print "%s@%d: line exceeds %d characters" % (fname, i+1, MAXLEN)
    f.close()

# vim: ts=4 sw=4 expandtab
