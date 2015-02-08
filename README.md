tmva-mlp
========

learning by doing: speeding up tmva's mlp

Motivation
----------

I took an existing [TMVA] [MLP] class.C file and try to make it's evaluation
faster. The project is thought of being potentially interesting to read, the
network itself will probably not be useful to many people. Copying the changes
may or may not be useful.

The steps are:
 * Avoid exp evaluations
 * convert from double precision to float
 * profile the code with callgrind
 * try using math libraries (e.g. eigen)
 * rearrange computations (evaluation -> instantiation)
 * rearrange code to achieve auto vectorisation
 * reading https://research.google.com/pubs/archive/37631.pdf

why this is not just code you can use directly The work is at the moment very
specific to my existing network. This does not use a decorrelation
transformation, which may change the picture. I used my private simple sigmoid
activation function in the hidden layer in the training [ROOT-7062]. As it
turns out, I failed to replace the output layer activation function (cross
entropy estimator in back propagation needs the standard sigmoid in the
training) but since i'm fine with monotoneous transformations of the evaluated
network output, I replaced the output layer activation function after the
training.

The actual profiles of the test case reveal that the test spends many cycles on
i/o and ROOT overhead.  Since in a real use scenario, the data will either come
from different sources or the i/o will anyhow be unavoidable, I still
concentrate on speeding up the MLP.

Warnings
--------

To avoid copying data around, I changed the interface such that the input data
is altered! Eventually, also the offset needs to be supplied in some versions
by the user.

License
-------

The code is released under the [GNU Lesser General Public License, version
2.1][LGPL], the license under which [ROOT] itself is provided.

Machine info
------------

The profiles were generated on an AMD Opteron(tm) Processor 6344.
The tools in use are:
gcc 4.8.1
ROOT 6.03/02
valgrind 3.8.1

[ROOT-7062]: https://sft.its.cern.ch/jira/browse/ROOT-7062
[TMVA]:      http://tmva.sourceforge.net/
[MLP]:       http://en.wikipedia.org/wiki/Multilayer_perceptron
[LGPL]:      https://gnu.org/licenses/old-licenses/lgpl-2.1
[ROOT]:      http://root.cern.ch
