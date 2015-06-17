ls sbave.*V|sed -e 's/sbave.//' -e 's/.V//'|sort -n|awk '{printf "sbave.%s.V %d\n",$1,$1*0.54381+0.5}' >sblst.V
ls colorave.*|sed -e 's/colorave.//'|sort -n|awk '{printf "colorave.%s %d\n",$1,$1*0.54381+0.5}' >sbclst
