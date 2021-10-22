## The script to split HEPevt file into smaller files with 50 events per file
## and then generating file list (both in full path, and in relative path with smaller batches) under the same output directoty
## written by Guanqun

#!/bin/bash

CurrentDir=$PWD

# the directory where large HEPevt text file sits
LargeFilePath="/uboone/data/users/gge/SinglePhotonAnalysis/CoherentPhotonSample/COHGAMMA/numu_uBooNE_Flux/500k"
FileName="gntp_HEPevt_*.txt"

## the directory where HEPevt text file with smaller size will sit
OutputFilePath="/pnfs/uboone/resilient/users/gge/work/coherent_Sept2021/HEPevtfile_list/numu_uBooNE_Flux_500k"
SmallFileSubDir="splited_file_50evts"
mkdir -p $OutputFilePath"/"$SmallFileSubDir

## ======= loop over each large HEPevt file, and split it into smaller files and save to output directory
cd $LargeFilePath
for file in $FileName; do
    echo $file
    split -l 150 $file $OutputFilePath"/"$SmallFileSubDir"/"$file 
done


## generate a filelist with full path --> used for simulating events with no overlay
ls $OutputFilePath"/"$SmallFileSubDir"/"* > $OutputFilePath"/"gntp_HEPevt_all_splited_file.list 


## ======= generate filelist in smaller batches and zip the whole folder ============
##  --> used for simulating events with overlays
## each filelist contain relative path to smaller HEPevt files splited from a certain larger HEPevt file

cd $OutputFilePath
OutputDirName=$(basename $OutputFilePath)  # name of the directory, used for zip command
cd ../
for file in $LargeFilePath"/"$FileName;do

   ## remove the path infront and suffix
   base_name=$(basename -s .txt $file)
   ls $OutputDirName"/"$SmallFileSubDir"/"$base_name* > $OutputDirName"/"$base_name"_splited_file.list"
done

## unzip command is not available on grid node
## use tar instead
#zip -r $OutputDirName".zip" $OutputDirName
tar -cvf $OutputDirName".tar" $OutputDirName 

## =======  end of generating filelist in smaller batches and zipping the whole folder ================


## go back to current dir
cd $CurrentDir
