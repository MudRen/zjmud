// yirong.c ������

inherit SKILL;

void create() { seteuid(getuid()); }

string type() { return "knowledge"; }

int valid_learn(object me)
{
	return 1;
}

int practice_skill(object me)
{
	return notify_fail("������ֻ�ܿ�ѧ(learn)����ߡ�\n");
}


