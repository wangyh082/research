* Initial Temperature automatically selected
InitTemp -1
* on the basis on TrialRunLength=100 steps
TrialRunLength 100
* with AcceptanceThreshold=0.6
AcceptanceThreshold 0.6
* 100000 iterations
TotalIter 32000000
* 2 Iterations at fixet temperature
IterAtT 2
* Start from random solution
InitNC
* Loading file
Open P50S8T10.fpm
* Initialization
InitSA
* Start searching
Start
* Results in results.txt
OutFile S50S8T10.txt
