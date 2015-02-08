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

enabled auto vectorisation at compiler options
split up loop in line 885 into two loops, the first of which can be run in parallel
