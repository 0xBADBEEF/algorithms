#include <time.h>
#include <stdlib.h>

#include <stdio.h>


#define MAX_ELEMENTS 50000000

#define MAX_KEY 0xffffffff


struct hash_el
{
	struct hash_el *next;
	struct hash_el *prev;

	unsigned int key;
	void *data;                     // Replace with actual data
};

struct key_val_t {
	unsigned int key;
	void *data;                     // Replace with actual data
};


static struct hash_el el_storage[MAX_ELEMENTS];
static struct hash_el *start_free;


static void init(void)
{
	struct hash_el *tmp = NULL;

	start_free = el_storage;

	for (int i = 0; i < MAX_ELEMENTS; ++i) {
		el_storage[i].prev = tmp;

		if (tmp)
			tmp->next = &el_storage[i];

		tmp = &el_storage[i];
	}
}

static struct hash_el *get_free(void)
{
	struct hash_el *res = start_free;

	start_free = res->next;

	if (start_free)
		start_free->prev = NULL;

	res->next = NULL;
	res->prev = NULL;

	return res;
}


static void put_free(struct hash_el *el)
{
	el->next = start_free;
	el->prev = NULL;

	if (start_free)
		start_free->prev = el;

	start_free = el;
}





// Hash table implement

static struct hash_el *hash_table[MAX_ELEMENTS];


// Universal hash-func
static int a;
static int b;

static unsigned int hash_func(unsigned int key)
{
	unsigned int hash;

	hash = a * key + b;
	hash = hash % MAX_KEY;
	hash = hash % MAX_ELEMENTS;

	return hash;
}


/*
// Division hash
static unsigned int hash_func(unsigned int key)
{
	return key % MAX_ELEMENTS;
}
*/

/*
// Multiply hash -- IS NOT READY
static float A;

static unsigned int hash_func(unsigned int key)
{
	unsigned int hash;

	hash = (int)(key * A) % 1;
	hash *= MAX_ELEMENTS;

	return hash;
}
*/


static void add_to_hash_table(struct key_val_t *data)
{
	unsigned int hash = hash_func(data->key);
	struct hash_el *new = get_free();
	struct hash_el *tmp = NULL;

	new->key = data->key;
	new->data = data->data;

	if (!hash_table[hash]) {
		hash_table[hash] = new;

		return;
	}

	tmp = hash_table[hash];

	while (tmp) {
		if (!tmp->next)
			break;

		tmp = tmp->next;
	}

	tmp->next = new;
	new->prev = tmp;

}

static void *find_in_hash_table(int key)
{
	unsigned int hash = hash_func(key);
	struct hash_el *tmp;

	tmp = hash_table[hash];
	if (!tmp)
		return NULL;

	if (!tmp->next) {
		if (tmp->key == key)
			return tmp->data;
		else
			return NULL;
	}

	while (tmp) {
		if (tmp->key == key)
			return tmp->data;

		tmp = tmp->next;
	}

	return NULL;
}

static void remove_from_hash_table(int key)
{
	// Search at first
	int hash = hash_func(key);
	struct hash_el *tmp;

	tmp = hash_table[hash];
	if (!tmp)
		return;

	if (!tmp->next) {
		if (tmp->key == key) {
			hash_table[hash] = NULL;
			put_free(tmp);
		}
		return;
	}

	while (tmp) {
		if (tmp->key == key) {

			if (tmp->prev)
				tmp->prev->next = tmp->next;

			if (tmp->next)
				tmp->next->prev = tmp->prev;

			put_free(tmp);

			return;
		}
		tmp = tmp->next;
	}
}



int main(void)
{
//	struct key_val_t key_array[MAX_ELEMENTS];
	int cur_el = 0;
	struct key_val_t tmp_data;
	unsigned long data;

	// Init free list
	init();
	a = 3;
	b = 4;

//	A = 0.618033887;

	srand(time(NULL));

	for (int i = 0; i < MAX_ELEMENTS; i++) {
//		tmp_data.key = rand();
//		tmp_data.data = (void *)rand();
		tmp_data.key = i;
		tmp_data.data = 12;

		if (!find_in_hash_table(tmp_data.key)) {
//			key_array[cur_el].key = tmp_data.key;
//			key_array[cur_el].data = tmp_data.data;
			cur_el++;

			add_to_hash_table(&tmp_data);
		}
	}

/*
	for (int i = 0; i < cur_el; i++) {
		data = (unsigned long)find_in_hash_table(key_array[i].key);

		if (data != (unsigned long)key_array[i].data)
			printf("Error! Stored <%lu> returned <%lu>\n", (unsigned long)key_array[i].data, data);
	}

	for (int i = 0; i < 10; i++) {
		remove_from_hash_table(key_array[cur_el].key);
		cur_el--;
	}
*/

	return 0;
}
