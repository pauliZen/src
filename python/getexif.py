from PIL import Image
from PIL.ExifTags import TAGS

import numpy as np
 
def get_exif(fn):
    ret = {}
    i = Image.open(fn)
    info = i._getexif()
    for tag, value in info.items():
        decoded = TAGS.get(tag, tag)
        ret[decoded] = value
    return ret

fl = open('image.lst','r')
path = fl.read()
path = path.splitlines()

print "FILE FocalLength[mm] Aperture Exposure[s] ISO Date Lens"
for j in path:
    data=get_exif(j)
    print j,(data['FocalLength'][0]/data['FocalLength'][1]),data['ExposureTime'][0]/(data['ExposureTime'][1]+0.0), data['ISOSpeedRatings'],data['DateTime'],
    if('ApertureValue' in data.keys()):
        print data['ApertureValue'][0]/(data['ApertureValue'][1]+0.0),
    if(42036 in data.keys()):
        print data[42036]
    else:
        print
