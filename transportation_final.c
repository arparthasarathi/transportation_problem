	#include<stdio.h>
	#include<math.h>
	
void direction(int m_row,int m_col,int i_row,int i_col)
{
if(m_row<i_row)
{
	if(m_col<i_col)
		printf("South East");
	else if(m_col>i_col)
		printf("South West");
	else
		printf("South");
}

else if(m_row>i_row)
{
	if(m_col<i_col)
		printf("North East");
	else if(m_col>i_col)
		printf("North West");
	else
		printf("North");
}

else
{
	if(m_col<i_col)
		printf("East");
	else if(m_col>i_col)
		printf("West");
	else
		printf("Center");
}
}
		
int det(int n,int mat[10][10])
{
  int submat[10][10]; int i,j,c,subi,subj,d=0;
if(n==2) return( (mat[0][0]*mat[1][1])-(mat[1][0]*mat[0][1]));
else
{  for(c=0;c<n;c++)
   {  subi=0;   //submatrix's i value
      for(i=1;i<n;i++)
          {  subj=0;
             for(j=0;j<n;j++)
                    {if(j==c)
                      continue;
                     submat[subi][subj]=mat[i][j];
                     subj++;
                     }
              subi++;
   
            }
      d=d+(c^-1)*mat[0][c]*det(n-1 ,submat);
    }
}
return d;
}

void show_data(int allocated_matrix[10][10], int cost_matrix[10][10],int distance_matrix[10][10],int number_demand,int number_supply)
{
    int i,j;
    printf("\nAllocated Matrix:\n");//prints allocated matrix
    for ( i=0; i<number_supply; i++ ) 
    {
       for ( j=0;j<number_demand; j++)
        {
            printf("%d\t",allocated_matrix[i][j]);
        }
        printf("\n");
    }

    printf("\nCost Matrix:\n");//prints cost matrix
    for ( i=0; i<number_supply; i++ ) 
    {
       for ( j=0;j<number_demand; j++)
        {
            printf("%d\t",cost_matrix[i][j]);
        }
        printf("\n");
    }
    
    printf("\nDistance Matrix:\n");//prints distance matrix
    for ( i=0; i<number_supply; i++ ) 
    {
       for ( j=0;j<number_demand; j++)
        {
            printf("%d\t",distance_matrix[i][j]);
        }
        printf("\n");
    }
}

void leastcost_allocation ( int allocated_matrix[10][10],int cost_matrix[10][10], int demand_array[10], int supply_array[10], int number_demand , int number_supply, int total_supply )
// Function to allocate the supplies to the demand 
{
    int i,j;
    int min; // variable to hold the minimum cost value
    int total_allocated = 0; // varaible to hold the total_allocated resources
    while ( total_allocated != total_supply  ) // loop to allocated all the available resources
    {
    	
    	min = 255; // initialising min variable to the maximum int value
        int temp_row,temp_col; // variables to store the index value of minimum cost value 
        for (i=0; i<number_supply; i++ ) // loop to find the min cost in the cost matrix
        {
            for (j=0;j<number_demand; j++)
            {
                if( allocated_matrix[i][j] == 0)
                {
                    if(min>cost_matrix[i][j])
                    {
                    	
                    	
                        min=cost_matrix[i][j];
                        temp_row=i;
                        temp_col=j;
                    	
                    }
                }
            }
        }
        
        
        if(supply_array[temp_row]>demand_array[temp_col])//if the demand is greater than supply,allocate the whole supply qunatity
        {
            allocated_matrix[temp_row][temp_col]=demand_array[temp_col];//allocate the resources
            supply_array[temp_row]=supply_array[temp_row]-demand_array[temp_col];//calculate the remaining demand and save
            total_allocated+=demand_array[temp_col]; //add the total allocation 
            demand_array[temp_col]=0;//
           
    	}
        else // if supply is greater than or equal to demand
        {
            allocated_matrix[temp_row][temp_col]= supply_array[temp_row];
            demand_array[temp_col]=demand_array[temp_col]-supply_array[temp_row];
            total_allocated+= supply_array[temp_row];
            supply_array[temp_row]=0;
            
        }
        
        printf("\n\nAllcated matrix:\n\n");
        for(i=0;i<number_supply;i++)
        {
        	for(j=0;j<number_demand;j++)
       		printf("%d\t",allocated_matrix[i][j]);
       	  printf("\n");
       	}
   		
   		
   		
   	 // end of while loop
	   	if(demand_array[temp_col]==0)
        {
        for(i=0;i<number_supply;i++)
            {
 			if(i==temp_row || allocated_matrix[i][temp_col]>0) continue;	        
            allocated_matrix[i][temp_col]=-1;
        	}
        }       
        
		else if(supply_array[temp_row]==0)
        {
            for(j=0;j<number_demand;j++)
            {
            if(j==temp_col || allocated_matrix[temp_row][j]>0) continue;
            allocated_matrix[temp_row][j]=-1;
        	}
        }
    }
} // end of function        
                
