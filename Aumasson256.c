#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>

#define myrand32 ((ul)(4294967296.0*drand48()))
#define myrand4 ((ul)(16.0*drand48()))


#define ul unsigned int
#define ull unsigned long long
#define rotateleft(x, n) (((x) << (n)) ^ ((x) >> (32-n)))
#define rotateright(x, n) (((x) >> (n)) ^ ((x) << (32-n)))
#define Add(a,b,n)((rotateleft(a+b,n)))


void print(ul *x)
{
int i;
for (i = 0; i < 16; i++)
{
printf("%8x ", x[i]);
if (i > 0 && i % 4 == 3)
printf("\n");
}
printf("\n");
}

void printk(ul *x)
{
int i;
for (i = 0; i < 8; i++)
{
printf("%8x ", x[i]);
if (i > 0 && i % 4 == 3)
printf("\n");
}
printf("\n");
}

void initial(ul *x){
int i;

for (i=0;i<16;i++)

x[i]= myrand32;

x[0] =0x61707865;
x[5] =0x3320646e;
x[10]=0x79622d32;
x[15]=0x6b206574;

}

void initialkey(ul *k){
int i;

for (i=0;i<8;i++)

k[i]= myrand32;


}

void initial4key(ul *k){
int i;

for (i=0;i<8;i++){

k[i]= myrand32;
k[4]= k[0];
k[5]= k[1];
k[6]= k[2];
k[7]= k[3];

}

}

void merge(ul *x,ul *k){

int i;

for (i=1;i<5;i++){

x[i]=k[i-1];
}

for (i=11;i<15;i++){

x[i]=k[i-7];
}

}


void alterkey(ul*k,int word, int bit){

int i;

ul pat= 0x1<<bit;

k[word]=k[word]^pat;

}


void same(ul*x, ul*y){
int i;

 for (i=0;i<16;i++)

 y[i]=x[i];  

}


ul *sum(ul*x,ul*y, ul*z){

int i;

for(i=0;i<16;i++)
{
z[i]=(x[i]+y[i])%4294967296;
}
return z;
}


ul *subt(ul*x,ul*y,ul*z){

int i;

for(i=0;i<16;i++)
{

z[i]=(x[i]-y[i])%4294967296;

}
return z;
}


ul *add(ul*x,ul*y,ul*f){

int i;
for(i=0;i<16;i++)
{

f[i]=(x[i]^y[i]);
}
return f;
}

