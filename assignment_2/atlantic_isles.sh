#Produces atlantic isles using gtopo utilities and gtopo print land#
#(Not exactly the same as sample output but as close as I could get)#
./gtopoReduce /vol/scratch/SoC/COMP1921/GTOPO30/gt30w020n90_dem/gt30w020n90.dem 4800 6000 20 model.dem
./gtopoTile model.dem 240 300 20 "tile_<row>_<column>.dem"
./gtopoAssemble atlantic_isles.dem 72 75 0 0 tile_12_5.dem 12 15 0 12 tile_12_6.dem 12 15 0 24 tile_12_7.dem 12 15 0 36 tile_12_8.dem 12 15 0 48 tile_12_9.dem 12 15 0 60 tile_12_10.dem 12 15 15 0 tile_13_5.dem 12 15 15 12 tile_13_6.dem 12 15 15 24 tile_13_7.dem 12 15 15 36 tile_13_8.dem 12 15 15 48 tile_13_9.dem 12 15 15 60 tile_13_10.dem 12 15 30 0 tile_14_5.dem 12 15 30 12 tile_14_6.dem 12 15 30 24 tile_14_7.dem 12 15 30 36 tile_14_8.dem 12 15 30 48 tile_14_9.dem 12 15 30 60 tile_14_10.dem 12 15 45 0 tile_15_5.dem 12 15 45 12 tile_15_6.dem 12 15 45 24 tile_15_7.dem 12 15 45 36 tile_15_8.dem 12 15 45 48 tile_15_9.dem 12 15 45 60 tile_15_10.dem 12 15 60 0 tile_16_5.dem 12 15 60 12 tile_16_6.dem 12 15 60 24 tile_16_7.dem 12 15 60 36 tile_16_8.dem 12 15 60 48 tile_16_9.dem 12 15 60 60 tile_16_10.dem 12 15 

./gtopoPrintLand atlantic_isles.dem 72 75 atlantic_isles.txt -9999 100 700

rm atlantic_isles.dem tile_* model.dem
