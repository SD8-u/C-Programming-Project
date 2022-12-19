#!/bin/sh
#
#
#
make clean
make all
#Test Script for all modules
##PGM ECHO TEST (binary)##
printf "\n#TEST SCRIPT#\n"
printf "ECHOING bird.pgm to temp.pgm\n"
./pgmEcho pgmFiles/bird.pgm pgmFiles/temp.pgm

printf "\nECHOING temp.pgm to temp2.pgm\n"
./pgmEcho pgmFiles/temp.pgm pgmFiles/temp2.pgm

printf "\nDiffing temp.pgm and temp2.pgm (should be identical - no output)\n"
diff pgmFiles/temp.pgm pgmFiles/temp2.pgm

##PGMCOMP TEST (binary)##
printf "\nCOMPARING temp.pgm and bird.pgm (should be identical)\n"
./pgmComp pgmFiles/temp.pgm pgmFiles/bird.pgm

printf "\nCOMPARING temp.pgm and feep.pgm (should be different)\n"
./pgmComp pgmFiles/temp.pgm pgmFiles/feep.pgm

rm pgmFiles/temp.pgm pgmFiles/temp2.pgm

##PGM B2A TEST##
printf "\nCONVERTING mona_lisaCommented.pgm (binary) to mona_lisaASCII.pgm (ascii)\n"
./pgmb2a pgmFiles/mona_lisaCommented.pgm pgmFiles/mona_lisaASCII.pgm

###test using ascii files

##PGM ECHO TEST (ascii)##
printf "\nECHOING mona_lisaASCII.pgm to temp.pgm\n"
./pgmEcho pgmFiles/mona_lisaASCII.pgm pgmFiles/temp.pgm

##PGM COMP TEST (ascii and binary)
printf "\nCOMPARING temp.pgm and mona_lisaCommented.pgm (should be identical)\n"
./pgmComp pgmFiles/temp.pgm pgmFiles/mona_lisaCommented.pgm

##PGM A2B TEST##
printf "\nCONVERTING feepCommented.pgm to feepBinary.pgm\n"
./pgma2b pgmFiles/feepCommented.pgm pgmFiles/feepBinary.pgm

printf "Diffing feepCommented.pgm and feepBinary.pgm\n"
diff pgmFiles/feepCommented.pgm pgmFiles/feepBinary.pgm

##PGM REDUCE TEST##
printf "\nREDUCING pbmlib.pgm by factor of 4 (divisable factor)\n"
./pgmReduce pgmFiles/pbmlib.pgm 4 pgmFiles/pbmlibReduced.pgm

printf "\nREDUCING feep.pgm by factor of 5 (indivisable factor)\n"
./pgmReduce pgmFiles/feep.pgm 5 pgmFiles/feepReduced.pgm

printf "Diffing feep.pgm and feepReduced.pgm\n"
diff pgmFiles/feep.pgm pgmFiles/feepReduced.pgm

##PGM TILE TEST##
printf "\nTILING feep.pgm to feep_<row>_<column>.pgm by 2 (indivisable factor)\n"
./pgmTile pgmFiles/feep.pgm 2 "pgmFiles/feep_<row>_<column>.pgm"

printf "\nTILING bird.pgm to b_<row>_<column>.pgm by 2 (indivisable factor)\n"
./pgmTile pgmFiles/bird.pgm 2 "pgmFiles/b_<row>_<column>.pgm"

printf "\nTILING pbmlib.pgm to pbmlib_<row>_<column>.pgm by 5 (divisable factor)\n"
./pgmTile pgmFiles/pbmlib.pgm 5 "pgmFiles/pbmlib_<row>_<column>.pgm"

printf "Diffing pbmlib.pgm and pbmlib_1_0.pgm\n"
diff pgmFiles/pbmlib.pgm "pgmFiles/pbmlib_1_0.pgm"

rm pgmFiles/mona_lisaASCII.pgm pgmFiles/temp.pgm pgmFiles/feepBinary.pgm pgmFiles/pbmlibReduced.pgm pgmFiles/feepReduced.pgm
rm pgmFiles/pbmlib_*

