# Vector-Transmitted-Disease

In my research, I found a lot of advanced SIR models that contained various ways of expressing the ODEs. I decided to keep my ODEs that I used to a more general structure—as I will show later—since it was a lot easier to implement them in C++ and it made modifying parameters a lot easier when testing the program for a simulation of different trends. Furthermore, I was mostly familiar with solving ODEs using either Runge Kutta integration or Euler’s method, so I didn’t want to overcomplicate the solutions to these ODEs with methods I have not learned about, making the debugging process seemingly harder. A lot of models had a wide range of variables to represent different factors in the ODEs, such as quarantine/isolation rate and accounting for bottlenecks in the population for recovery like in Espinosa’s (2020) article on Frontiers on modelling COVID19 with an SIR model.

We let $S$ be the number of susceptible people in $p$ at a given time, $t$. Let $I$ be the number
of infected people in $p$ at a given time, $t$. Let $R$ be the number of recovered people in $t$ at a given
time, $t$. It follows that, $S(t) + I(t) + R(t) = p$ Let $x$ be the rate that susceptible people turn into
infected people. Let $y$ be the rate that infected people turn into recovered people. Let $z$ be a
fraction of how many people in the population recover per day. The ODEs that I used express
and simulate the SIR model are the following:

$\frac{dS}{dt}=-xSI$

$\frac{dI}{dt}=ySI-z$

$\frac{dR}{dt}=zI$

I used David Smith and Lang Moore’s (2004) article on modeling the spread of disease
using the SIR model and derived these equations from it. As mentioned above, we use a fraction
of the population in our ODEs because when dealing with large populations (in the millions), the
numbers can get quite large and thus arithmetic can produce odd results on the computer. A big
problem I had when trying to implement these ODEs into C++ was that when I was solving
them, I was getting numbers so small (underflow) when dividing the population by a small
number; this led to the breaking of the program things like unknown compilation errors. Another
issue I had with implementing these ODEs was because of the fraction of population
components, which occurred when I was solving them using Runge-Kutta integration.
Originally, I had my $x$, $y$, and $z$ variables as functions that I would call in the ODE in C++. 

However, when I went to update my parameters for the population, I would be updating the
fraction of the population, and not the total population. Therefore, I was passing a fractionally
smaller number of the population into the function that was supposed to return the fraction of the
population and would get a number that is twice as small (in some fractional rate) that it
should’ve been. To counter this problem, I removed the functions that produced a fractional
amount of the population and decided to only work with fractional numbers by computing the
fractions at the start (before the integration), and never converting back to the total population.
Therefore, when you look at the graph, the y-axis, in this case the P axis for population, is a
maximum value of 1. The real number values from 0 to 1 represent any real number in that range
that multiplies by the population to produce a fraction of the population. Furthermore, once
someone from the population is infected, they are no longer susceptible in this case. I chose this
characteristic because I did testing with the Hong Kong Flu.

The following are demonstrations of the plotted graph in PGPlot upon compilation of the program:
<img width="526" alt="image" src="https://user-images.githubusercontent.com/58610843/216411295-bc48f5c7-2041-4fd6-b29d-b4f3c0156558.png">

<img width="497" alt="image" src="https://user-images.githubusercontent.com/58610843/216411484-64ea2aeb-7577-4f83-8e3a-706d3e254c7d.png">

The following shows data corresponding to the following table for the Hong Kong Flu:

<img width="623" alt="image" src="https://user-images.githubusercontent.com/58610843/216411820-64fe9845-a2d0-4d04-b5a7-7ac61179407d.png">

Simulated disease spread:
<img width="461" alt="image" src="https://user-images.githubusercontent.com/58610843/216411627-622a6152-bfac-4816-8e80-3c3593875177.png">


