// ding-force.c С������

inherit FORCE;

int valid_enable(string usage) { return usage == "force"; }

int valid_learn(object me)
{
	return ::valid_learn(me);
}

int practice_skill(object me)
{
	return notify_fail("С������ֻ�ܸ�С��ѧ�����������ȡ�\n");
}


