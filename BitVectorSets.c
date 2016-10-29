#include <stdio.h>
#include <stdlib.h>

struct bitset * bitset_new(int size);
int bitset_lookup(struct bitset * this, int item);
int bitset_add(struct bitset * this, int item);
int bitset_remove(struct bitset * this, int item);
void bitset_union(struct bitset * dest, struct bitset * src1, struct bitset * src2);
void bitset_intersect(struct bitset * dest, struct bitset * src1, struct bitset * src2);

const int MAX_STRING = 256;
const int INT_BITS = 32;

char firstLine[MAX_STRING];
char secondLine[MAX_STRING];

struct bitset
{
	int setSize;
	int * bitVector;
};

int main()
{
	printf("Please enter a line of text: ");
	fgets(firstLine, MAX_STRING, stdin);

	printf("Please enter a second line of text: ");
	fgets(secondLine, MAX_STRING, stdin);

	struct bitset *b1 = bitset_new(MAX_STRING);
	struct bitset *b2 = bitset_new(MAX_STRING);

	int index = 0;

	while (firstLine[index] != '\0')
	{
		int itemOne = (int) firstLine[index];
				
		bitset_add(b1, itemOne);
		
		index++;
	}

	index = 0;

	while (secondLine[index] != '\0')
	{
		int itemTwo = (int) secondLine[index];
		
		bitset_add(b2, itemTwo);
		
		index++;
	}

	printf("\nSet of characters in the first String: ");

	for (index = 0; index < MAX_STRING; index++)
	{
		if (bitset_lookup(b1, index))
		{
			char charOne = (char) index;
			printf("%c", charOne);
		}
	}

	printf("\n\nSet of characters in the second String: ");

	for (index = 0; index < MAX_STRING; index++)
	{
		if (bitset_lookup(b2, index))
		{
			char charTwo = (char) index;
			printf("%c", charTwo);
		}
	}

	struct bitset *setUnion = bitset_new(MAX_STRING);
	
	bitset_union(setUnion, b1, b2);

	struct bitset *setIntersection = bitset_new(MAX_STRING);

	bitset_intersect(setIntersection, b1, b2);

	printf("\n\nUnion of sets: ");

	for (index = 0; index < MAX_STRING; index++)
	{
		if (bitset_lookup(setUnion, index))
		{
			char unionChar = (char) index;
			printf("%c", unionChar);
		}
	}
	
	printf("\n\nIntersection of sets: ");

	for (index = 0; index < MAX_STRING; index++)
	{	
		if (bitset_lookup(setIntersection, index))
		{
			char intersectionChar = (char) index;
			printf("%c", intersectionChar);
		}
	}
	
	printf("\n\n");

	free(b1 -> bitVector);
	free(b1);

	free(b2 -> bitVector);
	free(b2);

	free(setUnion -> bitVector);
	free(setUnion);

	free(setIntersection -> bitVector);
	free(setIntersection);
}

struct bitset * bitset_new(int size)
{
	struct bitset *b;
	
	b = malloc(sizeof(struct bitset));

	b -> setSize = (size / INT_BITS);
	b -> bitVector = calloc((b -> setSize), sizeof(int));

	return b;
}

int bitset_lookup(struct bitset * this, int item)
{
	if (item >= 0 && item < (this -> setSize) * INT_BITS)
	{
		int index = item / INT_BITS;
		int shift = item;

		while (shift > INT_BITS)
		{
			shift = shift - INT_BITS;
		}

		int bitVectorMask = 0 | (1 << (INT_BITS - shift));

		int maskingResult = bitVectorMask & (this -> bitVector[index]);

		maskingResult = maskingResult >> (INT_BITS - shift);

		return maskingResult;
	}
	else
	{
		return -1;
	}
}

int bitset_add(struct bitset * this, int item)
{
	if (item >= 0 && item < (this -> setSize) * INT_BITS)
	{
		int index = item / INT_BITS;
		int shift = item;

		while (shift > INT_BITS)
		{
			shift = shift - INT_BITS;
		}
		
		int bitVectorMask = 0 | (1 << (INT_BITS-shift));	
		
		this -> bitVector[index] = (this -> bitVector[index]) | bitVectorMask;

		return 1;
	}
	else
	{
		return 0;
	}
}

int bitset_remove(struct bitset * this, int item)
{
	if (item >= 0 && item < (this -> setSize))
	{
		int index = item / INT_BITS;
		int shift = item;

		while (shift > INT_BITS)
		{
			shift = shift - INT_BITS;
		}

		int bitVectorMask = ~(0 & 0);
		bitVectorMask = bitVectorMask & ~(1 << (INT_BITS-shift));

		this -> bitVector[item] = (this -> bitVector[item]) & bitVectorMask;

		return 1;
	}
	else
	{
		return 0;
	}
}

void bitset_union(struct bitset * dest, struct bitset * src1, struct bitset * src2)
{
	int item;

	for (item = 0; item < MAX_STRING; item++)
	{
		if (bitset_lookup(src1, item) || bitset_lookup(src2, item))
		{
			bitset_add(dest, item);
		}
	}
}

void bitset_intersect(struct bitset * dest, struct bitset * src1, struct bitset * src2)
{
	int item;

	for (item = 0; item < MAX_STRING; item++)
	{
		if (bitset_lookup(src1, item) && bitset_lookup(src2, item))
		{
			bitset_add(dest, item);
		}
	}
}

