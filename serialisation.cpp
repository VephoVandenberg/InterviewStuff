#include <iostream>

struct ListNode {
     ListNode *      prev;
     ListNode *      next;
     ListNode *      rand;
     std::string     data;
};

class List {
public:
    void set(ListNode *first, ListNode *last, int number);
    void Serialize   (FILE * file);  // сохранение в файл (файл открыт с помощью fopen(path, "wb"))
    void Deserialize (FILE * file);  // загрузка из файла (файл открыт с помощью fopen(path, "rb"))

private:
     ListNode *      head;
     ListNode *      tail;
     int       count;
};


void List::set(ListNode *first, ListNode *last, int number)
{
    head = first;
    tail = last;
    count = number;
}

void List::Serialize(FILE *file)
{
    
    if (file)
    {
	ListNode *temp_node = head;
	int random_index;
	
	// First we write the total of number of nodes
	fwrite(&count, sizeof(int), 1, file);
	
	while (temp_node)
	{
	    // if  temp_node->rand is NULL then we write -1
	    if (!temp_node->rand)
	    {
		random_index = -1;
		
	    }
	    else
	    {
		// Here we try to find the index of random node
		ListNode *node = this->head;

		random_index = 0;
		while (node) 
		{
		    // if we found the random node just break the loop
		    if (node->prev == temp_node->rand->prev &&
			node->next == temp_node->rand->next &&
			node->data == temp_node->rand->data)
		    {
			break;
		    }
		    node = node->next;
		    random_index++;
		}
	    }


	    // The only thing we really care about is the random node and data
	    // beacuse we can easily determine what is next node and what is
	    // previous node
	    size_t length = temp_node->data.length(); 
	    
	    fwrite(&random_index, sizeof(int), 1, file);
	    fwrite(&length, sizeof(size_t), 1, file);

	    char *string = (char *)malloc(temp_node->data.length());
	    strcpy(string, temp_node->data.c_str());	    
	    fwrite(string, sizeof(char), temp_node->data.length(), file);

	    temp_node = temp_node->next;
	}

	fclose(file);
    }
}

void List::Deserialize(FILE *file)
{
    if (file)
    {	
	fread(&count, sizeof(int), 1, file);
	int *random_indexies = new int[count];
	int indexies_counter;
	
	if (!head)
	{
	    head = new ListNode;
	}

	ListNode *node = head;
	node->next = NULL;
	node->prev = NULL;
	indexies_counter = 0;
	while (fread(&random_indexies[indexies_counter++], sizeof(int), 1, file))
	{
	    size_t string_length;
	    fread(&string_length, sizeof(size_t), 1, file);
	    char *string = new char[string_length];
	    fread(string, sizeof(char), string_length, file);
	    string[string_length] = '\0';

	    node->data = std::string(string);
	    
	    node->next = new ListNode;	    
	    node->prev = new ListNode;
		
	    ListNode *prev_node = node;
	    node = node->next;
	    prev_node->next = node;
	    node->prev = prev_node;	    
	}      
	tail = node;
	tail->next = NULL;

	node = head;
	for (indexies_counter = 0; indexies_counter < count; indexies_counter++)
	{
	    ListNode *temp_node = head;
	    if (random_indexies[indexies_counter] != -1)
	    {
		int final_index;
		for (final_index = 0; temp_node; final_index++)
		{
		    if (final_index == random_indexies[indexies_counter])
		    {
			node->rand = temp_node;
		    }
		    temp_node = temp_node->next;
		}
	    }
	    else
	    {
		node->rand = NULL;
	    }
	    node = node->next;	    
	}

	free(random_indexies);
	fclose(file);
    }
}

struct point
{
    int x, y;
    point *next;
};


int main(int argc, char **argv)
{
/*
    List list;
    FILE *file = fopen("simple.bin", "wb");
    
    ListNode first;
    ListNode second;
    ListNode third;
    ListNode fourth;

    first.data = "AB";
    second.data = "CD";
    third.data = "EF";
    fourth.data = "GH";

    first.next = &second;
    first.rand = NULL;

    second.next = &third;
    second.prev = &first;
    second.rand = &third;
    
    third.next = &fourth;
    third.prev = &second;
    third.rand = &fourth;

    fourth.prev = &third;
    fourth.next = NULL;

    list.set(&first, &fourth, 4);
    list.Serialize(file);
    fclose(file);
    

    file = fopen("simple.bin", "rb");
    List desirialized;  
    desirialized.Deserialize(file);
    fclose(file);
*/

    std::string first_string = "Hello";
    std::string second_string;

    FILE *file = fopen("simple.bin", "wb");
    fwrite(&first_string, sizeof(char), first_string.length(), file);
    fclose(file);

    file = fopen("simple.bin", "rb");
    fread(&second_string, sizeof(char), first_string.length(), file);
    fclose(file);

    std::cout << second_string << std::endl;
/*
    ListNode* node = new ListNode;
	
    char* string = (char*)malloc(4);
    string = "hell";


    std::string another_one = std::string("asejflsdkfae");
    node->data = std::string(string);
*/
    return 0;
}
