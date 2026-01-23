# Purpose

This python environment extracts the Mnist dataset from the `tensorflow_datasets` python package.

## how is this Python environment used?
- This directory contains a python script that outputs training and test matrices in ./output directory.
- the C framework will use the files that are in the /output directory, to to train and test the ML model.

## structure of the matrices generated
- the images in the mnist dataset are 28 x 28 pixel grayscale hand drawn digits (0 to 9)
- each row in the matrix is 28*28 = 784 units. each unit is a Byte. i.e, we can have 0 to 255 pixel intensity.

- training dataset -> 60K rows
- test dataset -> 10K rows
