* Initial Temperature automatically selected
InitTemp -1
* on the basis on TrialRunLength=100 steps
TrialRunLength 100
* with AcceptanceThreshold=0.6
AcceptanceThreshold 0.6
* 100000 iterations
TotalIter 40000000
* 2 Iterations at fixet temperature
IterAtT 2
* Start from random solution
InitNC
* Loading file
Open P20S8T01.fpm
* Initialization
InitSA
* Start searching
Start
* Results in results.txt
OutFile S20S8T01.txt