void optimal_calculation(int allocated_matrix[10][10], int cost_matrix[10][10], int distance_matrix[10][10], int u[10] , int v[10] , int number_demand, int number_supply)
{
    u[0]=0;

    int i,j,temp_row,temp_col,m,n;
    int node1=0,node2=0,node3=0;//variables to store theta values
    int index_row=-1,index_col=-1;//variable to store index values of theta values
    int count=0,variable[6]; // to keep the count of number of equations to compute u(i) and v(j)
 	temp_row=0;
 	temp_col=0;
 	int d=0;
 	int temp[10][10],uv_mat[10][10],constant[10],uv[10][10];
 int mid_row,mid_col;
    mid_col = (((number_demand)*(number_demand-1))/2)/(number_demand-1);
   mid_row = (((number_supply)*(number_supply-1))/2)/(number_supply-1);
   
 	
	for (i=0; i<(number_demand+number_supply)-1; i++ ) 
    {
       for (j=0;j<(number_demand+number_supply); j++)
        {
           uv_mat[i][j]=0;
        }
      
    }
    
    
	for(i=0;i<(number_demand+number_supply)-1;i++)
    variable[i]=0;
   
    
    
 	for(i=0;i<number_supply;i++)
	{
		for(j=0;j<number_demand;j++)
		{
			if(allocated_matrix[i][j]>0)
			{
			uv_mat[count][i]=1;
			uv_mat[count][number_supply+j]=1;
			constant[count++]=cost_matrix[i][j];	
			}
		}
	}

	

	for (i=0; i<(number_demand+number_supply)-1; i++ ) 
    {
       for (j=0;j<(number_demand+number_supply)-1; j++)
        {
           uv[i][j]=uv_mat[i][j+1];
        }
    }

	
      
    
	d=det((number_demand+number_supply)-1,uv);
    
	
    for(i=0;i<(number_demand+number_supply)-1;i++)
	{
		
		for (m=0; m<(number_demand+number_supply)-1; m++ ) 
    	{
       		for (n=0;n<(number_demand+number_supply)-1; n++)
        	{
        	temp[m][n]=uv[m][n];
        	}
        }   
			
		     
		for(j=0;j<(number_demand+number_supply)-1;j++)
		{
			temp[j][i]=constant[j];		
		}
		
	
			
	 
		
	
    	variable[i]=det(((number_demand+number_supply)-1),temp)/d;
		
	}

	

	
	for(i=0;i<number_supply;i++)
	u[i+1]=variable[i];
	
	for(j=0;j<number_demand ;j++)
	v[j]=variable[(number_supply)+j-1]; 
	
	u[0]=0;
 
    count = 0; // reassign count variable to 0
    
    for ( i=0;i<number_supply;i++)//loop to assign the distance matrix
    {
        for(j=0;j<number_demand;j++)
        {
            distance_matrix[i][j]=cost_matrix[i][j] - (u[i]+v[j]);// accords the formula d(i)(j)=cost(i)(j)-(u(i)+v(j))
            if(distance_matrix[i][j]<0)
            count++; // counts the number of negative values in distance matrix
        }
    }
    
    printf("\n\nDistance Matrix:\n");//prints distance matrix
    
    for ( i=0; i<number_supply; i++ ) 
    {
       for ( j=0;j<number_demand; j++)
        {
            printf("%d\t",distance_matrix[i][j]);
        }
        printf("\n");
    }
    
    printf("\n\n\nU and V values:\n\n");
    
    for(i=0;i<number_supply;i++)
    printf("u[%d]:\t%d",i,u[i]);
    printf("\n");
    for(i=0;i<number_demand;i++)
    printf("v[%d]:\t%d",i,v[i]);
    printf("\n");
    if(count==0)
    printf("\nThe present cost is the most optimal\n");
    
    else
    {
    printf("\nOptimality algorithm comes into scene:\n");
    {
    while(count>0)//loop to make the distance positive & reallocate resources
    {
        int min=255;
        index_row=-1;
        node1=0;node2=0;node3=0;
        for(i=0;i<number_supply;i++)
        {
           for(j=0;j<number_demand;j++)
           {
               if(distance_matrix[i][j]<0 && min>distance_matrix[i][j])
               {
               min=distance_matrix[i][j];
               temp_row=i;
               temp_col=j;
               }
            }
        }
        
       

        
        for(i=0;i<number_supply;i++)// loop to trace the 'd' matrix and allocated matrix to assign -ve & +ve theta values
        {
        	
            for(j=0;j<number_demand;j++)
            {
            
                if(allocated_matrix[i][j]>0 && j==temp_col)// compute -ve theta and its index
                {
                    node1=allocated_matrix[i][j];
                    index_row=i;    
                }
                if(index_row>-1) 
				{
				break;
				}
               
            }
        
    	}
        for(j=0;j<number_demand;j++)
        {
        	if(allocated_matrix[index_row][j]>0 && j!=temp_col)
            	{
             		node2=allocated_matrix[index_row][j];
               		index_col=j;
		
  		
                }
                	
            if(allocated_matrix[temp_row][index_col]>0 && index_col!=temp_col)
            	{
                	node3=allocated_matrix[temp_row][index_col];
                }
        }

                	
        
        if(node1==0 || node2==0 || node3==0 )
          return; //while trcing if we reach last node without finding the theta values reassign i and j value
	
	
        printf("\nNode 1 is present ");direction(mid_row,mid_col,temp_row,temp_col); printf(" to the center of matrix");
	printf("\nNode 2 is present ");direction(mid_row,mid_col,index_row,temp_col);printf(" to the center of matrix");
	printf("\nNode 3 is present "); direction(mid_row,mid_col,index_row,index_col);printf(" to the center of matrix");
	printf("\nNode 4 is present "); direction(mid_row,mid_col,temp_row,index_col);printf(" to the center of matrix");

	        
        int min_node;//variable to hold min of negative theta values
        if(node1<node3) min_node= node1;
        else min_node=node3;
                
        distance_matrix[temp_row][temp_col]=min_node;//reassign negative 'd' 
        allocated_matrix[temp_row][temp_col]=min_node;
        allocated_matrix[index_row][temp_col]-=min_node;
        allocated_matrix[index_row][index_col]+=min_node;
        allocated_matrix[temp_row][index_col]-=min_node;
        //respective allocated resources are reassigned for
                
         count--;
         printf("\n\nDistance Matrix:\n");//prints distance matrix
         
    	for (i=0; i<number_supply; i++ ) 
    	{
       		for ( j=0;j<number_demand; j++)
        	{
            printf("%d\t",distance_matrix[i][j]);
        	}
       	 printf("\n");
    	}  
     
   		
        //end of loop to trace the distance matrix    
	}
    }
	}//e}nd of loop to reassign negative d values      
    
} //end of function 

