#!/usr/bin/env python2

f = open("random.net", "w")
layer_format=[1, 2000, 1000, 1]
f.write("%d\n"%(len(layer_format)))
f.write(" ".join(map(str,layer_format)))
f.write("\n\n")

layer = 1
while layer < len(layer_format):
	for node in range(layer_format[layer]):
		for weight in range(layer_format[layer-1]):
			f.write("0.000\t")
		f.write("\n0\n")
	f.write("\n")
	layer+=1
	
