#include <stdio.h>				//Berk Limoncu 2243541
#include <stdlib.h>
#include <string.h>

struct Date{
	int day;
	int month;
	int year;
};

struct DogDetails{
	int statusOfDog; // statusOfDog=0 no dog in the cell.--- statusOfDog=1 dog is added. ----- statusOfDog=2 dog is adopted.
	int id;
	char name[30];
	float weight;
	float height;
	struct Date entryDate;
	struct Date leaveDate;
};

struct DogRecord{
	struct DogDetails *dog;
	int N;
	int tableSize;
};

typedef struct DogRecord Dog;

int hash(Dog *d,int);
int addDog(Dog *,struct DogDetails);
Dog reHash(Dog *);
int searchDog(Dog*,int);
void adoptDog(Dog*,int);
int isPrime(int);
int nextPrime(int);
void printDogDetails(Dog);

int main()
{
	int i;
	struct DogDetails tempDog; //For getting input less complicated instead of too much variables.
	
	Dog myDog;
	myDog.dog=(struct DogDetails *)malloc(sizeof(struct DogDetails)*11); //Initialize 
	myDog.tableSize=11;													 //Initialize 
	myDog.N=0;															 //Initialize 
	
	
	for(i=0;i<11;i++)	
		myDog.dog[i].statusOfDog=0;										//Initialize 
	
	int exit=0,choice;
	
	while(!exit)
	{
		printf("\n1.Add a dog\n2.Search for a dog\n3.Adopt for a dog\n4.Print hash table\n5.Exit\n");
		printf("\nEnter:");
		scanf("%d",&choice);
		fflush(stdin);
		
		switch(choice)
		{
			case 1: //Add a Dog.
				printf("Enter unique identifier: ");
				scanf("%d",&tempDog.id);
				fflush(stdin);
	
				printf("Enter name: ");
				gets(tempDog.name);
				fflush(stdin);
		
				printf("Enter weight: ");
				scanf("%f",&tempDog.weight);
				fflush(stdin);
		
				printf("Enter height: ");
				scanf("%f",&tempDog.height);
				fflush(stdin);
		
				printf("Enter entry date: ");
				scanf("%d.%d.%d",&tempDog.entryDate.day,&tempDog.entryDate.month,&tempDog.entryDate.year);
				fflush(stdin);
				
				if(addDog(&myDog,tempDog)==1) //If add function can add any entity.
					printf("%s has been added to the dog shelter\n",tempDog.name);
				break;
			case 2: //Search a Dog with unique id.
				printf("Enter unique identifier: ");
				scanf("%d",&tempDog.id);
				fflush(stdin);
				
				int position=searchDog(&myDog,tempDog.id); 
				
				if(myDog.dog[position].statusOfDog==1) 
				{
					printf("Name: %s\n",myDog.dog[position].name);
					printf("Weight: %.2f\n",myDog.dog[position].weight);
					printf("Height: %.2f\n",myDog.dog[position].height);
					printf("Entry Date: %d.%d.%d\n",myDog.dog[position].entryDate.day,myDog.dog[position].entryDate.month,myDog.dog[position].entryDate.year);
				}
				else
					printf("No dog is found\n");
				break;
			case 3://Adopt for a dog.
				printf("Enter unique identifier: ");
				scanf("%d",&tempDog.id);
				adoptDog(&myDog,tempDog.id);
				break;	
			case 4: //Print dog details.
				printDogDetails(myDog);
				break;
			case 5://Exit case.
				printf("Good Bye!");
				exit=1;
				break;
			default:
				printf("Please enter a valid option!\n");
				break;
		}	
	}
	return 0;
}

int hash(Dog *d,int id) //myHash function 
{
	return id % (d->tableSize);
}

int addDog(Dog *d,struct DogDetails tempDog)
{
	double loadFactor=(d->N+1.0)/(d->tableSize); //loadFactor=N+1/tableSize because I check first then I add , so I have to add 1.
	
	if(loadFactor > 0.5) //When the load capacity is greater than 0.5. That means we have to double the size of the hash table and round the next prime number then assign to new tableSize as nextPrime(2*tableSize).
	{
		*d=reHash(d);//reHashing operation
		addDog(d,tempDog); 
 	}
	else	//When the load capacity is less or equal than 0.5. That means we dont have to rehash the table. We can directly insert the item when the desired location is founded.
	{
		int position=searchDog(d,tempDog.id); //position of the desired input
		
		if(d->dog[position].statusOfDog==0) //If desired cell is empty
		{
			d->dog[position]=tempDog;
			d->dog[position].statusOfDog=1; 
			d->N++;
			return 1; //When the operation of the adding is succesful to do print 112.th line.
		}
		if(d->dog[position].statusOfDog==1 || d->dog[position].statusOfDog==2) //If the desired cell is full
			printf("Id should be unique!\n");
	}
}

