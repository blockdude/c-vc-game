struct item
{
	int x;
	int y;
};

struct item a = {
	.x = 100,
	.y = 200
};

const struct item *b = &a;

const struct item *get()
{
	return &a;
}

int main( void )
{
	a.x = 12123;
	b->x = 100;
	return 0;
}