void swap(double *a, double *b)
{
    double temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

void swap_int(int *a, int *b)
{
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
    }

void sort(double *array, int *array1, int n)
{
    int ctr=0;
    for (int l = n - 1; l >= 0; --l)
    {
        ctr = 0;
        for (int j = 0; j < l; ++j)
        {
            if (array[j] > array[j + 1])
            {
                swap(&array[j], &array[j + 1]);
                swap_int(&array1[j], &array1[j + 1]);
                ctr = 1;
            }
        }
        if (ctr == 0)
        {
            break;
        }
    }
    printf("|   Bias  |  BIT  | Word | Bit | \n");
    for (int k = 0; k < n; ++k)
    {
        
        if (k == 0)
        {
            printf("|------------------------------|\n");
        }
        printf("| %.5lf | %d th | %d |  %d  | \n", array[k], array1[k], array1[k] / 32, array1[k] % 32);
        if (k == n - 1)
        {
            printf("|------------------------------|");
            
        }
    }

    
}

void fn(ul *a, ul*b,ul *c, ul*d){

ul a1,b1,c1,d1;

b1=(*b^Add(*a,*d,7));
c1=(*c^Add(b1,*a,9));
d1=(*d^Add(c1,b1,13));
a1=(*a^Add(c1,d1,18)); 

*a=a1;
*b=b1;
*c=c1;
*d=d1;
}

void hafn(ul *a, ul*b,ul *c, ul*d){

ul a1,b1,c1,d1;

b1=(*b^Add(*a,*d,7));
c1=(*c^Add(b1,*a,9));
// d1=(*d^Add(c1,b1,13));
// a1=(*a^Add(c1,d1,18)); 

// *a=a1;
*b=b1;
*c=c1;
// *d=d1;
}

void column(ul*x){

fn((&x[0]), &(x[4]), &(x[8]), &(x[12]));
fn((&x[5]), &(x[9]), &(x[13]),&(x[1]));                  
fn((&x[10]),&(x[14]),&(x[2]), &(x[6]));
fn((&x[15]),&(x[3]), &(x[7]), &(x[11]));
 }

void row(ul*x){

fn((&x[0]), &(x[1]), &(x[2]), &(x[3]));
fn((&x[5]), &(x[6]), &(x[7]), &(x[4]));                  
fn((&x[10]),&(x[11]),&(x[8]), &(x[9]));
fn((&x[15]),&(x[12]),&(x[13]),&(x[14]));
 }

void halfrow(ul*x){

hafn((&x[0]), &(x[1]), &(x[2]), &(x[3]));
hafn((&x[5]), &(x[6]), &(x[7]), &(x[4]));                  
hafn((&x[10]),&(x[11]),&(x[8]), &(x[9]));
hafn((&x[15]),&(x[12]),&(x[13]),&(x[14]));
 }



void refn(ul *a, ul*b,ul *c, ul*d){

ul a1,b1,c1,d1;

a1=(*a^Add(*c,*d,18));
d1=(*d^Add(*c,*b,13));
c1=(*c^Add(*b,a1,9));
b1=(*b^Add(a1,d1,7));

*a=a1;
*b=b1;
*c=c1;
*d=d1;

}

void rehafn(ul *a, ul*b,ul *c, ul*d){

ul a1,b1,c1,d1;

// a1=(*a^Add(*c,*d,18));
// d1=(*d^Add(*c,*b,13));
c1=(*c^Add(*b,*a,9));
b1=(*b^Add(*a,*d,7));

// *a=a1;
*b=b1;
*c=c1;
// *d=d1;

}

void recolumn(ul*x){

refn((&x[0]), &(x[4]), &(x[8]), &(x[12]));
refn((&x[5]), &(x[9]), &(x[13]),&(x[1]));                  
refn((&x[10]),&(x[14]),&(x[2]), &(x[6]));
refn((&x[15]),&(x[3]), &(x[7]), &(x[11]));
 }

void rerow(ul*x){

refn((&x[0]), &(x[1]), &(x[2]), &(x[3]));
refn((&x[5]), &(x[6]), &(x[7]), &(x[4]));                  
refn((&x[10]),&(x[11]),&(x[8]), &(x[9]));
refn((&x[15]),&(x[12]),&(x[13]),&(x[14]));
 }

void rehalfrow(ul*x){

rehafn((&x[0]), &(x[1]), &(x[2]), &(x[3]));
rehafn((&x[5]), &(x[6]), &(x[7]), &(x[4]));                  
rehafn((&x[10]),&(x[11]),&(x[8]), &(x[9]));
rehafn((&x[15]),&(x[12]),&(x[13]),&(x[14]));
 }


int main(){

printf("----------------The Aumasson way PNB set----------------\n");
 
ul x[16],x1[16],y[16],y1[16],z[16],z1[16],f[16],b[16],k[8],pt,pat,pattern;
 

int i,j,diff;
 
int bit,word; 

int pnbcount=0;
int forwardcount=0;
int backwardcount=0;

int KEYBIT[256];
int PNBword = 0;
int bit_no = 0;
int l = 0;

double bias[8][32];
double BIAS[256];

double biaslimit=0.12;

// double count=0;

double LOOP = 1000000;

srand48(time(NULL));

l=0;

for(word=0;word<8;word++){   

for(bit=0;bit<32;bit++){

double count=0;

for(int loop=0;loop<LOOP;loop++){


initial(x);
initialkey(k);

// initialkey(k);

merge(x,k);

same(x,x1);
same(x,y);

pt=0x1<<31;

// pt=0x1<<0;

x1[7]=x1[7]^pt;


same(x1,y1);

column(x);
column(x1);

row(x);
row(x1);

column(x);
column(x1);

row(x);
row(x1);

// column(x);
// column(x1);

/*4-round complete*/

add(x,x1,f);


pat=0x1<<14;

if(((f[1])&pat)==0)

{
forwardcount=1;
}
else
{
forwardcount=0;
}

column(x);
column(x1);

row(x);
row(x1);

column(x);
column(x1);

row(x);
row(x1);

sum(x,y,z);
sum(x1,y1,z1);

/*key change*/


alterkey(k,word,bit);
// alterkey(k,word+4,bit);

merge(y,k);
merge(y1,k);


subt(z,y,x);
subt(z1,y1,x1);

 
/*reverse round start*/

rerow(x);
rerow(x1);

recolumn(x);
recolumn(x1);

rerow(x);
rerow(x1);

recolumn(x);
recolumn(x1);


add(x,x1,b);

pat=0x1<<14;

if(((b[1])&pat)==0)
{
backwardcount=1;

}
else
{
backwardcount=0;
}

if(forwardcount==backwardcount){

    count++;
}

}

bias[word][bit] = (2.0 * count) / LOOP - 1.0;


if(bias[word][bit] >=biaslimit)

 {

     BIAS[PNBword]=bias[word][bit];

    KEYBIT[l] = ((word * 32) + bit);

 printf("The bias for %d-th keybit of %d-th word is \t ", ((word * 32) + bit),word);

  printf("%.10lf ~ %.5lf\n, ", BIAS[PNBword], BIAS[PNBword]);
PNBword++;
l++;
            }



}
}

sort(BIAS, KEYBIT, PNBword);

printf("\nTotal number of Non-significant keybits is %d\n", PNBword);
}
    
