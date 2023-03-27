unset colorbox
unset key
unset border
unset tics

# set object 1 rectangle from screen 0,0 to screen 1,1 fillcolor rgb "#eeeeee" behind

set tmargin at screen 0.9
set bmargin at screen 0.25
set lmargin at screen 0.15
set rmargin at screen 0.85

# set hidden3d
set isosamples 20

set xrange[-1:1]
set yrange[-1:1]
set zrange[0:1]

splot 0 with pm3d fillcolor "#f8f8f8", 0 lc "black"
