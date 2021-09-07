//kuangfeng-blade ��絶��
// Made by deaner
#include <ansi.h>
inherit SKILL;

mapping *action = ({
([  "action" : "$N����$w��ӣ�һ��"+HIW"����ƽ�˾���"NOR+"������ƽ��ʵ��Ѹ�ٵ���"
	       "$n��$l��ȥ",
    "force" : 60,
    "dodge" : 20,
    "lvl"   : 0,
    "skill_name" : "��ƽ�˾�",
    "damage_type" : "����"
]),
([  "action" : "$Nһ��"+HIW"��������ӿ��"NOR+"���ҽ�һ�㣬$w��������������ӿ$n��$l",
    "force"  : 80,
    "dodge"  : 35,
    "damage" : 20,
    "lvl"    : 10,
    "skill_name" : "������ӿ",
    "damage_type" : "����"
]),
([  "action" : "$Nһ��"+HIY"�������ơ�"NOR+"���ֱ�һ�գ�����һ�����϶���ն��$n",
    "force"  : 100,
    "dodge"  : 35,
    "damage" : 25,
    "lvl"    : 20,
    "skill_name" : "������",
    "damage_type" : "����"
]),
([  "action" : "$Nһ��"+HIC"��������ɢ��"NOR+"��������ˣ�$wȴ����ǰ����һ��Բ��"
	       "������$n��$l",
    "force"  : 120,
    "dodge"  : 45,
    "damage" : 35,
    "lvl"    : 30,
    "skill_name" : "������ɢ",
    "damage_type" : "����"
]),
([  "action" : "$N���������ϣ�һ��"+HIW"��������ড�"NOR+"������$n��ǰ��$w�Ϳ�$n��$l",
    "force"  : 140,
    "dodge"  : 50,
    "damage" : 25,
    "lvl"    : 45,
    "skill_name" : "�������",
    "damage_type" : "����"
]),
([  "action" : "$N���ٻ���$w��ʹ��һ��"+RED"�����в���"NOR+"������һƬ��������$n��$l",
    "force"  : 150,
    "dodge"  : 65,
    "damage" : 30,
    "lvl"    : 60,
    "skill_name" : "���в���",
    "damage_type" : "����"
]),
([  "action" : "$Nһ��"+HIC"���絶˪����"NOR+"��ֻ�����쵶����˸�����ص�Ӱ��$n��ȫ��ӿȥ",
    "force"  : 160,
    "dodge"  : 70,
    "damage" : 35,
    "lvl"    : 70,
    "skill_name" : "�絶˪��",
    "damage_type" : "����"
]),
([  "action" : "$Nʹһ��"+HIW"����۵糸��"NOR+"��$w��������Ӱ��$n��$lӿȥ",  
    "force"  : 170,
    "dodge"  : 75,
    "damage" : 45,
    "lvl"    : 85,
    "skill_name" : "��۵糸",
    "damage_type" : "����"
]),
([  "action" : "$Nһ��"+HIB"������Ʈҡ��"NOR+"��$w������˸�������ƻ�����ر�$n��$l",
    "force"  : 180,
    "dodge"  : 80,
    "damage" : 55,
    "lvl"    : 100,
    "skill_name" : "����Ʈҡ",
    "damage_type" : "����"
]),
([  "action" : "$NŲ��С�ˣ�һ��"+HIC"���绨ѩ�¡�"NOR+"������$w���赭д�ػӳ�һ"
	       "�����漴�֡��ৡ�������������������������$n��$l",
    "force"  : 190,
    "dodge"  : 100,
    "damage" : 60,
    "lvl"    : 120,
    "skill_name" : "�绨ѩ��",
    "damage_type" : "����"
]),
});


int valid_enable(string usage) { return usage == "blade" || usage == "parry"; } 

int valid_learn(object me)
{
    if ((int)me->query("max_neili") < 250)
	return notify_fail("�������������\n");

    if ((int)me->query_skill("force") < 80)
	return notify_fail("����ڹ��ķ����̫ǳ��\n");

    if ((int)me->query_skill("dodge") < 80)
	return notify_fail("����Ṧ���̫ǳ��\n");

    if ((int)me->query_dex() < 25)
	return notify_fail("�������������\n");

    return 1;
}

string query_skill_name(int level)
{
    int i;
    for(i = sizeof(action)-1; i >= 0; i--)
	if(level >= action[i]["lvl"])
	    return action[i]["skill_name"];
}

mapping query_action(object me, object weapon)
{
    int i, level;
    level   = (int) me->query_skill("kuangfeng-blade",1);
    for(i = sizeof(action); i > 0; i--)
	if(level > action[i-1]["lvl"])
	    return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
    object weapon;

    if (!objectp(weapon = me->query_temp("weapon"))
    || (string)weapon->query("skill_type") != "blade")
	return notify_fail("��ʹ�õ��������ԡ�\n");

    if ((int)me->query("qi") < 50)
	return notify_fail("���������������絶����\n");

    if ((int)me->query("neili") < 30)
	return notify_fail("���������������絶����\n");

    me->receive_damage("qi", 45);
    me->add("neili", -15);

    return 1;
}

string perform_action_file(string action)
{
    return __DIR__"kuangfeng-blade/" + action;
}
