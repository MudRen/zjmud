// xiaowuxiang.c С���๦
// by secret
// 1997-1-16
//

inherit FORCE;

int valid_enable(string usage) { return usage == "force"; }

int valid_force(string force)
{
	return force == "xiaoyao-xinfa" ||
	       force == "beiming-shengong" ||
	       force == "mizong-neigong" ||
	       force == "longxiang";
}

int query_neili_improve(object me)
{
    	int lvl;

    	lvl = (int)me->query_skill("xiaowuxiang", 1);
    	return lvl * lvl * 15 * 11 / 100 / 200;
}

int valid_learn(object me)
{
	if ((int)me->query_skill("force", 1) < 80)
		return notify_fail("��Ļ����ڹ�����㣬����ѧС���๦��\n");

	if (me->query("gender") == "����" &&
	(int)me->query_skill("xiaowuxiang", 1) > 49)
		return notify_fail("���޸����ԣ����������������������С���๦��\n");

	return ::valid_learn(me);
}

int practice_skill(object me)
{
	return notify_fail("С���๦ֻ����ѧ(learn)�������������ȡ�\n");
}

string exert_function_file(string func)
{
	return __DIR__"xiaowuxiang/" + func;
}

int difficult_level()
{
	object me;
	int lvl;

	if (me = this_player())
	{
		// �����������������ѧϰ��
		if (lvl = me->query_skill("longxiang", 1))
			return 3000;

	}

	return 100;
}
