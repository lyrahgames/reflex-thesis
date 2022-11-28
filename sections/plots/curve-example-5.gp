set size square

set rmargin 0.5
set tmargin 0.5
set lmargin 3.5
set bmargin 1.5

unset key
set format x "%.1f"
set format y "%.1f"

set xr [-1.2:1.2]
set yr [-0.6:1.6]
set tr [0:pi]

f(x) = cos(x)
g(x) = sin(x)


set style arrow 1 size 0.1,15,40 fixed filled lw 4

do for [i=1:4] {
  t = pi * (i) / 5
  set arrow arrowstyle 1 from f(t),g(t) to f(t+0.05),g(t+0.05)
}

set style arrow 2 size 0.05,90 fixed filled lw 4
set arrow arrowstyle 2 front empty from f(0.01),g(0.01) to f(0),g(0)
set arrow arrowstyle 2 front from f(pi-0.01),g(pi-0.01) to f(pi),g(pi)

set samples 1000
set parametric
plot f(t), g(t) notitle lc rgb "#0055ff" lw 4
