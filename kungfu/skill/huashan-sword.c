// huashan-sword.c
// Modified by Venus Oct.1997
#include <ansi.h>

inherit SKILL;

mapping *action = ({
([      "name"  : "�з�����",
	"action": "$Nʹһ�С��з����ǡ�������$w���Ⱪ������$n��$l��ȥ",
	"force" : 70,
	"attack": 10,
	"parry" : 5,
	"dodge" : 10,
	"damage": 30,
	"lvl"   : 0,
	"damage_type":  "����"
]),
([      "name"  : "�ޱ���ľ",
	"action": "$N������ת��һ�С��ޱ���ľ������$n��$l",
	"force" : 120,
	"attack": 20,
	"parry" : 15,
	"dodge" : 20,
	"damage": 40,
	"lvl"   : 20,
	"damage_type":  "����"
]),
([      "name"  : "���ڤڤ",
	"action": "$N�趯$w��һ�С����ڤڤ��Ю�������������$n��$l",
	"force" : 160,
	"attack": 25,
	"parry" : 20,
	"dodge" : 30,
	"damage": 45,
	"lvl"   : 40,
	"damage_type":  "����"
]),
([      "name"  : "ƽɳ����",
	"action": "$N����$w����һ����������ƽɳ���㡹��$n��$l�̳�����",
	"force" : 190,
	"attack": 30,
	"parry" : 28,
	"dodge" : 35,
	"damage": 50,
	"lvl"   : 60,
	"damage_type":  "����"
]),
([      "name"  : "��������",
	"action": "$N����$w���Ⱪ����һ�С��������á���$n$l��ȥ",
	"force" : 220,
	"attack": 40,
	"parry" : 33,
	"dodge" : 40,
	"damage": 55,
	"lvl"   : 80,
	"damage_type":  "����"
]),
([      "name"  : "�׺����",
	"action": "$N����$w����һ���⻡��ֱָ$n$l��һ�С��׺���ա���������������ȥ",
	"force" : 260,
	"attack": 50,
	"parry" : 40,
	"dodge" : -20,
	"damage": 90,
	"lvl"   : 100,
	"damage_type":  "����"
]),
});

int valid_learn(object me)
{
	object ob;
	
	if ((int)me->query("max_neili") < 100)
		return notify_fail("�������������û�а취����ɽ������\n");
	
	if (! (ob = me->query_temp("weapon"))
	||  (string)ob->query("skill_type") != "sword" )
		return notify_fail("���������һ�ѽ�����ѧϰ������\n");
	
	if (me->query_skill("sword", 1) < me->query_skill("huashan-sword", 1))
		return notify_fail("��Ļ�������������ޣ��޷���������Ļ�ɽ������\n");
	
	return 1;
}

int valid_enable(string usage)
{
	return usage=="sword" || usage=="parry";
}

string query_skill_name(int level)
{
	int i;
	for (i = sizeof(action)-1; i >= 0; i--)
		if (level >= action[i]["lvl"])
			return action[i]["skill_name"];
}

mapping query_action(object me, object weapon)
{
	int i, level;
	level = (int) me->query_skill("huashan-sword", 1);
	for (i = sizeof(action); i > 0; i--)
		if (level > action[i-1]["lvl"])
			return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
    if ((int)me->query("qi") < 60)
	return notify_fail("�������̫�ͣ�û�а취��ϰ��ɽ������\n");
		
    if ((int)me->query("neili") < 40)
	return notify_fail("�������������û�а취��ϰ��ɽ������\n");

    me->receive_damage("qi", 50);
    me->add("neili", -31);
    return 1;
}

int valid_effect(object me, object weapon, string name, int skill)
{
}

mixed hit_ob(object me, object victim, int damage_bonus)
{
	int lvl;
	int i;

	lvl = me->query_skill("sword-cognize", 1);
	i = random(lvl);

	if (me->query("family/family_name") == "��ɽ����" &&
	    i > 30 && random(2) == 0)
	{
		if (i < 80)
		{
			victim->receive_wound("qi", damage_bonus / 7);
			return HIG "ֻ��$N" HIG "�ھ����£�����ֱ��$n" HIG
			       "��ȥ��"NOR"\n";
		}
		if (i < 160)
		{
			victim->receive_wound("qi", damage_bonus / 5);
			return HIM "����$N" HIM "����������ʢ��ȫ��������"
			       "���У�����ԴԴ��������$n" HIM "��"NOR"\n";
		} else
		{
			victim->receive_wound("qi", damage_bonus / 2);
			return HIW "$N" HIW "Ĭ���ڹ������г���������â����"
			       "$n" HIW "��"NOR"\n";
		}
	}
}

string perform_action_file(string action)
{
	return __DIR__"huashan-sword/" + action;
}

