#!/bin/sh
#
#
#
make clean
make all
##GTOPO ECHO TEST##
printf "\n#TEST SCRIPT#\n"
printf "ECHOING W020N40 to model.dem\n"
./gtopoEcho /vol/scratch/SoC/COMP1921/GTOPO30/gt30w020n40_dem/gt30w020n40.dem 4800 6000 model.dem

printf "\nECHOING model.dem to model1.dem\n"
./gtopoEcho model.dem 4800 6000 model1.dem

printf "\nDiffing model.dem and model1.dem (should be identical - no output)\n"
diff model.dem model1.dem

##GTOPO COMP TEST##
printf "\nCOMPARING model1.dem and W020N40 (should be identical)\n"
./gtopoComp /vol/scratch/SoC/COMP1921/GTOPO30/gt30w020n40_dem/gt30w020n40.dem 4800 6000 model1.dem

printf "\nCOMPARING model1.dem and W020N90 (should be different)\n"
./gtopoComp /vol/scratch/SoC/COMP1921/GTOPO30/gt30w020n90_dem/gt30w020n90.dem 4800 6000 model1.dem

rm model.dem model1.dem

#Testing with no arguments
printf "\nGTOPO ECHO with no Arguments\n"
./gtopoEcho
printf "\nGTOPO COMP with no Arguments\n"
./gtopoComp
printf "\nGTOPO PRINTLAND with no Arguments\n"
./gtopoPrintLand
printf "\nGTOPO REDUCE with no Arguments\n"
./gtopoReduce
printf "\nGTOPO TILE with no Arguments\n"
./gtopoTile
printf "\nGTOPO ASSEMBLEREDUCE with no Arguments\n"
./gtopoAssembleReduce

#Testing an invalid file name
printf "\nAttempting to read an invalid file name\n"
./gtopoEcho DOESNOTEXIST.dem 4800 6000 bad.dem

#Testing too much data
printf "\nAttempting to echo file with too much data\n"
./gtopoEcho /vol/scratch/SoC/COMP1921/GTOPO30/gt30e020n40_dem/gt30e020n40.dem 3000 5000 bad.dem

#Testing too little data
printf "\nAttempting to echo file with too little data\n"
./gtopoEcho /vol/scratch/SoC/COMP1921/GTOPO30/gt30e020n40_dem/gt30e020n40.dem 4800 7000 bad.dem

#Testing with wrong integer type
printf "\nAttempting to input string for integer factor\n"
./gtopoReduce /vol/scratch/SoC/COMP1921/GTOPO30/gt30w020n90_dem/gt30w020n90.dem 4800 6000 NOTANINTEGER bad.dem

#Testing bad template in TILE
printf "\nAttempting to use a bad template file name\n"
./gtopoTile /vol/scratch/SoC/COMP1921/GTOPO30/gt30e020n90_dem/gt30e020n90.dem 4800 6000 2 "model_<rw>_<colu>.dem"

##GTOPO REDUCE TEST##
printf "\nTesting GTOPO REDUCE on four tiles of dataset\n"
./gtopoReduce /vol/scratch/SoC/COMP1921/GTOPO30/gt30w100n40_dem/gt30w100n40.dem 4800 6000 32 model1.dem
./gtopoReduce /vol/scratch/SoC/COMP1921/GTOPO30/gt30w060n40_dem/gt30w060n40.dem 4800 6000 32 model2.dem
./gtopoReduce /vol/scratch/SoC/COMP1921/GTOPO30/gt30w100s10_dem/gt30w100s10.dem 4800 6000 32 model3.dem
./gtopoReduce /vol/scratch/SoC/COMP1921/GTOPO30/gt30w060s10_dem/gt30w060s10.dem 4800 6000 32 model4.dem

##GTOPO TILE TEST##
printf "\nGTOPO TILING four reduced tiles of dataset by 2\n"
./gtopoTile model1.dem 150 188 2 "model1_<row>_<column>.dem"
./gtopoTile model2.dem 150 188 2 "model2_<row>_<column>.dem"
./gtopoTile model3.dem 150 188 2 "model3_<row>_<column>.dem"
./gtopoTile model4.dem 150 188 2 "model4_<row>_<column>.dem"

##GTOPO ASSEMBLE TEST##
printf "\nGTOPO ASSEMBLING 6 gtopo tiles\n"
./gtopoAssemble southAmerica.dem 150 282 0 0 model1_1_1.dem 75 94 0 75 model2_1_0.dem 75 94 94 0 model3_0_1.dem 75 94 94 75 model4_0_0.dem 75 94 188 0 model3_1_1.dem 75 94 188 75 model4_1_0.dem 75 94

printf "\nGTOPO REDUCE assembled model\n"
./gtopoReduce southAmerica.dem 150 282 2 southAmericaReduced.dem

rm southAmerica.dem
rm model*  
##GTOPO ASSEMBLE REDUCE TEST##
printf "\nTesting GTOPO ASSEMBLE REDUCE\n"
./gtopoAssembleReduce a.dem      9600   6000   40             0               0               /vol/scratch/SoC/COMP1921/GTOPO30/gt30w180n90_dem/gt30w180n90.dem       4800    6000    0               4800    /vol/scratch/SoC/COMP1921/GTOPO30/gt30w140n90_dem/gt30w140n90.dem 4800 6000

