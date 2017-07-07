# comparisonOfProtonRangeModels
Code for the comparison of the proton range using different parameterization models. Used for my Radiation Physics and Chemstry publication.

First load the findRangeEquation.C in ROOT:

[ROOT] .L findRangeEquation.C+

and run the program by specifing the inverse number of datapoints to use (1 runs all, 2 runs 50%, etc.)

[ROOT] Run(2)

Then the output is stored in MedianValuesForComparison.csv.
Run the python script computeAverageValueForCSV.py to merge all lines with the same number of datapoints (do this anyway, as it is the merged file which is to be plotted)

To make the plot of 75% percentile vs number of datapoints, run

bash $ root makePlots.C

