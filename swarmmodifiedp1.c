#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#define M_PI 3.14159265358979323846
#define debug 1


//Global Variables
int *arraycmd;
int *arrayvb;
float *arraycst;
void exec_function(int *,int *,float *);
void readfile(FILE *file1);

FILE *file1;
int arraylen;
int cmd,vb;
float cst;  
//Print result
main()
{
	printf("Please enter the requested contents into the tristack.txt file\n");
	printf("Enter the size of your triplet list and data list size");
	printf("Input should be: triplet list size(space)data list size(enter)\n");	
	printf("Next enter the contents of your stacks.\n");
	printf("Your input should have the following order:\nCommand(space)Variable(space)Constant(space)Data(enter)\n");	
	printf("The amount of numbers you enter for each stack should be equal to list size*tech size");	 		
	printf("\n");	
	readfile(file1);
	
}

//Read File

/**********************************
 *                                *
 *  Function Name:  readfile      *
 *  Function Author:  M. Li       *
 *                    C. Qiu      *
 *                    S. Kazadi   *
 *  Creation Date:  24 May 2015   *
 *                                *
 *  Global Varibles: arraycmd,    *
 *  arrayvb, arraycst, arraylen   *
 *                                *		
 *  Variable Description:         *
 *  1. Name: arraycmd             *
 *     Type: array pointer        *
 *     The array that stores the  *
 *     function number            *
 *                                *
 *  2. Name: arrayvb              *
 *     Type: array pointer        *
 *     The array that stores the  *
 *     user entered variables     *
 *                                *
 *  3. Name: arraycst             *
 *     Type: array pointer        *
 *     The array that stores the  *
 *     user entered constants     *
 *                                *
 *  4. Name: arraylen             *
 *     Type: integer              *
 *     Measure the length of the  *
 *     array, used for memory     *
 *     allocation.                *
 *                                *
 *  Parameter Description:        *
 *  1. Name: file1                *
 *     Type: file                 *
 *     This is were the user will *
 *     input the function numbers * 
 *     variables and constants.   *
 *     The file will be read by   *
 *     exec_function.             *
 *                                *
 *                                *
 *  Description:                  *
 *  Program reads a triad of      *
 *  values from a file. Each      *
 *  value is stored in seperate   *
 *  arrays. The values represent  *
 *  commands, variables, and      *
 *  constants.                    *
 *                                *
 **********************************/


void readfile(FILE *file1)
{
	file1 = fopen("tristack.txt","r");
	int k; 
	fscanf(file1,"%d", &arraylen);
	arraycmd=(int *)malloc(sizeof(int)*arraylen);
	arrayvb=(int *)malloc(sizeof(int)*arraylen);
	arraycst=(float *)malloc(sizeof(float)*arraylen);
	for(k=0;k<arraylen;k++)
	{
		fscanf(file1,"%d %d %f", &cmd,&vb,&cst);
		arraycmd[k]=cmd;
		arrayvb[k]=vb;
		arraycst[k]=cst;
	}
#ifdef debug
	printf("More debugging stuff.\n");
#endif	
	for(k=0;k<arraylen;k++)
	{
		printf("%d %d %f\n",arraycmd[k],arrayvb[k],arraycst[k]);
	}
	exec_function(arraycmd,arrayvb,arraycst);
	fclose(file1);
	
}

/***********************************
*                                  * 
*  Function Name: exec_function    * 
*  Function Author: M. Li          *
*                   C. Qiu         *
*                   S. Kazadi      *
*  Creation Date:  24 May 2015     *
*                                  *
*  Global Variables: arraylen,     *
*  arrayvb, arraycmd, arraycst     *
*                                  *
*  Local Variables: i, k, st_ptr   *
*                                  *
*                                  *
*  Variable Description:           *
*                                  *
*  1. Name: i                      *
*     Type: Integer                *
*     Used to move the For loop    *
*                                  *
*  2. Name: k                      *
*     Type: Integer                *
*     Used to store the value of   *
*     pi.                          *
*                                  *
*  3. Name: st_ptr                 *
*     Type: Integer                *
*     The stack pointer that is    *
*     used for the reverse polish. *
*     Moves foward and backward    *
*     depending on function        *
*                                  *
*  Description:                    *
*  Each function is called by the  *  
*  command variable. Depending on  *
*  the function, it will either    *
*  move the stack pointer foward   *
*  while inputing values into the  *
*  stack, or it will take the      *
*  current value and do something  *
*  with it while moving the stack  * 
*  pointer back one or two spaces. *
*                                  *
*                                  *
*                                  * 
************************************/