##PGM ASSEMBLE TEST##
printf "\nASSEMBLING feep2.pgm from tiled feep.pgm\n"
./pgmAssemble pgmFiles/feep2.pgm 24 7 0 0 pgmFiles/feep_0_0.pgm 0 12 pgmFiles/feep_0_1.pgm 4 0 pgmFiles/feep_1_0.pgm 4 12 pgmFiles/feep_1_1.pgm

printf "\nCOMPARING feep.pgm with feep2.pgm (should be identical)\n"
./pgmComp pgmFiles/feep2.pgm pgmFiles/feep.pgm

printf "\nASSEMBLING bird2.pgm from tiled bird.pgm\n"
./pgmAssemble pgmFiles/bird2.pgm 321 481 0 0 pgmFiles/b_0_0.pgm 0 161 pgmFiles/b_0_1.pgm 241 0 pgmFiles/b_1_0.pgm 241 161 pgmFiles/b_1_1.pgm

printf "\nCOMPARING bird.pgm with bird2.pgm (should be identical)\n"
./pgmComp pgmFiles/bird2.pgm pgmFiles/bird.pgm

rm pgmFiles/feep_*
rm pgmFiles/b_*
rm pgmFiles/bird2.pgm
rm pgmFiles/feep2.pgm

#Testing with no arguments
printf "\nAttempting to run with no arguments\n"
printf "pgmEcho:     "
./pgmEcho
printf "pgmComp:     "
./pgmComp
printf "pgmA2b:      "
./pgma2b
printf "pgmB2a:      "
./pgmb2a
printf "pgmReduce:   "
./pgmReduce
printf "pgmTile:     "
./pgmTile
printf "pgmAssemble: "
./pgmAssemble

#Testing bad argument count
printf "\nAttempting to use the wrong argument number\n"
printf "pgmEcho:     "
./pgmEcho pgmFiles/bad.pgm
printf "pgmComp:     "
./pgmComp pgmFiles/bad.pgm
printf "pgmA2b:      "
./pgma2b pgmFiles/bad.pgm
printf "pgmB2a:      "
./pgmb2a pgmFiles/bad.pgm
printf "pgmReduce:   "
./pgmReduce 2 pgmFiles/bad.pgm
printf "pgmTile:     "
./pgmTile  2 "pgmFiles/bad_<row>_<column>.pgm"
printf "pgmAssemble: "
./pgmAssemble pgmFiles/feep2.pgm 24 7 0 0 pgmFiles/feep_0_0.pgm 0 12 pgmFiles/feep_0_1.pgm 4

#Testing an invalid file name
printf "\nAttempting to read an invalid file name\n"
printf "pgmEcho:     "  
./pgmEcho pgmFiles/doesnotexist.pgm pgmFiles/bad.pgm
printf "pgmComp:     "  
./pgmComp pgmFiles/doesnotexist.pgm pgmFiles/bad.pgm
printf "pgmA2b:      "  
./pgma2b pgmFiles/doesnotexist.pgm pgmFiles/bad.pgm
printf "pgmB2a:      "  
./pgmb2a pgmFiles/doesnotexist.pgm pgmFiles/bad.pgm
printf "pgmReduce:   "  
./pgmReduce pgmFiles/doesnotexist.pgm 2 pgmFiles/bad.pgm
printf "pgmTile:     "  
./pgmTile pgmFiles/doesnotexist.pgm 2 "pgmFiles/bad_<row>_<column>.pgm"
printf "pgmAssemble: "  
./pgmAssemble pgmFiles/bad.pgm 3 3 0 0 pgmFiles/doesnotexist.pgm

