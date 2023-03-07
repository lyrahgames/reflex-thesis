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

# # color definitions
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
# # set view 60,210,1.5,1
# set isosamples 19,44
# # set xrange[-8:10]
# # set yrange[-8:8]
# set urange[-pi:pi]
# set vrange[-pi:pi]

# set parametric
# x(u,v)= (1 + 0.5 * v * cos(0.5 * u)) * cos(u)
# y(u,v)= (1 + 0.5 * v * cos(0.5 * u)) * sin(u)
# z(u,v)= 0.5 * v * sin(0.5 * u)
# splot x(u,v),y(u,v),z(u,v) w pm3d
# plot cos(t),sin(t)

set parametric
set isosamples 50
# set pm3d depthorder hidden3d 1
set pm3d depthorder
set hidden3d trianglepattern 7
set xrange[-8:8]
set yrange[-8:8]
splot [-pi:pi][-pi:pi] (5 + cos(u))*cos(v), (5 + cos(u))*sin(v), sin(u) w pm3d
