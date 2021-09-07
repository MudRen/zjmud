#include <ansi.h>
inherit SKILL;

mapping *action = ({
([  "action": "$Nʹ��һ�С��ٻ����㡹��������ɣ�����ֱ��$n��$l",
    "force" : 220,
    "attack": 25,
    "dodge" : 10,
    "parry" : 16,
    "damage": 10,
    "lvl"   : 0,
    "skill_name" : "�ٻ�����" ,
    "damage_type" : "����"
]),
([  "action": "$Nʹ��һ�С���ľ�Կݡ���˫�Ƽ��������������������Ʒ�ֱ��$n��$l",
    "force" : 280,
    "attack": 55,
    "dodge" : 15,
    "parry" : 19,
    "damage": 25,
    "lvl"   : 30,
    "skill_name" : "��ľ�Կ�" ,
    "damage_type" : "����"
]),
([  "action": "$N����һԾ����һ���ֽУ�һ�С������ɢ����˫������ǵذ�����$n",
    "force" : 340,
    "attack": 67,
    "dodge" : 20,
    "parry" : 25,
    "damage": 35,
    "lvl"   : 60,
    "skill_name"  : "�����ɢ" ,
    "damage_type" : "����"
]),
([  "action": "$N��Ȼһ����Х��һ�С��ջ����ǡ���˫����Ȼ���£�ֱ��$n��Ҫ��",
    "force" : 440,
    "attack": 85,
    "dodge" : 20,
    "parry" : 38,
    "damage": 60,
    "lvl"   : 90,
    "skill_name" : "�ջ�����" ,
    "damage_type" : "����"
]),
([  "action": "$N���һ��������һ���죬˫�ۺ�Ȼ�������ߣ�һ�С�����׷�꡹ֱֱ����$n��$l",
    "force" : 470,
    "attack": 90,
    "dodge" : 40,
    "parry" : 43,
    "damage": 65,
    "lvl"   : 120,
    "skill_name" : "����׷��" ,
    "damage_type" : "����"
]),
([  "action": "$Nһ�С��ѹǴ��ġ���˫���ͷ��ĳ�������������Ӱ����Ȼ��һ����Ѹ���ޱȵ�����$n",
    "force" : 480,
    "attack": 126,
    "dodge" : 40,
    "parry" : 55,
    "damage": 80,
    "lvl"   : 150,
    "skill_name" : "�ѹǴ���" ,
    "damage_type" : "����"
]),
});

int valid_enable(string usage) { return usage == "strike" || usage == "parry"; }

int valid_combine(string combo) { return combo=="jiuyin-baiguzhao"; }

int valid_learn(object me)
{
	if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
	    return notify_fail("�������Ʊ�����֡�\n");

	if ((int)me->query("max_neili") < 1200)
	    return notify_fail("���������Ϊ̫ǳ���޷���ϰ�����ơ�\n");

	if ((int)me->query_skill("force") < 90)
	    return notify_fail("����ڹ�̫��޷���ϰ�����ơ�\n");

	if ((int)me->query_skill("strike", 1) < 80)
	    return notify_fail("��Ļ����Ʒ�̫��޷��������ơ�\n");

	if ((int)me->query_skill("strike", 1) < (int)me->query_skill("cuixin-zhang", 1))
	    return notify_fail("��Ļ����Ʒ���򲻹����޷���������Ĵ����ơ�\n");

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
	level = (int) me->query_skill("cuixin-zhang",1);
	for (i = sizeof(action); i > 0; i--)
		if (level > action[i-1]["lvl"])
			return action[NewRandom(i, 5, level/5)];
}

int practice_skill(object me)
{
	if ((int)me->query("qi") < 100)
		return notify_fail("�������̫���ˡ�\n");

	if ((int)me->query("neili") < 350)
		return notify_fail("�������������\n");

	if (environment(me)->query("no_fight"))
		return notify_fail("���ﲻ��������\n");

	if (environment(me)->query("sleep_room"))
		return notify_fail("���ﲻ��������\n");

	me->receive_damage("qi", 80);
	me->add("neili", -300);
	return 1;
}
mixed hit_ob(object me, object victim, int damage_bonus, int factor)
{
	int lvl;
	int flvl;

	lvl  = me->query_skill("cuixin-zhang", 1);
	flvl = me->query("jiali");
	if (lvl < 80 || flvl < 10 || ! damage_bonus)
		return;

	if (flvl * 2 + random(lvl) > victim->query_skill("force") &&
	    victim->affect_by("cuixin_zhang",
			      ([ "level" : flvl + random(flvl),
				 "id"    : me->query("id"),
				 "duration" : lvl / 100 + random(lvl / 10) ])))
	{
		return HIR "ֻ��$n�ƺ���һ�����������ܵ��˴������ƾ��ĸ��ţ�"NOR"\n";
	}
}

string perform_action_file(string action)
{
	return __DIR__"cuixin-zhang/" + action;
}

