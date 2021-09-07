// linji-zhuang.c �ټ�ʮ��ׯ

#include <ansi.h>

inherit FORCE;

int valid_enable(string usage) { return usage == "force"; }

int query_neili_improve(object me)
{
	int lvl;
	int scale;

	if (me->query("sex"))
		return 0;

	lvl = (int)me->query_skill("linji-zhuang", 1);
	if (lvl >= 250) scale = 17; else scale = 21;
	return lvl * lvl * 15 * scale / 100 / 200 + 500;
}

int valid_force(string force)
{
	return force == "emei-xinfa";
}

int valid_learn(object me)
{
	int i, np, nf, nh, ns, ts;
	nf = (int)me->query_skill("force", 1);
	nh = (int)me->query_skill("linji-zhuang", 1);
	np = (int)me->query_skill("mahayana", 1);

	if (me->query("gender") != "Ů��")
		return notify_fail("���Ů�ӣ�������ϰ�ټ�ʮ��ׯ��\n");

	if (np <= nh && np < 200)
		return notify_fail("��Ĵ�����͹���Ϊ�������޷�����������ټ�ʮ��ׯ��\n");

	if (nf < 40)
		return notify_fail("��Ļ����ڹ���򻹲������޷�����ټ�ʮ��ׯ��\n");

	return 1;
}

int practice_skill(object me)
{
	return notify_fail("�ټ�ʮ��ׯֻ����ѧ(learn)�������������ȡ�\n");
}

void skill_improved(object me)
{
	switch (me->query_skill("linji-zhuang",1))
	{
	case 30:
		tell_object(me, HIG "���Ѿ������ׯ�����ˣ�"NOR"\n" );
		break;
	case 60:
		tell_object(me, HIG "���Ѿ���֮��ׯ�����ˣ�"NOR"\n" );
		break;
	case 90:
		tell_object(me, HIG "���Ѿ�������ׯ�����ˣ�"NOR"\n" );
		break;
	case 120:
		tell_object(me, HIG "���Ѿ��ѷ���ׯ�����ˣ�"NOR"\n" );
		break;
	case 150:
		tell_object(me, HIG "���Ѿ��Ѵ�Сׯ�����ˣ�"NOR"\n" );
		break;
	case 180:
		tell_object(me, HIG "���Ѿ�����ڤׯ�����ˣ�"NOR"\n" );
		break;
	}
	return;
}

string exert_function_file(string func)
{
	return __DIR__"linji-zhuang/" + func;
}
