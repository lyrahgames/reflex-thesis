#!/usr/bin/gnuplot
#
# Plot of a Klein bottle
#
# AUTHOR: Hagen Wierstorf

# reset

# wxt
# set terminal wxt size 350,262 enhanced font 'Verdana,10' persist
# png
#set terminal pngcairo size 350,262 enhanced font 'Verdana,10'
#set output 'klein_bottle.png'
# svg
#set terminal svg size 350,262 fname 'Verdana, Helvetica, Arial, sans-serif' \
#fsize '10'
#set output 'klein_bottle.svg'

# color definitions
# set style line 1 lc rgb '#157545' lt 1 lw 1 # --- green

# set tmargin at screen 0.99
# set bmargin at screen 0.01
# set lmargin at screen 0
# set rmargin at screen 0.9
# set pm3d depthorder hidden3d 1
# set hidden3d
# set style fill transparent solid 0.65
# set palette rgb 9,9,3
# unset colorbox
# unset key
# unset border
# unset tics
# set ticslevel 0
# set view 0,0,1,1
# set xrange[-2:2]
# set yrange[-2:2]
# set zrange[-2:2]
# set size square

set parametric
set isosamples 100,100
# set hidden3d
set urange[0:pi]
set vrange[0:2*pi]
x(u,v) = sin(u) * cos(v)
y(u,v) = sin(u) * sin(v)
z(u,v) = cos(u)

splot x(u,v),y(u,v),z(u,v)
# plot x(sin(t),t),y(sin(t),t),z(sin(t),t)
