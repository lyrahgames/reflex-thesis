set size square

set rmargin 0.5
set tmargin 0.5
set lmargin 3.5
set bmargin 1.5

unset key
set format x "%.1f"
set format y "%.1f"

set xr [-1.2:1.2]
set yr [-0.2:2.2]

f(x) = x**3
g(x) = 2 * x**2

set style arrow 1 size 0.1,15,40 fixed filled lw 4
set arrow arrowstyle 1 from f(0.4),g(0.4) to f(0.41),g(0.41)
set arrow arrowstyle 1 from f(0.6),g(0.6) to f(0.61),g(0.61)
set arrow arrowstyle 1 from f(0.8),g(0.8) to f(0.81),g(0.81)

set arrow arrowstyle 1 from f(-0.4),g(-0.4) to f(-0.39),g(-0.39)
set arrow arrowstyle 1 from f(-0.6),g(-0.6) to f(-0.59),g(-0.59)
set arrow arrowstyle 1 from f(-0.8),g(-0.8) to f(-0.79),g(-0.79)

set style arrow 2 size 0.05,90 fixed filled lw 4
set arrow arrowstyle 2 front from f(-0.99),g(-0.99) to f(-1),g(-1)
set arrow arrowstyle 2 front from f(0.99),g(0.99) to f(1),g(1)

# do for [i=1:8] {
#   t = 2.0 * i / 9.0 - 1.0
#   set arrow arrowstyle 1 from f(t),g(t) to f(t+0.01),g(t+0.01)
# }

set parametric
plot [-1:1] f(t), g(t) notitle lc rgb "#0055ff" lw 4
