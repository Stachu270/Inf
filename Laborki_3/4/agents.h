struct agent
{
	int x, y;
};

struct agent newagent(int x, int y);
void north(struct agent *ptr);
void south(struct agent *ptr);
void east(struct agent *ptr);
void west(struct agent *ptr);
double distance(struct agent ob1, struct agent ob2);