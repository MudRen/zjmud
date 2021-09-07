#include <ansi.h>
inherit SKILL;

mapping *action = ({
([  "action": "$Nȫ��εض��𣬰����һ�����һʽ����ӥϮ�á���Ѹ�͵�ץ��$n��$l",
    "force" : 250,
    "attack": 45,
    "dodge" : 10,
    "parry" : 18,
    "damage": 30,
    "lvl"   : 0,
    "skill_name" : "��ӥϮ��" ,
    "damage_type" : "ץ��"
]),
([  "action": "$N����ֱ����˫��ƽ�죬һʽ����ӥչ�᡹��˫צһǰһ��£��$n��$l",
    "force" : 270,
    "attack": 50,
    "dodge" : 20,
    "parry" : 26,
    "damage": 45,
    "lvl"   : 40,
    "skill_name" : "��ӥչ��" ,
    "damage_type" : "ץ��"
]),
([  "action": "$Nһʽ���γ�ӥ�ɡ���ȫ����б��ƽ�ɣ�����һ����˫צ����$n�ļ�ͷ",
    "force" : 300,
    "attack": 60,
    "dodge" : 20,
    "parry" : 32,
    "damage": 45,
    "lvl"   : 70,
    "skill_name"  : "�γ�ӥ��" ,
    "damage_type" : "ץ��"
]),
([  "action": "$N˫צ�����Ͼ٣�ʹһʽ��ӭ��������һ�����ֱ�Ϯ��$n����Ҹ����",
    "force" : 340,
    "attack": 85,
    "dodge" : 30,
    "parry" : 55,
    "damage": 55,
    "lvl"   : 100,
    "skill_name" : "ӭ������" ,
    "damage_type" : "ץ��"
]),
([  "action": "$Nȫ�������ǰ��һʽ��������צ������צͻ�������Ȱ�ץ��$n���ؿ�",
    "force" : 350,
    "attack": 110,
    "dodge" : 40,
    "parry" : 68,
    "damage": 76,
    "lvl"   : 120,
    "skill_name" : "������צ" ,
    "damage_type" : "ץ��"
]),
([  "action": "$N���ػ��У�һʽ���������ء�������Ϯ�����д�Ѩ�����ַ�ץ$n���ɲ�",
    "force" : 370,
    "attack": 121,
    "dodge" : 51,
    "parry" : 78,
    "damage": 96,
    "lvl"   : 140,
    "skill_name" : "��������" ,
    "damage_type" : "ץ��"
]),
([  "action": "$N��������צ���棬һʽ���������ա��������������ƿն�����Ѹ���ޱȵػ���$n",
    "force" : 398,
    "attack": 133,
    "dodge" : 67,
    "parry" : 85,
    "damage": 107,
    "lvl"   : 160,
    "skill_name" : "��������" ,
    "damage_type" : "ץ��"
]),
([  "action": "$N�ڿո߷����ɣ�һʽ��ӥ�����������ж�ʱ�Գ�һ������צӰ����������$n",
    "force" : 410,
    "attack": 143,
    "dodge" : 55,
    "parry" : 81,
    "damage": 121,
    "lvl"   : 180,
    "skill_name" : "ӥ������" ,
    "damage_type" : "ץ��"
]),
([  "action": "$N���Ĳ��ض���ʹһʽ��������ˮ�������λ���һ����������$n",
    "force" : 431,
    "attack": 162,
    "dodge" : 63,
    "parry" : 86,
    "damage": 133,
    "lvl"   : 200,
    "skill_name" : "������ˮ" ,
    "damage_type" : "����"
]),
([  "action":  "$N΢΢һЦ��ʹһʽ������ڡ���˫�ֻó�������,ֱ����$n��$l",
    "force" : 455,
    "attack": 173,
    "dodge" : 66,
    "parry" : 95,
    "damage": 137,
    "lvl"   : 220,
    "skill_name" : "�����" ,
    "damage_type" : "����"
]),
});

int valid_enable(string usage) { return usage == "claw" || usage == "parry"; }

int valid_learn(object me)
{
	if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
	    return notify_fail("����Ѫ��צ������֡�\n");

	if ((int)me->query("max_neili") < 800)
	    return notify_fail("�������̫�����޷�����Ѫ��צ��\n");

	if ((int)me->query_str() < 40)
	    return notify_fail("�������������������޷�����Ѫ��צ��\n");

	if ((int)me->query_dex() < 40)
	    return notify_fail("��������Ƿ�ѣ����޷�����Ѫ��צ��\n");

	if ((int)me->query_skill("force") < 200)
	    return notify_fail("����ڹ�̫��޷�����Ѫ��צ��\n");

	if ((int)me->query_skill("claw", 1) < 180)
	    return notify_fail("��Ļ���צ��̫��޷������Ѫ��צ��\n");

	if ((int)me->query_skill("claw", 1) < (int)me->query_skill("ningxue-shenzhao", 1))
	    return notify_fail("��Ļ���צ����򲻹����޷������������Ѫ��צ��\n");

	return 1;
}

string query_skill_name(int level)
{
	int i;
	for (i = sizeof(action); i > 0; i--)
		if (level >= action[i-1]["lvl"])
			return action[i-1]["skill_name"];
}

mapping query_action(object me, object weapon)
{
	int i, level;
	level = (int) me->query_skill("ningxue-shenzhao",1);
	for (i = sizeof(action); i > 0; i--)
		if (level > action[i-1]["lvl"])
			return action[NewRandom(i, 5, level/5)];
}

int practice_skill(object me)
{
	if ((int)me->query("qi") < 120)
		return notify_fail("�������̫���ˡ�\n");

	if ((int)me->query("neili") < 350)
		return notify_fail("���������������Ѫ��צ��\n");

	me->receive_damage("qi", 100);
	me->add("neili", -300);
	return 1;
}

mixed hit_ob(object me, object victim, int damage_bonus, int factor)
{
	int lvl;
	int flvl;

	lvl  = me->query_skill("ningxue-shenzhao", 1);
	flvl = me->query("jiali");
	if (lvl < 80 || flvl < 10 || ! damage_bonus)
		return;

	if (flvl * 2 + random(lvl) > victim->query_skill("force") &&
	    victim->affect_by("ningxue_shenzhao",
			      ([ "level" : flvl + random(flvl),
				 "id"    : me->query("id"),
				 "duration" : lvl / 100 + random(lvl / 10) ])))
	{
		return HIR "ֻ��$n" HIR "һ���Һ��������ܵ�����Ѫ��צ�����ĸ��ţ�"NOR"\n";
	}
}

string perform_action_file(string action)
{
	return __DIR__"ningxue-shenzhao/" + action;
}
