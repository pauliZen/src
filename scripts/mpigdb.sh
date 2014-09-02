#!/bin/bash
if [ "$PMI_RANK" == "0" ]; then
    exec gdb --annotate=3 $*
else
    xterm -sb -rightbar -e "bash -c \"gdb $*<<EOF
run
EOF\""
fi
exit 0
