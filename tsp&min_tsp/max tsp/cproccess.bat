echo off
set /A a =1
set /A ALLLINE = 15
set /A RealAllLine = %ALLLINE%+1

echo blasting...
:loop
	easy.py WAAC_PSSM_train.txt
	easy.py EBGW_PSSM_train.txt
:end
echo blasting end successfully

pause