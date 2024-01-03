map relief generator


this repo is an attempt to generate a map using only random values, and the current coordinates of the map, 

in the first approach(without any research about procedural map generation) I will use 3 values, given by the random seeding of the current coordinates * 10 (x*10, y*10 x*y*10), theese 3 values will be summed(with 0.33 of relevance per value) to generate the 0-1 value of an pixel, this is the height, 