Dog reHash(Dog *d)//It takes the old table and returns the new table with size of doubled and rounded to the next prime number
{	
	Dog tempDog;
	int i,newTableSize;
	
	newTableSize=nextPrime(d->tableSize*2); //Round to the next prime.
	
	tempDog.tableSize=newTableSize; //assign to tableSize
	tempDog.dog=(struct DogDetails*)malloc(sizeof(struct DogDetails)*newTableSize); //allocate memory.
		
	if(tempDog.dog==NULL) //In case of allocating problem.
	{
		printf("Failed!\n");
		exit(0);
	}
	else
	{
		for(i=0;i<d->tableSize;i++)
		{
			tempDog.dog[i].statusOfDog=0;
			
			if(d->dog[i].statusOfDog==1 || d->dog[i].statusOfDog==2) 	//If value exist in a spesific cell.
				addDog(&tempDog,d->dog[i]);								//copy old rehashing table to newtable
			
		}
		
		return tempDog; //return the new hashtable with new tablesize and new N
	}
}

int searchDog(Dog *d,int id) //returns the position of the desired dog in table.
{
	int position=hash(d,id);
	int positionOriginal=position; //to store the initial value of the position of the desired item.
	int collisions=0;
	
	while(d->dog[position].statusOfDog!=0 && d->dog[position].id!=id)
	{
		position=positionOriginal;                   
		collisions++;			// it represents # of collision in the hash table
	
		position=position+collisions*collisions;	//quadratic probing equation
		if(position>=d->tableSize)				//If the desired position is greater than the tableSize 
			position=position-d->tableSize;		
	}
	return position;		
}

void adoptDog(Dog *d,int id)
{
	int position=searchDog(d,id);
	
	if(d->dog[position].statusOfDog==0) //If there is no dog with given id.
		printf("No dog is found\n");
	else if(d->dog[position].statusOfDog==2) //In case of dog is already adopted.
		printf("Dog is already adopted!\n");
	else
	{
		printf("Name: %s\n",d->dog[position].name); 		
		printf("Weight: %.2f\n",d->dog[position].weight);
		printf("Height: %.2f\n",d->dog[position].height);
		printf("Entry Date: %d.%d.%d\n",d->dog[position].entryDate.day,d->dog[position].entryDate.month,d->dog[position].entryDate.year);
		printf("Enter leave date: ");
		scanf("%d.%d.%d",&d->dog[position].leaveDate.day,&d->dog[position].leaveDate.month,&d->dog[position].leaveDate.year);
		fflush(stdin);
		
		printf("%s has been adopted.\n",d->dog[position].name);
	}
}

void printDogDetails(Dog myDog)
{
	int i;

	for(i=0;i<myDog.tableSize;i++)
	{
		if(myDog.dog[i].statusOfDog==0) //There is no dog like in the shelter.
			printf("Empty\n");
		else if(myDog.dog[i].statusOfDog==1) //Dog is in the shelter.
			printf("ID:%d Name:%s Weight:%.2f Height:%.2f Entry Date:%d.%d.%d\n",myDog.dog[i].id,myDog.dog[i].name,myDog.dog[i].weight,myDog.dog[i].height,myDog.dog[i].entryDate.day,myDog.dog[i].entryDate.month,myDog.dog[i].entryDate.year);
		else
			printf("ID:%d Name:%s Weight:%.2f Height:%.2f Entry Date:%d.%d.%d Leave Date:%d.%d.%d\n",myDog.dog[i].id,myDog.dog[i].name,myDog.dog[i].weight,myDog.dog[i].height,myDog.dog[i].entryDate.day,myDog.dog[i].entryDate.month,myDog.dog[i].entryDate.year,myDog.dog[i].leaveDate.day,myDog.dog[i].leaveDate.month,myDog.dog[i].leaveDate.year);
	}
}	

int isPrime(int number) 	//Cheks the given number is it prime or not.
{
	int i,flag=1;
	
	if(number==1) //If number is 1 it's definetally not prime.
		return 0;
	for(i=2;i<number;i++)
	{
		if(number%i==0)
		{
			flag=0; //When the breaks the prime condition
			break;
		}
	}
	return flag; //Flag=0 means it's not prime.        Flag=1 means it's prime.
}

int nextPrime(int number) //To round to the next prime number.
{
	int founded=0,i=1;
	
	while(!founded)
	{
		if(isPrime(number+i)==1) //Checks to the number+i is prime or not if it is founded will be 1 then loop terminates and returns number+i
		{
			founded=1;
			break;
		}
		i++;	
	}
	return number+i;
}
