#!/bin/bash
mate-terminal -e "/bin/bash -c 'ffmpeg -i videoReporte.mjpeg -r 25 -pix_fmt yuv420p -strict -2 -acodec aac -b:a 128k -vcodec libx264 -crf 21 -rc-lookahead 250 videoReporte.mp4; ./ncambia; rm id_video.txt; rm videoReporte.mjpeg; exit; exec /bin/bash'; &"