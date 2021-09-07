// hengshan-jian.c ��ɽ����
// Modified by Java Sep.1998

#include <ansi.h>
inherit SKILL;

mapping *action = ({
([      "action" : "$N����$w�����˸���Ȧ��бб��$n$l��ȥ",
	"force"  : 120,
	"dodge"  : 40,
	"damage" : 20,
	"lvl"    : 0,
	"damage_type" : "����",
]),

([      "action" : "$NͻȻ�佫$w�����֣����ִ̳�",
	"force"  : 140,
	"dodge"  : 35,
	"damage" : 25,
	"lvl"    : 30,
	"damage_type" : "����",
]),
});


int valid_enable(string usage) { return usage == "sword" || usage == "parry"; }

int valid_learn(object me)
{
	if ((int)me->query("max_neili") < 150)
		return notify_fail(HIC"�������������"NOR"\n");

	if ((int)me->query_skill("force") < 30)
		return notify_fail(HIC"����ڹ���򲻹���"NOR"\n");

	return 1;
}

mapping query_action(object me, object weapon)
{
	int i, level;
	level = (int) me->query_skill("hengshan-jian", 1);
	for (i = sizeof(action); i > 0; i--)
		if (level > action[i - 1]["lvl"])
			return action[NewRandom(i, 20, level / 5)];
}

int practice_skill(object me)
{
	object weapon;

	if (! objectp(weapon = me->query_temp("weapon")) ||
	    (string)weapon->query("skill_type") != "sword")
		return notify_fail("��ʹ�õ��������ԡ�\n");

	if ((int)me->query("qi") < 40)
		return notify_fail("���������������ɽ������\n");

	if ((int)me->query("neili") < 40)
		return notify_fail("���������������ɽ������\n");

	me->receive_damage("qi", 25);
	me->add("neili", -14);
	return 1;
}

string perform_action_file(string action)
{
	return __DIR__"hengshan-jian/" + action;
}
