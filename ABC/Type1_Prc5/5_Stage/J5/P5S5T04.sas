* Initial Temperature automatically selected
InitTemp -1
* on the basis on TrialRunLength=100 steps
TrialRunLength 100
* with AcceptanceThreshold=0.6
AcceptanceThreshold 0.6
* 10000 iterations
TotalIter 330000000
* 2 Iterations at fixet temperature
IterAtT 2
* Start from random solution
InitNC
* Loading file
Open P5S5T04.fpm
* Initialization
InitSA
* Start searching
Start
* Results in results.txt
OutFile S5S5T04.txt
