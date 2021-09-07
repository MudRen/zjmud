#include <ansi.h>

inherit SKILL;

mapping *action = ({
([      "action": "$N����һ�һ�С�ŰĿ��������$w���ñ�ֱ��ֱ��$n��˫��",
	"force" : 100,
	"dodge" : 12,
	"parry" : 10,
	"damage": 5,
	"lvl"   : 0,
	"skill_name" : "ŰĿ",
	"damage_type": "����"
]),
([      "action": "$N������ң�һ�С��˸Ρ�������$w��������Ӱ����ɨ$n����",
	"force" : 130,
	"dodge" : 17,
	"parry" : 15,
	"damage": 10,
	"lvl"   : 20,
	"skill_name" : "�˸�",
	"damage_type": "����"
]),
([      "action": "$N��������һ�С����ġ�������$w��һ��ͭ����ֱ��$n�ز�",
	"force" : 150,
	"dodge" : 21,
	"parry" : 19,
	"damage": 13,
	"lvl"   : 40,
	"skill_name" : "����",
	"damage_type": "����"
]),
([      "action": "$N����һ�ӣ�һ�С��ߵ���������$wֱ����$n����",
	"force" : 175,
	"dodge" : 32,
	"parry" : 27,
	"damage": 18,
	"lvl"   : 60,
	"skill_name" : "�ߵ�",
	"damage_type": "����"
]),
([      "action": "$N�߸�Ծ��һ�С����ǡ�������$w��ֱ��$n��ͷ����",
	"force" : 225,
	"dodge" : 42,
	"parry" : 37,
	"damage": 35,
	"lvl"   : 80,
	"skill_name" : "����",
	"damage_type": "����"
]),
([      "action": "$N����һת��һ�С��ջ꡹������$w��������ڿ�һ���͵���$n��ͷ����",
	"force" : 320,
	"dodge" : 57,
	"parry" : 39,
	"damage": 41,
	"lvl"   : 100,
	"skill_name" : "�ջ�",
	"damage_type": "����"
]),
});

int valid_enable(string usage) { return usage == "whip" || usage == "parry"; }

int valid_learn(object me)
{
	object weapon;

	if (! objectp(weapon = me->query_temp("weapon")) ||
	    (string)weapon->query("skill_type") != "whip" )
		return notify_fail("���������һ�����Ӳ�����ϰ��������\n");

	if ((int)me->query("max_neili") < 400)
		return notify_fail("����������㣬û�а취��ϰ��������\n");

	if ((int)me->query_skill("force") < 80)
		return notify_fail("����ڹ����̫ǳ��\n");

	if ((int)me->query_skill("whip", 1) < 60)
		return notify_fail("��Ļ����޷����̫ǳ��\n");

	if ((int)me->query_skill("whip", 1) < (int)me->query_skill("chanhun-suo", 1))
		return notify_fail("��Ļ����޷�ˮƽ���ޣ��޷���������Ĳ�������\n");

	return 1;
}

string query_skill_name(int level)
{
	int i;
	for (i = sizeof(action) - 1; i >= 0; i--)
		if (level >= action[i]["lvl"])
			return action[i]["skill_name"];
}

mapping query_action(object me, object weapon)
{
	int i, level;
	level = (int) me->query_skill("chanhun-suo", 1);
	for (i = sizeof(action); i > 0; i--)
		if (level > action[i - 1]["lvl"])
			return action[NewRandom(i, 20, level / 5)];
}

int practice_skill(object me)
{
	object weapon;

	if (! objectp(weapon = me->query_temp("weapon")) ||
	    (string)weapon->query("skill_type") != "whip")
		return notify_fail("��ʹ�õ��������ԡ�\n");

	if ((int)me->query("qi") < 60)
		return notify_fail("���������������������\n");

	if ((int)me->query("neili") < 60)
		return notify_fail("���������������������\n");

	me->receive_damage("qi", 50);
	me->add("neili", -50);
	return 1;
}

string perform_action_file(string action)
{
	return __DIR__"chanhun-suo/" + action;
}
