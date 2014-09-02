tput civis; cline=`tput lines`; while true; do tput cup $( $cline - 1 ) 0; date; sleep 2; done