printf "\nTesting GTOPO ASSEMBLE REDUCE on full dataset\n"
./gtopoAssembleReduce   reducedGtopoDataset.dem      43200   21600   400             0               0               /vol/scratch/SoC/COMP1921/GTOPO30/gt30w180n90_dem/gt30w180n90.dem       4800    6000    0               4800    /vol/scratch/SoC/COMP1921/GTOPO30/gt30w140n90_dem/gt30w140n90.dem       4800    6000    0               9600    /vol/scratch/SoC/COMP1921/GTOPO30/gt30w100n90_dem/gt30w100n90.dem       4800    6000    0               14400   /vol/scratch/SoC/COMP1921/GTOPO30/gt30w060n90_dem/gt30w060n90.dem       4800    6000    0               19200   /vol/scratch/SoC/COMP1921/GTOPO30/gt30w020n90_dem/gt30w020n90.dem       4800    6000    0               24000   /vol/scratch/SoC/COMP1921/GTOPO30/gt30e020n90_dem/gt30e020n90.dem       4800    6000    0               28800   /vol/scratch/SoC/COMP1921/GTOPO30/gt30e060n90_dem/gt30e060n90.dem       4800    6000    0               33600   /vol/scratch/SoC/COMP1921/GTOPO30/gt30e100n90_dem/gt30e100n90.dem       4800    6000    0               38400   /vol/scratch/SoC/COMP1921/GTOPO30/gt30e140n90_dem/gt30e140n90.dem       4800    6000    6000    0               /vol/scratch/SoC/COMP1921/GTOPO30/gt30w180n40_dem/gt30w180n40.dem       4800    6000    6000    4800    /vol/scratch/SoC/COMP1921/GTOPO30/gt30w140n40_dem/gt30w140n40.dem       4800    6000    6000    9600    /vol/scratch/SoC/COMP1921/GTOPO30/gt30w100n40_dem/gt30w100n40.dem       4800    6000    6000    14400   /vol/scratch/SoC/COMP1921/GTOPO30/gt30w060n40_dem/gt30w060n40.dem       4800    6000    6000    19200   /vol/scratch/SoC/COMP1921/GTOPO30/gt30w020n40_dem/gt30w020n40.dem       4800    6000    6000    24000   /vol/scratch/SoC/COMP1921/GTOPO30/gt30e020n40_dem/gt30e020n40.dem       4800    6000    6000    28800   /vol/scratch/SoC/COMP1921/GTOPO30/gt30e060n40_dem/gt30e060n40.dem       4800    6000    6000    33600   /vol/scratch/SoC/COMP1921/GTOPO30/gt30e100n40_dem/gt30e100n40.dem       4800    6000    6000    38400   /vol/scratch/SoC/COMP1921/GTOPO30/gt30e140n40_dem/gt30e140n40.dem       4800    6000    12000   0               /vol/scratch/SoC/COMP1921/GTOPO30/gt30w180s10_dem/gt30w180s10.dem       4800    6000    12000   4800    /vol/scratch/SoC/COMP1921/GTOPO30/gt30w140s10_dem/gt30w140s10.dem       4800    6000    12000   9600    /vol/scratch/SoC/COMP1921/GTOPO30/gt30w100s10_dem/gt30w100s10.dem       4800    6000    12000   14400   /vol/scratch/SoC/COMP1921/GTOPO30/gt30w060s10_dem/gt30w060s10.dem       4800    6000    12000   19200   /vol/scratch/SoC/COMP1921/GTOPO30/gt30w020s10_dem/gt30w020s10.dem       4800    6000    12000   24000   /vol/scratch/SoC/COMP1921/GTOPO30/gt30e020s10_dem/gt30e020s10.dem       4800    6000    12000   28800   /vol/scratch/SoC/COMP1921/GTOPO30/gt30e060s10_dem/gt30e060s10.dem       4800    6000    12000   33600   /vol/scratch/SoC/COMP1921/GTOPO30/gt30e100s10_dem/gt30e100s10.dem       4800    6000    12000   38400   /vol/scratch/SoC/COMP1921/GTOPO30/gt30e140s10_dem/gt30e140s10.dem       4800    6000    18000   0               /vol/scratch/SoC/COMP1921/GTOPO30/gt30w180s60_dem/gt30w180s60.dem       7200    3600    18000   7200    /vol/scratch/SoC/COMP1921/GTOPO30/gt30w120s60_dem/gt30w120s60.dem       7200    3600    18000   14400   /vol/scratch/SoC/COMP1921/GTOPO30/gt30w060s60_dem/gt30w060s60.dem       7200    3600    18000   21600   /vol/scratch/SoC/COMP1921/GTOPO30/gt30w000s60_dem/gt30w000s60.dem       7200    3600    18000   28800   /vol/scratch/SoC/COMP1921/GTOPO30/gt30e060s60_dem/gt30e060s60.dem       7200    3600    18000   36000   /vol/scratch/SoC/COMP1921/GTOPO30/gt30e120s60_dem/gt30e120s60.dem       7200    3600

##GTOPO PRINT LAND TEST##
printf "\nPrinting South America from reduced tiles\n"
./gtopoPrintLand southAmericaReduced.dem 75 141 southAmericaPrint.txt -9999 500 4000
cat southAmericaPrint.txt

printf "\nPrinting reduced dataset in ascii\n"
./gtopoPrintLand reducedGtopoDataset.dem 108 54 gtopoDatasetPrint.txt -9999 500 4000
cat gtopoDatasetPrint.txt

rm a.dem
rm southAmericaReduced.dem
rm southAmericaPrint.txt
rm reducedGtopoDataset.dem
rm gtopoDatasetPrint.txt

printf "\nPrinting atlantic isles in ascii\n"
./atlantic_isles.sh
cat atlantic_isles.txt
rm atlantic_isles.txt
