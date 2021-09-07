//bizhen-qingzhang ��������

#include <ansi.h>

inherit SKILL;

mapping *action = ({
([      "action" : "$N���μ��Σ�һԾ����$n��ǰ�����ƴ����й�֮������$n��$l",
	"force" : 180,
	"attack": 23,
	"dodge" : 25,
	"parry" : 17,
	"damage": 19,
	"lvl"   : 0,
	"damage_type" : "����"
]),
([      "action" : "$N����Ծ��˫�����϶���б����������ʱ��ǧ���ƺ���������˷�ϯ��$n",
	"force" : 240,
	"attack": 41,
	"dodge" : 25,
	"parry" : 27,
	"damage": 25,
	"lvl"   : 30,
	"damage_type" : "����"
]),
([      "action" : "$Nƽ��Ϊ����бб�������ó�һ�������͵��ƾ���쫷�����$n��ȫ��",
	"force" : 330,
	"attack": 58,
	"dodge" : 36,
	"parry" : 35,
	"damage": 39,
	"lvl"   : 60,
	"damage_type" : "����"
]),
([      "action" : "$N��ת���ƻ�סȫ��������Ծ��$n��ǰ����ע���ƣ�����$n������ȥ",
	"force" : 410,
	"attack": 96,
	"dodge" : 81,
	"parry" : 62,
	"damage": 53,
	"lvl"   : 90,
	"damage_type" : "����"
]),
([      "action" : "$N���ƺ󳷣�����һ�����͵ػ��ƿ������ó�һ���ޱ��������ƾ�ֱն��$n��$l",
	"force" : 460,
	"attack": 125,
	"dodge" : 35,
	"parry" : 47,
	"damage": 78,
	"lvl"   : 120,
	"damage_type" : "����"
]),
([      "action" : "$N˫�ֻ�������γ�һ����Ȧ��һ�ɾ���������ӿ�������Ƶ�$n���Ժ���",
	"force" : 520,
	"attack": 110,
	"dodge" : 45,
	"parry" : 40,
	"damage": 85,
	"lvl"   : 150,
	"damage_type" : "����"
]),
});

int valid_enable(string usage) { return usage=="strike" || usage=="parry"; }

int valid_learn(object me)
{
	if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
		return notify_fail("���������Ʊ�����֡�\n");

	if ((int)me->query_skill("force") < 250)
		return notify_fail("����ڹ���򲻹����޷���ϰ�������ơ�\n");

	if ((int)me->query("max_neili") < 2500)
		return notify_fail("�������̫�����޷���ϰ�������ơ�\n");

	if ((int)me->query_skill("strike", 1) < 180)
		return notify_fail("��Ļ����Ʒ���򲻹����޷���ϰ�������ơ�\n");

	if ((int)me->query_skill("strike", 1) < (int)me->query_skill("bizhen-qingzhang", 1))
		return notify_fail("��Ļ����Ʒ�ˮƽ���ޣ��޷���������ı������ơ�\n");

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
	level = (int) me->query_skill("bizhen-qingzhang",1);
	for (i = sizeof(action); i > 0; i--)
		if (level > action[i - 1]["lvl"])
			return action[NewRandom(i, 20, level / 5)];
}

int practice_skill(object me)
{
	if ((int)me->query("qi") < 100)
		return notify_fail("�������̫���ˡ�\n");

	if ((int)me->query("neili") < 100)
		return notify_fail("��������������������ơ�\n");

	me->receive_damage("qi", 80);
	me->add("neili", -80);
	return 1;
}

mixed hit_ob(object me, object victim, int damage_bonus)
{
	if (damage_bonus < 100) return 0;

	if (random(me->query_skill("force")) > victim->query_skill("force") / 2)
	{
		victim->receive_wound("qi", (damage_bonus - 100) / 2);
		return HIR "ֻ��" + victim->name() +
		       HIR "ǰ�ء����ꡱһ�����������߹���ϵ�������"NOR"\n";
	}
}

string perform_action_file(string action)
{
	return __DIR__"bizhen-qingzhang/" + action;
}
