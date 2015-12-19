#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
/****************File setup******************/ 

FILE *circuit, *input, *output;

circuit = fopen(argv[1], "r");
input = fopen(argv[2], "r");
output = fopen(argv[3], "w");

if (circuit == NULL)
{printf("FIle %s cannot open!\n", argv[1]);
}
if (input == NULL)
{printf("FIle %s cannot open!\n", argv[2]);
}
if (output == NULL)
{printf("FIle %s cannot open!\n", argv[3]);
}
if (argc != 4)
{printf("Usage: executable circuitFile inputFile outputFile\n");
 exit(0);
}
	
/****************Variable setup******************/

int F[100], S[100], PI[100], PO[100], OUT[100], IN[100];
int a, i=0, j=0, k=0, z, x, y, Isize, Osize, Tsize, Ssize, t=0, SIZE;
int IN1, IN2, IN3, O1, in, I, IA[50];
char Gate;	
int O, I1, I2, I3;
char gatename[11];

/*****************GATE NAMING*********************/
while (fscanf(circuit, "%s", &gatename)!=EOF)
{
	//Scan in for each gate type and name

	/********************AND***********************/
	if (gatename[0] == 'A')
	{
		fscanf(circuit, "%d %d %d", &OUT[j], &IN[k], &IN[k+1]);
		F[i]=OUT[j];
		F[i+1]=IN[k];
		F[i+2]=IN[k+1];
		i=i+3;
		j++;
		k=k+2;
	}
	/********************OR***********************/
	if (gatename[0] == 'O')
	{
		fscanf(circuit, "%d %d %d", &OUT[j], &IN[k], &IN[k+1]);
		F[i]=OUT[j];
		F[i+1]=IN[k];
		F[i+2]=IN[k+1];
		i=i+3;
		j++;
		k=k+2;
	}
	/********************NAND***********************/
	if (gatename[0] == 'N')
	{
		if (gatename[2] == 'N')
		{
			fscanf(circuit, "%d %d %d", &OUT[j], &IN[k], &IN[k+1]);
			F[i]=OUT[j];
			F[i+1]=IN[k];
			F[i+2]=IN[k+1];
			i=i+3;
			j++;
			k=k+2;
		}
	}
	/********************NOT***********************/
	if (gatename[0] == 'N')
	{
		if (gatename[2] == 'T')
		{
		fscanf(circuit, "%d %d", &OUT[j], &IN[k]);
		F[i]=OUT[j];
		F[i+1]=IN[k];
		i=i+2;
		j++;
		k=k+1;
		}
	}
	/********************NOR***********************/
	if (gatename[0] == 'N')
	{
		if (gatename[2] == 'R')
		{
			fscanf(circuit, "%d %d %d", &OUT[j], &IN[k], &IN[k+1]);
			F[i]=OUT[j];
			F[i+1]=IN[k];
			F[i+2]=IN[k+1];
			i=i+3;
			j++;
			k=k+2;
		}
	}
	/********************XOR***********************/
	if (gatename[0] == 'X')
	{
		fscanf(circuit, "%d %d %d", &OUT[j], &IN[k], &IN[k+1]);
		F[i]=OUT[j];
		F[i+1]=IN[k];
		F[i+2]=IN[k+1];
		i=i+3;
		j++;
		k=k+2;
	}
	/********************IMPLY***********************/
	if (gatename[0] == 'I')
	{
		fscanf(circuit, "%d %d %d", &OUT[j], &IN[k], &IN[k+1]);
		F[i]=OUT[j];
		F[i+1]=IN[k];
		F[i+2]=IN[k+1];
		i=i+3;
		j++;
		k=k+2;
	}
	/********************ENEE140***********************/
	if (gatename[0] == 'E')
	{
		fscanf(circuit, "%d %d %d %d", &OUT[j], &IN[k], &IN[k+1], &IN[k+2]);
		F[i]=OUT[j];
		F[i+1]=IN[k];
		F[i+2]=IN[k+1];
		F[i+3]=IN[k+2];
		i=i+4;
		j++;
		k=k+3;
	}
}

Tsize = i;
Isize = k;
Osize = j;

fclose(circuit);

//Sort Array
for (i = 0; i<Tsize; ++i)
{
	for (j=i+1; j<Tsize ; j++)
	{
		if (F[i] > F[j])
		{
			a =  F[i];
			F[i] = F[j];
			F[j] = a;
		}
	}
}

z=0;
for(x=0; x<Tsize; x++)
{
		if (F[x]==F[x+1])
		{
			continue;
		}
		S[z]=F[x];
		z++;
}
Ssize = z;

