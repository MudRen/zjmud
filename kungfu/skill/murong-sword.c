// murong-sword Ľ�ݽ���

inherit SKILL;

mapping *action = ({
([  "action" : "$N��ǰ����һ����һ�С���ɨǧ����������$w�������Һ�ն$n��$l",
    "force"  : 90,
    "attack" : 25,
    "dodge"  : 40,
    "damage" : 20,
    "lvl"    : 0,
    "skill_name" : "��ɨǧ��",
    "damage_type" : "����"
]),
([  "action" : "$N���ֽ���������һ����$w��â��ҫ��һʽ��ǧ��һ����ֱ��$n��$l",
    "force"  : 120,
    "attack" : 31,
    "dodge"  : 45,
    "damage" : 25,
    "lvl"    : 20,
    "skill_name" : "ǧ��һ��",
    "damage_type" : "����"
]),
([  "action" : "$Nһ�С������ڡ���$w�������������⣬��ס$n��$l",
    "force"  : 140,
    "attack" : 37,
    "dodge"  : 50,
    "damage" : 30,
    "lvl"    : 40,
    "skill_name" : "������",
    "damage_type" : "����"
]),
([  "action" : "$Nһ�С��������������$w��ɨ��������ĥ�����Ĺ���$n��$l",
    "force"  : 160,
    "attack" : 45,
    "dodge"  : 55,
    "damage" : 40,
    "lvl"    : 60,
    "skill_name" : "��������",
    "damage_type" : "����"
]),
([  "action" : "$Nʹ����������������$w�������������ԴԴ���ϻ���$n��$l",
    "force"  : 180,
    "attack" : 52,
    "dodge"  : 60,
    "damage" : 50,
    "lvl"    : 80,
    "skill_name" : "��������",
    "damage_type" : "����"
]),
([  "action" : "$Nһ�С�һ�򵱹ء�������$w�󿪴�ϣ����϶��������������"
	       "ֱ��$n��$l������ȥ",
    "force"  : 210,
    "attack" : 58,
    "dodge"  : 65,
    "damage" : 65,
    "lvl"    : 100,
    "skill_name" : "һ�򵱹�",
    "damage_type" : "����"
]),
([  "action" : "$Nһ�С�ɳ������������е�$wָָ�����������ʱ������$n",
    "force"  : 240,
    "attack" : 63,
    "dodge"  : 70,
    "damage" : 75,
    "lvl"    : 120,
    "skill_name" : "ɳ�����",
    "damage_type" : "����"
]),
([  "action" : "$N��Ӱ����, һ�С���¹��ԭ�������е�$wȥ�ƿ���쳣������$n��$l",
    "force"  : 270,
    "attack" : 70,
    "dodge"  : 75,
    "damage" : 85,
    "lvl"    : 140,
    "skill_name" : "��¹��ԭ",
    "damage_type" : "����"
]),
});


int valid_enable(string usage)
{
	return (usage == "sword") || (usage == "parry");
}

int valid_learn(object me)
{
    if ((int)me->query("max_neili") < 150)
	return notify_fail("�������������\n");

    return 1;
}

mapping query_action(object me, object weapon)
{
    int i, level;
    level   = (int) me->query_skill("murong-sword",1);
    for(i = sizeof(action); i > 0; i--)
	if(level > action[i-1]["lvl"])
	    return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
    object weapon;

    if (!objectp(weapon = me->query_temp("weapon"))
       || (string)weapon->query("skill_type") != "sword")
	return notify_fail("��ʹ�õ��������ԡ�\n");

    if ((int)me->query("qi") < 50)
	return notify_fail("�������������Ľ�ݽ�����\n");

    if ((int)me->query("neili") < 50)
	return notify_fail("�������������Ľ�ݽ�����\n");

    me->receive_damage("qi", 38);
    me->add("neili", -33);
    return 1;
}

string perform_action_file(string action)
{
    return __DIR__"murong-sword/" + action;
}
