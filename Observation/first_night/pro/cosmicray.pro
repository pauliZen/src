pro cosmicray

image = readfits('dU021m065odfse.fit')
image2 = readfits('dU021m083odfse.fit')
;image_c = sigma_filter(image,4,N_sigma=3,/ALL,/MON)
for i = 0,4095 do begin
   for j = 0,4095 do begin
      detla= (image[j,i]-image2[j,i]) / max([image[j,i],image2[j,i])
      if (delta gt 0.5) then begin
         
      endif
   endfor
endfor

writefits, 'dU021m065odfser.fit', image_c

end