/****************DETERMINE PI AND PO****************/
//PI
for (i=0; i<Ssize; i++)
{
	PI[i] = 1;	
}


for (i=0; i<Ssize; i++)
{
	for (j=0; j<Osize; j++)
	{
		if (S[i] == OUT[j])
		{
			PI[i] = 0;
			I++;
		}
	}
}

//PO
for (i=0; i<Ssize; i++)
{
	PO[i] = 1;	
}


for (i=0; i<Ssize; i++)
{
	for (j=0; j<Isize; j++)
	{
		if (S[i] == IN[j])
		{
			PO[i] = 0;
		}
	}
}

/**********Correct Number of Values****************/
i=0;
while (fscanf(input, "%d", &I)!=EOF)
{
	i++;
}
SIZE = i;
fclose(input);

if (SIZE < Ssize-I)
{
	printf("Invalid number of input values!\n");
	exit(0);
}


/***********VALUES**********/
input = fopen(argv[2], "r");
int Value[Ssize];
for (i=0; i<Ssize; i++)
{
	if (PI[i] == 1)
	{
		fscanf(input, "%d", &in);
		Value[i] = in;
	}
	if (PI[i] == 0)
	{
		Value[i] = 0;
	}	
}

circuit = fopen(argv[1], "r");

while (fscanf(circuit, "%s", gatename)!=EOF)
{
/*********************AND************************/
	if (gatename[0] == 'A')
	{
		fscanf(circuit, "%d %d %d", &O, &I1, &I2);
		if((Value[I1]==1) && (Value[I2]==1))
		{
			Value[O]=1;
		}
		else
		{
			Value[O]=0;
		}
	}
/*************************OR*************************/	
	if (gatename[0] == 'O')
	{
		fscanf(circuit, "%d %d %d", &O, &I1, &I2);
		if((Value[I1]==1) || (Value[I2]==1))
		{
			Value[O]=1;
		}
		else
		{
			Value[O]=0;
		}
	}
	/*************************NAND*************************/	
	if (gatename[0] == 'N')
	{
		if (gatename[2] == 'N')
		{
			fscanf(circuit, "%d %d %d", &O, &I1, &I2);
			if((Value[I1]==1) && (Value[I2]==1))
			{
				Value[O]=0;
			}
			else
			{
				Value[O]=1;
			}
		}
	}
	/*************************NOT*************************/	
	if (gatename[0] == 'N')
	{
		if (gatename[2] == 'T')
		{
			fscanf(circuit, "%d %d", &O, &I1);
			if(Value[I1]==0)
			{
				Value[O]=1;
			}
			else
			{
				Value[O]=0;
			}
		}
	}
	/*************************NOR*************************/	
	if (gatename[0] == 'N')
	{
		if (gatename[2] == 'R')
		{
			fscanf(circuit, "%d %d %d", &O, &I1, &I2);
			if((Value[I1]==1) || (Value[I2]==1))
			{
				Value[O]=0;
			}
			else
			{
				Value[O]=1;
			}
		}
	}
	/*************************XOR*************************/	
	if (gatename[0] == 'X')
	{
		fscanf(circuit, "%d %d %d", &O, &I1, &I2);
		if(Value[I1] == Value[I2])
		{
			Value[O]=0;
		}
		else
		{
			Value[O]=1;
		}
	}
	/*************************IMPLY*************************/	
	if (gatename[0] == 'I')
	{
		fscanf(circuit, "%d %d %d", &O, &I1, &I2);
		if((Value[I1]==1) && (Value[I2]==0))
		{
			Value[O]=0;
		}
		else
		{
			Value[O]=1;
		}
	}
	/*************************ENEE140*************************/	
	if (gatename[0] == 'E')
	{
		fscanf(circuit, "%d %d %d %d", &O, &I1, &I2, &I3);
		if((Value[I1]==0) && (Value[I2]==0))
		{
			Value[O]=1;
		}
		if((Value[I1]==1) && (Value[I2]==0) && (Value[I3]==0))
			{
			Value[O]=1;
		}
		else
		{
			Value[O]=0;
		}
	}
}

/**************************FILE PRINT PO**************************/
for (i=0; i<=Ssize; i++)
{
	if(PO[i] == 1)
	{
		fprintf(output, "%3d", S[i]);
	}
}
fprintf(output, "\n");
for (i=0; i<=Ssize; i++)
{
	if(PO[i] == 1)
	{
		fprintf(output, "%3d", Value[i]);
	}
}

fclose(circuit);
fclose(input);
fclose(output);
return 0;
}
