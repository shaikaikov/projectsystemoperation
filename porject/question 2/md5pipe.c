#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/uio.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <sys/fcntl.h>
#include <sys/wait.h>
#include "md5.h"



//here the global of strings
char inbuf[20];     
char str[32];

//the function of signale SIGINT
void cheak_anddie(int sig_num){
   //if num==32 the encryption was successed print this and than kill the son.
   int num;
   num=strlen(str);
       if(num==32){
   printf("encrypted by process %d : %s\n",getpid() , str);
exit(0);
}

return;
}

int main(){
///the signal+two pipes and pid and nbytes(we will see what this in the contineu)
signal(SIGINT,cheak_anddie);
int p1[2],pid,nbytes;
int p2[2];
  
  

 
  
  

//cheak error
if(pipe(p1)<0){
  fprintf(stderr,"pipe failed");
  return 1;
}

if(pipe(p2)<0){
   fprintf(stderr,"pipe failed");
   return 1;
}
//create process of son and parent
 pid=fork();
if(pid>0){
close(p1[0]); //this part of pipe is to read and we dont need it
//here we need to create word
char msg[20];
printf("plain text: ");
   
    scanf("%s",msg);
 //pipe and than close it
write(p1[1],msg,20);
close(p1[1]);




close(p2[1]);  ///dont need it in this process
 if((nbytes =read(p2[0],str,32))>0){

       
           }
          //cheak if nbytes<0 if that happen exit
           if(nbytes<0){
             
           exit(1);
         }

close(p2[0]);  //we read this to str and then we close it


kill(pid,SIGINT);   //cheak the md5 and if that happen kill son
wait(NULL);         //wait untill son dead

     


}

else if(pid<0){
  fprintf(stderr,"pipe failed");
   return 1;
}


else{

close(p1[1]);        //we dont need this part of pipe here
     if((nbytes =read(p1[0],inbuf,20))>0){

        //create the encrypteion
        std::string s;
        s=md5(inbuf);
        for(int i=0;i<s.length();i++){
        str[i]=s[i];
        }
        
           
        }

     
        
      
        if(nbytes<0){
             
           exit(2);
         }
close(p1[0]); 

close(p2[0]);
      write(p2[1],str,32);

close(p2[1]);
      
      //stop the process untill he terminate/get signal to contineu
      pause();
          

    }  

  
  return 1;

}

