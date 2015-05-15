#include <stdio.h>
#include <stdlib.h>

#define INTEGER_HEAP_STARTING_SIZE 4

struct integer_heap
{
	int * array;
	int arraySize;
	int numberOfElements;
};

struct integer_heap * integer_heap_new()
{
	struct integer_heap * result = malloc(sizeof(struct integer_heap));
	result->array = malloc(sizeof(int) * INTEGER_HEAP_STARTING_SIZE);
	result->arraySize = INTEGER_HEAP_STARTING_SIZE;
	result->numberOfElements = 0;
	return result;
}

void integer_heap_grow(struct integer_heap * this)
{
	int * newArray = malloc(sizeof(int) * this->arraySize * 2);
	int i;
	for(i = 0; i < this->arraySize; i++)
	{
		newArray[i] = this->array[i];
	}
	free(this->array);
	this->array = newArray;
	this->arraySize *= 2;
}

void integer_heap_exchange_elements(struct integer_heap * this, int zero, int one)
{
	int temp = this->array[zero];
	this->array[zero] = this->array[one];
	this->array[one] = temp;
}

void integer_heap_swim(struct integer_heap * this, int currentIndex)
{
	if(this->array[currentIndex/2] < this->array[currentIndex] && currentIndex != 1)
	{
		integer_heap_exchange_elements(this, currentIndex, currentIndex/2);
		integer_heap_swim(this, currentIndex/2);
	}
}
void integer_heap_insert(struct integer_heap * this, int item)
{
	if(this->arraySize - 1 <= this->numberOfElements)
	{
		integer_heap_grow(this);
	}
	this->array[this->numberOfElements + 1] = item;
	this->numberOfElements++;
	integer_heap_swim(this, this->numberOfElements);
}

int integer_heap_get_max(struct integer_heap * this)
{
	return this->array[1];
}

void integer_heap_sink(struct integer_heap * this, int currentIndex)
{
	if(currentIndex * 2 <= this->numberOfElements && 
		this->array[currentIndex] < this->array[currentIndex*2])
	{
		integer_heap_exchange_elements(this, currentIndex, currentIndex * 2);
		integer_heap_sink(this, currentIndex*2);
	}
	else if(currentIndex * 2 + 1 <= this->numberOfElements &&
		this->array[currentIndex] < this->array[currentIndex*2 + 1])
	{
		integer_heap_exchange_elements(this, currentIndex, currentIndex*2 + 1);
		integer_heap_sink(this, currentIndex*2 + 1);
	}
}

int integer_heap_delete_max(struct integer_heap * this)
{
	int result = this->array[1];
	this->array[1] = this->array[this->numberOfElements];
	this->array[this->numberOfElements] = 0;	//prevents loitering in actual abstract implementation
	this->numberOfElements--;
	integer_heap_sink(this, 1);
}

void integer_heap_print(struct integer_heap * this)
{
	int i;
	for(i = 1; i <= this->numberOfElements; i++)
	{
		printf("%d\n", this->array[i]);
	}
}


int main()
{
	struct integer_heap * test = integer_heap_new();
	int i;
	for(i = 10; i >= 0; i--)
	{
		integer_heap_insert(test, i);
	}
	integer_heap_delete_max(test);
	integer_heap_print(test);

	return 0;
}