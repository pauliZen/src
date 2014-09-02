#!/bin/bash

#####################################################################################
#                                                                                   #
#  Script for generating snapshot files from NBODY6 stellar evolution output files  #
#  - fort.83  (NBODY6, NBODY6GPU)                                                   #
#  - sev.83   (NBODY6++, NBODY6++GPU)                                               #
#                                                                                   #
#                                                                                   #
#  C. Olczak, 2013-03-07                                                            #
#                                                                                   #
#####################################################################################


# Build file list.
output_file=`find . -maxdepth 1 -regex '\.\/[a-z]+\.83' | cut -c 3-`

# Count list size.
number_of_output_files=`echo $output_file | sed 's/ /\r\n/g' | grep -c 83`

# Make sure list contains only one single file.
if [[ ${number_of_output_files} == 0 ]]
then
    echo
    echo ERROR: there is no file to process.
    echo
    echo Make sure a file \"*.83\" is present.
    echo
    exit
elif [[ ${number_of_output_files} > 1 ]]
then
    echo
    echo ERROR: there are multiple files to process.
    echo 
    echo File list content:
    echo ${output_file} | sed 's/ /\r\n/g'
    echo
    echo Make sure there is only one such file.
    echo
    exit
fi


# Get output file prefix.
output_file__prefix=`echo ${output_file} | cut -d"." -f1`


# Run awk script to split file into snapshots.
echo
echo Generating snapshots from file \"${output_file}\"...

awk -v file_prefix=${output_file__prefix} \
'BEGIN { \
    # Initialize snapshot counter.
    snapshot_counter = -1; \
}; \
{ \
    # Check for new data block (snapshot) and read time from header. \
    # Header has two (old format) or four fields (new format). \
    if ( NF == 2 || NF == 4 ) \
    { \
	# Time is given by last field. \
	time_step = $NF; \
        \
        # Increase snapshot counter.
        snapshot_counter++
        \
	# Build filename with appended snapshot time. \
	file_name = sprintf( "%s%s%4.4d", file_prefix, ".83_", snapshot_counter ); \
        \
	# Inform user about current input and output file. \
	printf ( "%s   ->   %s\n", FILENAME, file_name ); \
        \
	# Write time of given snapshot to corresponding file. \
	print $NF >> file_name; \
    } \
    else \
    { \
	# Write data of given snapshot to corresponding file. \
	print $0 >> file_name; \
    } \
}' \
${output_file}

echo ...done.
echo