void exec_function(int *arraycmd, int *arrayvb, float *arraycst)
{	
	#ifdef debug

			printf("This is the debugging stuff.\n");

	#endif
	//Variable initation
	float divh, div, divf, stack[1000];	                              
	int modh,mod,modf,i,k,st_ptr=0;              
	for (i=0; i<arraylen; i++)
	{
		#ifdef debug

			printf("This is the debugging stuff!\n");

		#endif	
	printf("%d\n",arraycmd[i]);
		switch (arraycmd[i]) 
		{


			case 1: //Adding integers and moving stack pointer forward
                	{
                   		stack[st_ptr]=arrayvb[i];
                   		st_ptr++;
                	}
                	break;
		
			case 2://Adding integers to stack and moving pointer forward
               		{
                   		stack[st_ptr]=arraycst[i];
                   		st_ptr++;
                	}
                	break;
		
			case 3: //Addition
                	{
                  		if (st_ptr>=2)
                   		{
                      			stack[st_ptr-2]=stack[st_ptr-2]+stack[st_ptr-1];
                      			st_ptr--;
                   		}
                	}
                	break;
		
			case 4: //Subtraction
                	{
		     		if (st_ptr>=2)
                   		{
                      			stack[st_ptr-2]=stack[st_ptr-2]-stack[st_ptr-1];
                      			st_ptr--;
                   		}
				#ifdef debug

			printf("This is the debugging stuff???\n");

#endif
                	}
                	break;
		
			case 5: //Multiplication
              		{
		     		if (st_ptr>=2)
                   		{
                      			stack[st_ptr-2]=stack[st_ptr-2]*stack[st_ptr-1];
                      			st_ptr--;
                   		}
                	}
                	break;
		
			case 6: //Division 
                	{
     		     		if (st_ptr>=2)
                   		{
                      			stack[st_ptr-2]=stack[st_ptr-2]/stack[st_ptr-1];
                      			st_ptr--;
					if (stack[st_ptr-1]==0) //Error check
					{
						printf("Please revise file 2, you have a nonvalid divisor");
					}
                   		}
                	}
                	break;
		
			case 7: //Division
                	{
		        	if (st_ptr>=2)
                   		{
                      			stack[st_ptr-2]=stack[st_ptr-1]/stack[st_ptr-2];
                      			st_ptr--;
					if (stack[st_ptr-2]==0) //Error check
					{
						printf("Please revise file 2, you have a nonvalid divisor");
                   			}
                		}
                	}
			break;
		
			case 8://exponentials
                	{
	        		if (st_ptr>=2)
                  	 	{
                   	   		stack[st_ptr-2]=exp(log(stack[st_ptr-1])*stack[st_ptr-2]);
                   	   		st_ptr--;
                   		}
               		}
              		break;
		
			case 9: //exponentials
                	{
      		        	if (st_ptr>=2)
                   		{
                      			stack[st_ptr-2]=exp(log(stack[st_ptr-2])*stack[st_ptr-1]);
                      			st_ptr--;
                   		}
                	}
                	break;
                
			case 10: //Sine
                	{
      		        	if (st_ptr>=1)
                   		{
                      			st_ptr--;
		      			stack[st_ptr-1]=sin(stack[st_ptr-1]);
                   		}
                	}
                	break;
   		
			case 11: //Cosine
                	{
      		        	if (st_ptr>=1)
                   		{
                      		st_ptr--;
		      		stack[st_ptr-1]=cos(stack[st_ptr]-1);
                   		}
                	}
                	break;
   		
			case 12: //Tangent
                	{
			   	
				divh=stack[st_ptr-1]/M_PI;
				modh = (int) div;
				k=stack[st_ptr-1]-M_PI*mod;
      		           	if (st_ptr>=1&&k!=M_PI/2 )
                   		{
                      			st_ptr--;
		      			stack[st_ptr-1]=tan(stack[st_ptr-1]);
                   		}
                	}
                	break;
   		
			case 13: //Arcsine
                	{
      		           	if (st_ptr>=1&&1>=stack[st_ptr-1]>=-1)
                   		{
                      		st_ptr--;
		      		stack[st_ptr-1]=asin(stack[st_ptr-1]);
                	   	}
                	}
                	break;
		
			case 14: //Arccosine
                	{
      		        	if (st_ptr>=1&&1>=stack[st_ptr-1]>=-1)
                   		{
                      			st_ptr--;
		      			stack[st_ptr-1]=acos(stack[st_ptr-1]);
                   		}
                	}
                	break;
		
			case 15://Arctangent
                	{
      		           	if (st_ptr>=1)
                   		{
                     			st_ptr--;
		      			stack[st_ptr-1]=atan(stack[st_ptr-1]);
                   		}
                	}
                	break;
		
			case 16: //Modularity
                	{
      		           	if (st_ptr>=2)
                   		{
		      			div = stack[st_ptr-2] / stack[st_ptr-1];
					mod = (int) div;
					modf = stack[st_ptr-2] - stack[st_ptr-1]*mod;
		      			stack[st_ptr-2]= (float) modf;
					st_ptr--;
                   		}
                	}
                	break;
		
			case 17: //Modularity
                	{
      		           	if (st_ptr>=2)
                   		{
		      			div = stack[st_ptr-1] / stack[st_ptr-2];
					mod = (int) div;
					modf = stack[st_ptr-1] - stack[st_ptr-2]*mod;
		      			stack[st_ptr-2]= (float) modf;
					st_ptr--;
                   		}
                	}
                	break;
		
			case 18://Hyperbolic Sine
			{
				if (st_ptr>=2)
		  		{
					stack[st_ptr-2]=sinh(stack[st_ptr-1]);
					st_ptr--;
		  		} 
			}
			case 19: //Hyperbolic Cosine
			{
				if (st_ptr>=2)
		  		{
					stack[st_ptr-2]=cosh(stack[st_ptr-1]);
					st_ptr--;
		  		} 
			}
			case 20: //Hyperboline Tangent
			{
				if (st_ptr>=2)
		  		{
					stack[st_ptr-2]=tanh(stack[st_ptr-1]);
					st_ptr--;
		  		} 
			}
		}
	}
	for (i=0; i<arraylen; i++)
	{
		printf(
	}
}
