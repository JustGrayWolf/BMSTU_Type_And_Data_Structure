#ifndef CHECK

#define CHECK

void sort1 (int keys[ARR_LEN][2], int count);

void sort_array_qs(struct performance *array, int first, int last);

void sort_array_sort1 (struct performance *array, int count);

void search(struct performance *array, int count);

void qs(int keys[ARR_LEN][2], int first, int last);

unsigned long long tick(void);

void time_sort_keys( struct performance *array, int keys[ARR_LEN][2], int count);

void time_sort_array( struct performance *array, int keys[ARR_LEN][2], int count);

#endif