void cost_calculation(int allocated_matrix[10][10], int cost_matrix[10][10], int number_demand, int number_supply)
{
    int cost=0;//variable to store the cost
    int i,j;
    for (i=0;i<number_supply;i++)
    {
        for(j=0;j<number_demand;j++)
        {
            if(allocated_matrix[i][j]>0)//caluculate the cost only if allocation of resources is positive  
            cost+=(allocated_matrix[i][j]*cost_matrix[i][j]);
        }
    }        
                
   printf("\t%d",cost);
}
             
void feed_data(int allocated_matrix[10][10],int cost_matrix[10][10], int u[10], int v[10], int distance_matrix[10][10], int demand_array[10], int supply_array[10], int number_demand, int number_supply)
//funtion to initialise the respective matrices and values
{
    	
int a[100];
int c[100];//,supply_array[10],demand_array[10]; 
int adj[100],adj_mat[3][4];
FILE *file1,*file2,*file3;
int i,j,k;//,adjacency_matrix[3][4];

i=j=k=0;
for(i=0;i<100;i++)
{
a[i]=0;
c[i]=0;
adj[i]=0;
}
i=0;
file1 = fopen("weight.txt", "r");
file2 = fopen("nodes.txt", "r");
file3=fopen("adjacency.txt","r");

if (file1){
while (!feof(file1))
fscanf(file1,"%d",&a[i++]);    
}
i=0;
if (file2){

while (!feof(file2))
fscanf(file2,"%d",&c[i++]);    

}

i=0;
if(file3)
{

while(!feof(file3))
{
fscanf(file3,"%d",&adj[i++]);
}
}

k=0;
for(i=0;i<number_supply;i++)
{
for(j=0;j<number_demand;j++)
{
adj_mat[i][j]=adj[k++];
}

}
k=0;
for(i=0;i<number_supply;i++)
{
  for(j=0;j<number_demand;j++)     
	 cost_matrix[i][j]=a[k++];
}
k=0;

for(i=0;i<number_supply;i++)
 {
  for(j=0;j<number_demand;j++)    
{
	if(adj_mat[i][j]==0)
	{ 
	 cost_matrix[i][j]=0;
	}	
}}

k=0;
for(i=0,j=0;i<number_supply||j<number_demand;i++,j++)
{
if(i<number_supply)
supply_array[i]=c[k++];
if(j<number_demand)
demand_array[j]=c[k++];
}






printf("\nCost Matrix\n");
for(i=0;i<number_supply;i++)
{
for(j=0;j<number_demand;j++)
printf("%d\t",cost_matrix[i][j]);
printf("\n");
}



fclose(file1);
fclose(file2);
fclose(file3); 
}


