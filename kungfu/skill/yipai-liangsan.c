// yipai-liangsan.c

#include <ansi.h>

inherit SHAOLIN_SKILL;

mapping *action = ({
([      "action": "$Nһ������$n��û��ʲô�·�",
	"force" : 100,
	"attack": -50,
	"dodge" : -50,
	"parry" : -50,
	"damage": -50,
	"lvl"   : 0,
	"damage_type" : "����"
]),
([      "action": "$N��������һ������˫�ƻ���һ��Ȧ�ӣ���������$n������������ɽ����һ��",
	"force" : 700,
	"attack": 400,
	"dodge" : -20,
	"parry" : 30,
	"damage": 300,
	"lvl"   : 150,
	"damage_type" : "����"
]),
});

int valid_enable(string usage) { return usage == "strike"; }

int valid_learn(object me)
{
	if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
		return notify_fail("��һ����ɢ������֡�\n");

	if ((int)me->query_skill("force") < 200)
		return notify_fail("����ڹ���򲻹�������ǿ����ϰһ����ɢ��\n");

	if ((int)me->query("max_neili") < 2500)
		return notify_fail("�������������ǿ���޷���ϰһ����ɢ��\n");

	if ((int)me->query_skill("strike", 1) < (int)me->query_skill("yipai-liangsan", 1))
		return notify_fail("��Ļ����Ʒ����ˮƽ���ޣ��޷����������һ����ɢ��\n");

	return 1;
}

string query_skill_name(int level)
{
	int i;
	for (i = sizeof(action); i > 0; i--)
		if (level >= action[i - 1]["lvl"])
			return action[i - 1]["skill_name"];
}

mapping query_action(object me, object weapon)
{
	int i, level;
	level = (int) me->query_skill("yipai-liangsan", 1);
	if (level < action[1]["lvl"])
		return action[0];

	return action[1];
}

int practice_skill(object me)
{
	if (me->query_temp("weapon") ||
	    me->query_temp("secondary_weapon"))
		return notify_fail("����������ϰ��\n");

	if ((int)me->query("qi") < 300)
		return notify_fail("�������̫���ˡ�\n");

	if ((int)me->query("neili") < 300)
		return notify_fail("�������������һ����ɢ��\n");

	me->receive_damage("qi", 100);
	me->add("neili", -100);
	return 1;
}

mixed hit_ob(object me, object victim, int damage_bonus)
{
	if (damage_bonus < 100) return 0;

	if (me->query("jiali") < 50 || me->query("neili") < 300)
		return 0;

	me->start_busy(2);
	victim->receive_damage("qi", damage_bonus, me);
	if (victim->query("neili") < 200)
		victim->set("neili", 0);
	else
		victim->add("neili", -100);

	return HIR "$n" HIR "����$N" HIR "��һ�ƣ�һʱ��ֻ���û�������"NOR"\n";
}
