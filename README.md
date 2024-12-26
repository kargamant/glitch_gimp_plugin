# glitch_gimp_plugin

A plugin for GIMP to apply glitch effect to images.  
Works by creating random noise regions with color inversion, shifting or corrupting color data.  
![2024-12-2617-45-15-ezgif com-video-to-gif-converter](https://github.com/user-attachments/assets/c01da961-0ffd-40c6-a121-5921a09e611b)

## Examples  
![](examples/AstonMartin.jpg)

->

![](processed_examples/AstonMartin_glitch.jpg)

![](examples/CyberPunk.jpg)

->

![](processed_examples/CyberPunk_glitch.jpg)

![](examples/eveningNY.jpg)

->

![](processed_examples/eveningNY_glitch.jpg)

![](examples/japan_street.jpg)

->

![](processed_examples/japan_street_glitch.jpg)  

## How to build this plug-in from source?  
1. Replace ```your_gimp_path``` variable value in Makefile with directory name where gimp is installed on your linux machine.
```
your_gimp_path = /home/kargamant/.config/GIMP/2.10
all:
	mkdir -p $(your_gimp_path)/plug-ins/glitch
	gcc  -pthread -I/usr/include/gegl-0.4 -I/usr/include/gio-unix-2.0 -I/usr/include/json-glib-1.0 -I/usr/include/babl-0.1 -I/usr/include/gtk-2.0 -I/usr/lib/x86_64-linux-gnu/gtk-2.0/include -I/usr/include/pango-1.0 -I/usr/include/atk-1.0 -I/usr/include/gdk-pixbuf-2.0 -I/usr/include/libmount -I/usr/include/blkid -I/usr/include/pango-1.0 -I/usr/include/fribidi -I/usr/include/cairo -I/usr/include/pixman-1 -I/usr/include/harfbuzz -I/usr/include/glib-2.0 -I/usr/lib/x86_64-linux-gnu/glib-2.0/include -I/usr/include/uuid -I/usr/include/freetype2 -I/usr/include/libpng16 -I/usr/include/gimp-2.0 -o '$(your_gimp_path)/plug-ins/glitch/glitch' 'glitch.c' 'utils.c' 'widget.c' -lgimpui-2.0 -lgimpwidgets-2.0 -lgimpmodule-2.0 -lgimp-2.0 -lgimpmath-2.0 -lgimpconfig-2.0 -lgimpcolor-2.0 -lgimpbase-2.0 -lgegl-0.4 -lgegl-npd-0.4 -lm -Wl,--export-dynamic -lgmodule-2.0 -pthread -ljson-glib-1.0 -lbabl-0.1 -lgtk-x11-2.0 -lgdk-x11-2.0 -lpangocairo-1.0 -latk-1.0 -lcairo -lgdk_pixbuf-2.0 -lgio-2.0 -lpangoft2-1.0 -lpango-1.0 -lgobject-2.0 -lglib-2.0 -lharfbuzz -lfontconfig -lfreetype -w
```  
 
3. Built plugin will appear at ```Filters > MyFilters > glitch``` . Have fun :) 

