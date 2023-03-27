unset colorbox
unset key
unset border
unset tics

set tmargin at screen 0.9
set bmargin at screen 0.25
set lmargin at screen 0.15
set rmargin at screen 0.85

# set hidden3d
set isosamples 20
set samples 20
set pm3d hidden3d

set xrange[-1:1]
set yrange[-1:1]
set zrange[0:1]

f(x) = 0.5 * exp(-16.0 * x**2)
g(x,y) = f(x**2 + y**2)
splot g(x,y) with pm3d fillcolor "#f8f8f8"
