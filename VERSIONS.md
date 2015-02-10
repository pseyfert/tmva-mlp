initial (0)
-----------

ef2d420226136ad6c761225a91e6912d0cd26240
the MLP.class.C as it comes out of TMVA

version 1
---------

552b5fed487235e09c320505246eb6a1345e0a70
switch to float

version 2
---------

fa67edfc70ea29b0ff52e5709535f9ebd25ee645
remove fLayerSize and hard code it (anyhow hard coded for array sizes)

remove loop in line 907
  for (int o=0; o<fLayerSize[2]; o++)
  because fLayerSize[2] == 1

remove loop in line 889
  layer zero is anyhow overwritten by the input values in line 896
  output layer is a single value

remove loop in line 892
  there are exactly two offset weights, hard code them
  move the offset weight of the input layer to the other assignments of the input layer (may help due to memory layout?)

version 3
---------

c48976a321cac637e9568a9e84f6812bf6807b7b
remove fTypes

version 4
---------

26ee130b4fa9195b26fd04fbaff50af32734a481
enabled auto vectorisation at compiler options
split up loop in line 885 into two loops, the first of which can be run in parallel

version 5
---------

8c77f13af60bbdba2cb54d4089c02e5793cc753a
vectorise loop at line 880 similarly

version 6
---------

b79c4c927342d276119dbad77d02c1e4697b768e
replaced output layer activation function

version 7
---------

8bade7cbfb9a20896479e2a2e906679ee82d3951
removed usage of fWeights[0]
additional offset weight in input vector required (does not undergo transformation)
fWeights[1][26] is not set to 0.f prior to setting it to 1.f
and set fWeights[1][26] only once to 1.f
NB: ActivationFnc is not applied to fWeights[1][26]

version 8
---------

f17245bc42c4ca0b0e646bb890dfd3fc1a39ffb2
compute variable transformation scale at initialisation, not once per evaluation
do not instantiate get/put matrix once per evaluation
avoid get/put matrix at all

version 9
---------

7f925a983931cbecde928c678e1999002579b3c9
hard code conditional branches in data GetMvaValue (wrapper for GetMvaValue__)
do input variable transformation in place, instead of copying the data around

version 10
----------

added some SSE by hand

version 11
----------

inline ActivationFnc(s)

version 12
----------

SIMD for output layer and activation function

version 13
----------

use SIMD also for input variable transformation (except for edge)