int main()
{
    
	int number_demand,number_supply,total_demand,total_supply; 
	// variable to store number of demand and supply points
    printf("\nEnter the number of supply points:\t");
    scanf("%d",&number_supply);
    printf("\nEnter the number of demand points:\t");
    scanf("%d",&number_demand);
    
	int i,j;
    int demand_array[10];//to store the demands for each node
    int supply_array[10];//to store the supplies from each node
    int cost_matrix[10][10];//to store the cost matrix
    int allocated_matrix[10][10];//to store the allocated resources
    int distance_matrix[10][10]			;//to store the distance 
    int u[10],v[10];//to store u(i) and v(j)
    total_demand=0;
    total_supply=0;

    for(i=0;i<=9;i++)
	{
		u[i]=-1;
		v[i]=-1;
		for(j=0;j<=9;j++)
		{

			allocated_matrix[i][j]=0;
			distance_matrix[i][j]=0;
		}
	}
    
    feed_data(allocated_matrix,cost_matrix,u,v,distance_matrix,demand_array,supply_array,number_demand,number_supply) ; //give inputs
	printf("\nMatrices after feeding the data:\n");    
	for(i=0;i<number_demand;i++)
            total_demand+=demand_array[i];
    	for(j=0;j<number_supply;j++)
            total_supply+=supply_array[j];
    

    show_data(allocated_matrix,cost_matrix,distance_matrix,number_demand,number_supply);

    /*balancing(cost_matrix,demand_array,supply_array,number_demand,number_supply,total_demand,total_supply);//Balance to get feasible solutin*/
    if(total_demand!=total_supply)
    {
        printf("\nUnbalanced Situation:");
        if(total_demand<total_supply)//demand is less than supply
        {
            number_demand++;//add a dummy column
            for(i=0;i<number_supply;i++)
            cost_matrix[i][number_demand-1]=0;//dummy column is equated to 0
            demand_array[number_demand-1]=total_supply-total_demand;//equate the remaining supply to the demand
            total_demand=total_supply;
        }
        else //supply is less than demand
        {
            number_supply++;//add a dummy row
            for(i=0;i<number_demand;i++)
            cost_matrix[number_supply-1][i]=0;//dummy row is equated to 0
            supply_array[number_supply-1]=total_demand-total_supply;//equate the remaining demand to supply
            total_supply=total_demand;
        } 
    }
    
	else
    printf("\nBalanced Situation");
    
	
   	printf("\nMatrices after Balancing:\n");
    show_data(allocated_matrix,cost_matrix,distance_matrix,number_demand,number_supply); 
  	
	printf("\nMatrices after allocating the resources:\n");
  	leastcost_allocation(allocated_matrix,cost_matrix,demand_array,supply_array,number_demand,number_supply,total_supply ) ;//allocate based on least cost algo
    show_data(allocated_matrix,cost_matrix,distance_matrix,number_demand,number_supply);
    
	printf("\n Cost after balncing:\t");
	cost_calculation(allocated_matrix,cost_matrix,number_demand,number_supply);//display the cost
    optimal_calculation(allocated_matrix,cost_matrix,distance_matrix,u,v,number_demand,number_supply);//calculate the most optimal cost
    
	printf("\nMatrices after removing negative values:\n");
    show_data(allocated_matrix,cost_matrix,distance_matrix,number_demand,number_supply);
    
	printf("\n Optimal Cost:\t");
	cost_calculation(allocated_matrix,cost_matrix,number_demand		,number_supply);//print the most optimal cost    	

}
    
                
                
                
                
                
                
                
               
                
                
