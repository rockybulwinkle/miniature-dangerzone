#!/usr/bin/env python2
import random
f = open("random.net", "w")
layer_format=[32, 1024, 10240, 32]
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
	
