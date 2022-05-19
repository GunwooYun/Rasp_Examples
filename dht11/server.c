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
	char ser_buff[10] = {0};
	int index = 0, temp, humi, str_len;
	char *pArray[2] = {0};
	char *pToken;
	printf("Raspberry Start\n");
	fflush(stdout);
	if((fd = serialOpen(device, baud)) < 0){
		fprintf(stderr, "Unable %s\n",strerror(errno));
		exit(1);
	}
	if(wiringPiSetup() == -1) return 1;
	while(1){
		if(serialDataAvail(fd)){
			ser_buff[index++] = serialGetchar(fd);
			if(ser_buff[index-1] == 'L'){
				ser_buff[index-1] = '\0';
				str_len = strlen(ser_buff);
				printf("ser_buff = %s\n", ser_buff);
				pToken = strtok(ser_buff, ":");
				int i = 0;
				while(pToken != NULL){
					pArray[i] = pToken;
					if(++i > 3) break;
					pToken = strtok(NULL, " ");
				}
				temp = atoi(pArray[0]);
				humi = atoi(pArray[1]);
				printf("temp = %d, humi = %d\n", temp, humi);
				for(int i = 0; i <= str_len; i++)
					ser_buff[i] = 0;
				index = 0;
			}
		}
		fflush(stdout);
	}
	return 0;
}
