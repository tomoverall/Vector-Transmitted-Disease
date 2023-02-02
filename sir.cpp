#include <stdio.h>
#include <iostream>
#include <cmath>
#include "cpgplot.h"

// time (int t) is in days for this simulation
// susceptible fraction of the total population
double s(double susceptible, double population)
{
    return susceptible / population;
}

// infected fraction of the total population
double i(double infected, double population)
{
    return infected / population;
}

// recovered fraction of the total population
double r(double recovered, double population)
{
    return recovered / population;
}

// differential equation for susceptible individuals in the population
double dsdt(double population, double susceptible, double infected, double recovered, double contacts, double vaccinationRate)
{
    return (-contacts) * susceptible * infected - vaccinationRate;
}

// differential equation for recovered individuals in the population, k is fraction of the infected that recover in a day
double drdt(double population, double infected, double recoverFraction, double vaccinationRate)
{
    return (recoverFraction)*infected + vaccinationRate;
}

// differential equation for infected individuals in the population
double didt(double population, double susceptible, double infected, double recoverFraction, double contacts)
{
    return (contacts)*susceptible * infected - (recoverFraction * infected);
}

double deltat(double start, double end, int step)
{
    return (end - start) / step;
}

int main()
{
    // number of susceptible individuals in the population
    double population = 7900000.0;
    double susceptible = 7900000.0 / population;
    // number of infected individuals in the population
    double infected = 10.0 / population;
    // number of recovered individuals in the population
    double recovered = 0.0 / population;
    // contacts per day for each person in the population
    double contact = 0.5;
    // average infected symptoms last about 3 days, so our 'recover fraction' value is 1/3
    double recoverFraction = 0.33;
    // vaccination rate
    double vaccinationRate = 15000 / population;

    // Runge-Kutta integration
    int n = 365.0;
    // time in days (plotting for a year in this case)
    double tstart = 0.0;
    double tend = 365.0;
    double time = tstart;
    float ta[n];
    float ys[n];
    float yr[n];
    float yi[n];
    double ks1;
    double ki1;
    double kr1;
    double ks2;
    double ki2;
    double kr2;
    double ks3;
    double ki3;
    double kr3;
    double ks4;
    double ki4;
    double kr4;
    float yv[n];
    double vaccinated = 0;

    for (int i = 0; i < n; i++)
    {
        ks1 = deltat(tstart, tend, n) * dsdt(population, susceptible, infected, recovered, contact, vaccinationRate);
        ki1 = deltat(tstart, tend, n) * didt(population, susceptible, infected, recoverFraction, contact);
        kr1 = deltat(tstart, tend, n) * drdt(population, infected, recoverFraction, vaccinationRate);
        ks2 = deltat(tstart, tend, n) * dsdt(population, susceptible + 0.5 * ks1, infected, recovered, contact, vaccinationRate);
        ki2 = deltat(tstart, tend, n) * didt(population, susceptible, infected + 0.5 * ki1, recoverFraction, contact);
        kr2 = deltat(tstart, tend, n) * drdt(population, infected + 0.5 * kr1, recoverFraction, vaccinationRate);
        ks3 = deltat(tstart, tend, n) * dsdt(population, susceptible + 0.5 * ks2, infected, recovered, contact, vaccinationRate);
        ki3 = deltat(tstart, tend, n) * didt(population, susceptible, infected + 0.5 * ki2, recoverFraction, contact);
        kr3 = deltat(tstart, tend, n) * drdt(population, infected + 0.5 * kr2, recoverFraction, vaccinationRate);
        ks4 = deltat(tstart, tend, n) * dsdt(population, susceptible + ks3, infected, recovered, contact, vaccinationRate);
        ki4 = deltat(tstart, tend, n) * didt(population, susceptible, infected + ki3, recoverFraction, contact);
        kr3 = deltat(tstart, tend, n) * drdt(population, infected + kr3, recoverFraction, vaccinationRate);
        ta[i] = time;
        time = time + deltat(tstart, tend, n);
        vaccinated = vaccinated + vaccinationRate;
        susceptible = susceptible + (ks1 + 2 * ks2 + 2 * ks3 + ks4) / 6.0;
        infected = infected + (ki1 + 2 * ki2 + 2 * ki3 + ki4) / 6.0;
        recovered = recovered + (kr1 + 2 * kr2 + 2 * kr3 + kr4) / 6.0;
        ys[i] = susceptible;
        yi[i] = infected;
        yr[i] = recovered;
        yv[i] = vaccinated;
    }

    // Open a pgplot window
    if (!cpgopen("/XWINDOW"))
        return 1;

    // Set-up plot axes
    // Second arg is x-axis max
    cpgenv(0., 365., 0., 1., 0, 1);
    // label axes
    cpglab("time (days)", "fraction of total population", "susceptible in blue, recovered in green, infected in red, and vaccinated in teal");
    // plot susceptible
    cpgsci(4);
    cpgline(n, ta, ys);
    // plot recovered
    cpgsci(3);
    cpgline(n, ta, yr);
    // plot infected
    cpgsci(2);
    cpgline(n, ta, yi);
    // plot vaccinated
    cpgsci(5);
    cpgline(n, ta, yv);
    cpgclos();

    return 0;
}
