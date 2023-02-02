# Vector-Transmitted-Disease

In my research, I found a lot of advanced SIR models that contained various ways of expressing the ODEs. I decided to keep my ODEs that I used to a more general structure—as I will show later—since it was a lot easier to implement them in C++ and it made modifying parameters a lot easier when testing the program for a simulation of different trends. Furthermore, I was mostly familiar with solving ODEs using either Runge Kutta integration or Euler’s method, so I didn’t want to overcomplicate the solutions to these ODEs with methods I have not learned about, making the debugging process seemingly harder. A lot of models had a wide range of variables to represent different factors in the ODEs, such as quarantine/isolation rate and accounting for bottlenecks in the population for recovery like in Espinosa’s (2020) article on Frontiers on modelling COVID19 with an SIR model.

We let $S$ be the number of susceptible people in � at a given time, �. Let � be the number
of infected people in � at a given time, �. Let � be the number of recovered people in � at a given
time, �. It follows that, �(�) + �(�) + �(�) = � Let � be the rate that susceptible people turn into
infected people. Let � be the rate that infected people turn into recovered people. Let � be a
fraction of how many people in the population recover per day. The ODEs that I used express
and simulate the SIR model are the following
