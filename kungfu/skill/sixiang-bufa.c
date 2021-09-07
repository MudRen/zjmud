// sixiang-bufa.c
// created by doing

inherit SKILL;

string *dodge_msg = ({
    "ֻ��$n�Ų��������ƣ������֮��ܿ���$N��һ�С�\n",
    "$n����ĽȻ���һ�����ܿ���$N���������ơ�\n",
    "$n����΢΢һ�࣬��ǰ��������$N��һ�����˸��ա�\n",
    "����$n����Ʈ��������һ�ݣ����ѱܿ�$N��\n",
    "$n��ǰ����������ת����$N���еĺ���ȫ����ա�\n",
});

int valid_enable(string usage)
{
	return usage == "dodge";
}

int valid_learn(object me)
{
	if (me->query_skill("dodge", 1) < 180)
		return notify_fail("������Ṧˮƽ���㣬�����������󲽷���\n");

	return 1;
}

string query_dodge_msg(string limb)
{
	return dodge_msg[random(sizeof(dodge_msg))];
}

int query_effect_dodge(object attacker, object me)
{
	int lvl;

	lvl = me->query_skill("sixiang-bufa", 1);
	if (lvl < 50)  return 0;
	if (lvl < 100) return 20;
	if (lvl < 150) return 30;
	if (lvl < 200) return 40;
	if (lvl < 250) return 60;
	if (lvl < 300) return 70;
	if (lvl < 350) return 80;
	return 90;
}

int practice_skill(object me)
{
	if ((int)me->query("qi") < 60)
		return notify_fail("�������̫���ˣ����������󲽷���\n");

	me->receive_damage("qi", 55);
	return 1;
}