#Testing bad magic number
printf "\nAttempting to read file with bad magic number\n"
printf "pgmEcho:     "
./pgmEcho pgmFiles/birdBadMagicNumber.pgm pgmFiles/bad.pgm
printf "pgmComp:     "
./pgmComp pgmFiles/birdBadMagicNumber.pgm pgmFiles/bad.pgm
printf "pgmA2b:      "
./pgma2b pgmFiles/birdBadMagicNumber.pgm pgmFiles/bad.pgm
printf "pgmB2a:      "
./pgmb2a pgmFiles/birdBadMagicNumber.pgm pgmFiles/bad.pgm
printf "pgmReduce:   "
./pgmReduce pgmFiles/birdBadMagicNumber.pgm 2 pgmFiles/bad.pgm
printf "pgmTile:     "
./pgmTile pgmFiles/birdBadMagicNumber.pgm 2 "pgmFiles/bad_<row>_<column>.pgm"
printf "pgmAssemble: "
./pgmAssemble pgmFiles/bad.pgm 3 3 0 0 pgmFiles/birdBadMagicNumber.pgm

#Testing bad dimensions
printf "\nAttempting to read file with bad dimensions\n"
printf "pgmEcho:     "
./pgmEcho pgmFiles/pbmlibBadDimensions.pgm pgmFiles/bad.pgm
printf "pgmComp:     "
./pgmComp pgmFiles/pbmlibBadDimensions.pgm pgmFiles/bad.pgm
printf "pgmA2b:      "
./pgma2b pgmFiles/pbmlibBadDimensions.pgm pgmFiles/bad.pgm
printf "pgmB2a:      "
./pgmb2a pgmFiles/pbmlibBadDimensions.pgm pgmFiles/bad.pgm
printf "pgmReduce:   "
./pgmReduce pgmFiles/pbmlibBadDimensions.pgm 5 pgmFiles/bad.pgm
printf "pgmTile:     "
./pgmTile pgmFiles/pbmlibBadDimensions.pgm 2 "pgmFiles/bad_<row>_<column>.pgm"
printf "pgmAssemble: "
./pgmAssemble pgmFiles/bad.pgm 3 3 0 0 pgmFiles/pbmlibBadDimensions.pgm

#Testing bad max grey value
printf "\nAttempting to read file with bad max grey value\n"
printf "pgmEcho:     "
./pgmEcho pgmFiles/mona_lisaBadMaxGrey.pgm pgmFiles/bad.pgm
printf "pgmComp:     "
./pgmComp pgmFiles/mona_lisaBadMaxGrey.pgm pgmFiles/bad.pgm
printf "pgmA2b:      "
./pgma2b pgmFiles/mona_lisaBadMaxGrey.pgm pgmFiles/bad.pgm
printf "pgmB2a:      "
./pgmb2a pgmFiles/mona_lisaBadMaxGrey.pgm pgmFiles/bad.pgm
printf "pgmReduce:   "
./pgmReduce pgmFiles/mona_lisaBadMaxGrey.pgm 5 pgmFiles/bad.pgm
printf "pgmTile:     "
./pgmTile pgmFiles/mona_lisaBadMaxGrey.pgm 2 "pgmFiles/bad_<row>_<column>.pgm"
printf "pgmAssemble: "
./pgmAssemble pgmFiles/bad.pgm 3 3 0 0 pgmFiles/mona_lisaBadMaxGrey.pgm

#Testing Bad Data
printf "\nAttempting to read file with bad data\n"
printf "pgmEcho:     "
./pgmEcho pgmFiles/feepBadData.pgm pgmFiles/bad.pgm
printf "pgmComp:     "
./pgmComp pgmFiles/feepBadData.pgm pgmFiles/bad.pgm
printf "pgmA2b:      "
./pgma2b pgmFiles/feepBadData.pgm pgmFiles/bad.pgm
printf "pgmB2a:      "
./pgmb2a pgmFiles/feepBadData.pgm pgmFiles/bad.pgm
printf "pgmReduce:   "
./pgmReduce pgmFiles/feepBadData.pgm 5 pgmFiles/bad.pgm
printf "pgmTile:     "
./pgmTile pgmFiles/feepBadData.pgm 2 "pgmFiles/bad_<row>_<column>.pgm"
printf "pgmAssemble: "
./pgmAssemble pgmFiles/bad.pgm 3 3 0 0 pgmFiles/feepBadData.pgm

