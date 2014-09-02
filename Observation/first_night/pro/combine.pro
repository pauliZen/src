pro combine

image = make_array(4096,4096,3,/double)

image[*,*,0] = readfits('dU021m065odfse.fit')
image[*,*,1] = readfits('dU021m083odfse.fit')

for i = 0,4095 do begin
   for j = 0,4095 do begin
;      if (abs([image[j,i,0]-image[j,i,1])/max([image[j,i,0],image[j,i,1])
;      image[j,i,2] = mean([image[j,i,1],image[j,i,0]])
      image[j,i,2]=min([image[j,i,0],image[j,i,1]])
  endfor
endfor

writefits, 'combine.fits', image[*,*,2]

end
