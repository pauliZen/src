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

for j in path:
    info=get_exif(j)
    print info
    