#Testing too much data
printf "\nAttempting to echo file with too much data\n"
printf "pgmEcho:     "
./pgmEcho pgmFiles/pbmlibMoreData.pgm pgmFiles/bad.pgm
printf "pgmComp:     "
./pgmComp pgmFiles/pbmlibMoreData.pgm pgmFiles/bad.pgm
printf "pgmA2b:      "
./pgma2b pgmFiles/pbmlibMoreData.pgm pgmFiles/bad.pgm
printf "pgmB2a:      "
./pgmb2a pgmFiles/pbmlibMoreData.pgm pgmFiles/bad.pgm
printf "pgmReduce:   "
./pgmReduce pgmFiles/pbmlibMoreData.pgm 5 pgmFiles/bad.pgm
printf "pgmTile:     "
./pgmTile pgmFiles/pbmlibMoreData.pgm 2 "pgmFiles/bad_<row>_<column>.pgm"
printf "pgmAssemble: "
./pgmAssemble pgmFiles/bad.pgm 3 3 0 0 pgmFiles/pbmlibMoreData.pgm

#Testing too little data
printf "\nAttempting to echo file with too little data\n"
printf "pgmEcho:     "
./pgmEcho pgmFiles/mona_lisaLittleData.pgm pgmFiles/bad.pgm
printf "pgmComp:     "
./pgmComp pgmFiles/mona_lisaLittleData.pgm pgmFiles/bad.pgm
printf "pgmA2b:      "
./pgma2b pgmFiles/mona_lisaLittleData.pgm pgmFiles/bad.pgm
printf "pgmB2a:      "
./pgmb2a pgmFiles/mona_lisaLittleData.pgm pgmFiles/bad.pgm
printf "pgmReduce:   "
./pgmReduce pgmFiles/mona_lisaLittleData.pgm 5 pgmFiles/bad.pgm
printf "pgmTile:     "
./pgmTile pgmFiles/mona_lisaLittleData.pgm 2 "pgmFiles/bad_<row>_<column>.pgm"
printf "pgmAssemble: "
./pgmAssemble pgmFiles/bad.pgm 3 3 0 0 pgmFiles/mona_lisaLittleData.pgm

#Testing with wrong integer type
printf "\nAttempting to input string for integer factor\n"
printf "pgmReduce:   "
./pgmReduce pgmFiles/feep.pgm NOTANINTEGER pgmFiles/bad.pgm
printf "pgmTile:     "
./pgmTile pgmFiles/mona_lisaLittleData.pgm NOTANINTEGER "pgmFiles/bad_<row>_<column>.pgm"
printf "pgmAssemble: "
./pgmAssemble pgmFiles/feep2.pgm 3 NOTANINTEGER 0 0 pgmFiles/feep.pgm

#Testing bad template in TILE
printf "\nAttempting to use a bad template file name\n"
./pgmTile pgmFiles/feep.pgm 2 "pgmFiles/feep_<rw>_<colu>.pgm"

#Testing bad comment
printf "\nAttempting to read a file with bad comment\n"
printf "pgmEcho:     "
./pgmEcho pgmFiles/badComment.pgm pgmFiles/bad.pgm
printf "pgmComp:     "
./pgmComp pgmFiles/badComment.pgm pgmFiles/bad.pgm
printf "pgmA2b:      "
./pgma2b pgmFiles/badComment.pgm pgmFiles/bad.pgm
printf "pgmB2a:      "
./pgmb2a pgmFiles/badComment.pgm pgmFiles/bad.pgm
printf "pgmReduce:   "
./pgmReduce pgmFiles/badComment.pgm 5 pgmFiles/bad.pgm
printf "pgmTile:     "
./pgmTile pgmFiles/badComment.pgm 2 "pgmFiles/bad_<row>_<column>.pgm"
printf "pgmAssemble: "
./pgmAssemble pgmFiles/bad.pgm 3 3 0 0 pgmFiles/badComment.pgm
