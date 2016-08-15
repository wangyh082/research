* Initial Temperature automatically selected
InitTemp -1
* on the basis on TrialRunLength=100 steps
TrialRunLength 100
* with AcceptanceThreshold=0.6
AcceptanceThreshold 0.6
* 1500000 iterations
TotalIter 15000000
* 2 Iterations at fixet temperature
IterAtT 2
* Start from random solution
InitNC
* Loading file
Open PH1S8T02.fpm
* Initialization
InitSA
* Start searching
Start
* Results in results.txt
OutFile SH1S8T02.txt
