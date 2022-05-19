#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<string.h>

#include<wiringPi.h>
#include<wiringSerial.h>

char device[] = "/dev/ttyACM0";
int fd;
unsigned long baud = 9600;
int main()
{
	printf("%s\n", "Raspberry Startup");
	fflush(stdout);
	
	if(( fd = serialOpen(device, baud)) < 0 ){
		printf("Unable to open serial device %s\n", strerror(errno));
		exit(1);
	}
	
	if(wiringPiSetup() == -1) return 1;

	while(1)
	{
		if(serialDataAvail(fd))
		{
			char newChar = serialGetchar(fd);
			printf(" %c ", newChar);
			fflush(stdout);
		}
	}
	printf("\n");
	

	return 0;

}

