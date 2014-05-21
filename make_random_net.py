#!/usr/bin/env python2
import random
import sys
f = open(sys.argv[-1], "w")
layer_format=map(int, sys.argv[1:-1])
f.write("%d\n"%(len(layer_format)))
f.write(" ".join(map(str,layer_format)))
f.write("\n\n")

layer = 1
while layer < len(layer_format):
	for node in range(layer_format[layer]):
		for weight in range(layer_format[layer-1]):
			f.write("%f\t"%random.random())
		f.write("\n0\n")
	f.write("\n")
	layer+=1
	
