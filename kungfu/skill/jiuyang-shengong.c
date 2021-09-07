// jiuyang-shengong.c ������
// cleansword
// Modified by Venus Oct.1997
// Updated by Doing Lu for Hell

inherit FORCE;

int valid_enable(string usage)
{
	return usage == "force";
}

int query_neili_improve(object me)
{
	int lvl;

	lvl = (int)me->query_skill("jiuyang-shengong", 1);
	return lvl * lvl * 15 * 22 / 100 / 200;
}

int valid_force(string force)
{
	return 1;
}

int valid_learn(object me)
{
	int lvl = (int)me->query_skill("jiuyang-shengong", 1);

	if (me->query("gender") == "����" && (int)me->query_skill("jiuyang-shengong", 1) > 49)
		return notify_fail("���޸����ԣ���������������������ľ����񹦡�\n");

	if ((int)me->query_skill("force", 1) < 100)
		return notify_fail("��Ļ����ڹ���򻹲�����������ѧϰ�����񹦡�\n");

	if (me->query("int") < 25)
		return notify_fail("����þ����񹦹��ڼ��������⡣\n");

	if (me->query("con") < 29)
		return notify_fail("��ĸ��ǲ��ã�������ת�����񹦡�\n");

	return ::valid_learn(me);
}

int practice_skill(object me)
{
	return notify_fail("������ֻ����ѧ(learn)�������������ȡ�\n");
}

string exert_function_file(string func)
{
	return __DIR__"jiuyang-shengong/" + func;
}

