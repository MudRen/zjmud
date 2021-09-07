// piaoxue-zhang.c

#include <ansi.h>
inherit SKILL;

mapping *action = ({
([      "action" : "$N�������һʽ��׷����硹��˫����£���У�ͬʱ����$n�����",
	"force"  : 170,
	"attack" : 85,
	"dodge"  : 38,
	"parry"  : 38,
	"damage" : 36,
	"lvl"    : 0,
	"skill_name" : "׷�����",
	"damage_type" : "����"
]),
([      "action" : "$Nһʽ����Ʈ�ĺ�����˫������ʵʵ����Ѹ�ײ����ڶ�֮������$n",
	"force"  : 210,
	"attack" : 98,
	"dodge"  : 43,
	"parry"  : 43,
	"damage" : 44,
	"lvl"    : 40,
	"skill_name" : "��Ʈ�ĺ�",
	"damage_type" : "����"
]),
([      "action" : "$Nʹһʽ���˷���ӿ��������������˫�����֣�һ������$n�ĺ��ȥ",
	"force"  : 280,
	"attack" : 103,
	"dodge"  : 51,
	"parry"  : 51,
	"damage" : 58,
	"lvl"    : 80,
	"skill_name" : "�˷���ӿ",
	"damage_type" : "����"
]),
([      "action" : "$Nһʽ�������졹��˫�����÷��ã��ƶ��Ƕ��������缱����ʹ$n��������",
	"force"  : 340,
	"attack" : 125,
	"dodge"  : 65,
	"parry"  : 65,
	"damage" : 67,
	"lvl"    : 120,
	"skill_name" : "������",
	"damage_type" : "����"
]),
([      "action" : "$Nһʽ�������������Ӱ��������ƮƮ���죬�������Ʒ�ֱӿ$n��ȥ",
	"force"  : 370,
	"attack" : 131,
	"dodge"  : 68,
	"parry"  : 68,
	"damage" : 71,
	"lvl"    : 160,
	"skill_name" : "��������",
	"damage_type" : "����"
]),
([      "action" : "$N˫�ֱ�ã���ָ�ᵯ��һ�С��德��ɡ���������·���л�ʮ������$n",
	"force"  : 410,
	"attack" : 145,
	"dodge"  : 73,
	"parry"  : 73,
	"damage" : 82,
	"lvl"    : 200,
	"skill_name" : "�德���",
	"damage_type" : "����"
]),
});

int valid_enable(string usage) { return usage == "strike" ||  usage == "parry"; }

int valid_learn(object me)
{
	if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
		return notify_fail("��Ʈѩ�����Ʊ�����֡�\n");

	if (me->query("con") < 23 || me->query_con() < 50)
		return notify_fail("��ĸ���Ƿ�ѣ�������Ʈѩ�����ơ�\n");

	if (me->query("str") < 24 || me->query_str() < 52)
		return notify_fail("��ı���������������Ʈѩ�����ơ�\n");

	if (me->query_skill("force") < 200)
		return notify_fail("����ڹ���򲻹���������Ʈѩ�����ơ�\n");

	if (me->query_skill("strike", 1) < 100)
		return notify_fail("����Ʒ�����������������Ʈѩ�����ơ�\n");

	if (me->query("max_neili") < 2200)
		return notify_fail("���������Ϊ̫ǳ���޷���Ʈѩ�����ơ�\n");

	if (me->query_skill("strike", 1) < me->query_skill("sixiang-zhang", 1))
		return notify_fail("��Ļ����Ʒ�̫��޷����������Ʈѩ�����ơ�\n");

	return 1;
}

string query_skill_name(int level)
{
	int i;
	for(i = sizeof(action)-1; i >= 0; i--)
		if(level >= action[i-1]["lvl"])
			return action[i-1]["skill_name"];
}

mapping query_action(object me, object weapon)
{
	int i, level;
	level   = (int)me->query_skill("piaoxue-zhang",1);
	for(i = sizeof(action); i > 0; i--)
		if(level > action[i-1]["lvl"])
			return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
	if ((int)me->query("qi") < 100)
		return notify_fail("�������̫���ˡ�\n");

	if ((int)me->query("neili") < 120)
		return notify_fail("�������������ϰƮѩ�����ơ�\n");

	if (me->query_skill("sixiang-zhang", 1) < 100)
	{
		me->receive_damage("qi", 60);
		me->add("neili", -80);
	} else
	{
		me->receive_damage("qi", 80);
		me->add("neili", -100);
	}
	return 1;
}

mixed hit_ob(object me, object victim, int damage_bonus)
{
	int lvl;

	lvl = me->query_skill("piaoxue-zhang", 1);

	if (damage_bonus < 180 || lvl < 160) return 0;

	if (damage_bonus / 6 > victim->query_con() && random(4) == 0)
	{
		victim->receive_wound("qi", (damage_bonus - 140) / 3, me);
			return HIR "ֻ��$n" HIR "ǰ�ء����ꡱһ�����죬��"
			       "���۶���һ���߹ǡ�"NOR"\n";
	}
}

string perform_action_file(string action)
{
	return __DIR__"piaoxue-zhang/"+ action;
}

