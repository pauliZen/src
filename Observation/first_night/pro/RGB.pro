pro RGB
RGB = dblarr(1248,1152,3)

RGB[*,*,0] = readfits('l10070078_obf.fits')
RGB[*,*,1] = readfits('l10070079_obf.fits') *1.4
RGB[*,*,2] = readfits('l10070080_obf.fits') / 1.5

prinT, minmax(rgb)

rgb[where(RGB lt 0.)] = 0.
rgb[where(RGB gt 15000.)] = 15000.


RGB = RGB / max(RGB) * 255.


set_plot, 'ps'
device, /encapsulated,file = 'PlanetaryNebulae.eps', /color, bits = 24
tv, RGB, true = 3
device, /close
set_plot, 'X'

stop
end
