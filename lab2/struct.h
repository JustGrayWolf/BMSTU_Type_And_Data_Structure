#ifndef MY_STRUCT
#define MY_STRUCT
#define THEATER 70
#define NAME_LEN 80
#define ARR_LEN 350

struct performance 
{
	char theater[THEATER + 1];
	char perf_name[NAME_LEN + 1];
	char director[NAME_LEN+1];
	int low_prise;
	int high_prise;
	int type_spc;
	union 
	{
		struct v1
		{
			int age;
			int type;
		} child;
		
		struct v2
		{
			int type;
		} adult;
		
		struct v3
		{
			char composer[NAME_LEN + 1];
			char country[THEATER + 1];
			int age;
			int duration;
		} musical;
	} spct;
};

void fill_keys(int keys[ARR_LEN][2], struct performance *array, int count);

void print_keys(int keys[ARR_LEN][2], int count);

void add_struct(struct performance *array, int i);

void remove_struct(struct performance *array, int *count);

void print_array_by_keys(struct performance *array, int keys[ARR_LEN][2], int count);

void print_string(struct performance *array);

void print(struct performance *array, int count);

int read_line(char *s, int n);

int read_int(int *a);

void fill_file(struct performance *array, int *count);

void fill_manually(struct performance *array, int *count);

#endif
