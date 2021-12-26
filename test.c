#include <sys/time.h>
#include <stdio.h>
#include <limits.h>

int main(void)
{
	struct timeval tmp;

	long years;
	long days;
	long hours;
	long minutes;
	long seconds;

	int res = gettimeofday(&tmp, NULL);
	printf("%d res %ld seconds %d microsec\n", res, tmp.tv_sec, tmp.tv_usec);
	printf("%lld", SSIZE_MAX);
/*
	years = sec/(60*60*24*365);
	seconds = sec % (years*60*60*24*365);
	days = seconds / (60*60*24);
	seconds = seconds % (days*60*60*24);
	hours = seconds / (60*60);
	seconds = seconds % (hours*60*60);
	minutes = seconds / 60;
	seconds = seconds % (minutes*60);

	printf("%ld years %ld days %ld hours %ld minutes %ld seconds\n", years, days, hours, minutes, seconds);
	printf("%ld years %ld days %ld hours %ld minutes %ld seconds %ld miliseconds %ld microseconds\n", (usec/1000/1000/60/60/24/365), (usec/1000/1000/60/60/24), (usec/1000/1000/60/60), (usec/1000/1000/60), (usec/1000/1000), (usec/1000), usec);*/

	//printf("%ld", usec%(1000*1000*60*60*24*365));
	return (0);
}
