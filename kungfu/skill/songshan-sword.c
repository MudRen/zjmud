// songshan-sword.c
// Modified by Java Sep.1998
#include <ansi.h>

inherit SKILL;

mapping *action = ({
([      "skill_name":    "��������",
	"action":  "$N����$wһ�����ٽ���������������ʹһ�С��������ڡ�����"
		   "��ϵ���ڵ���ɽ����",
	"dodge" : 10,
	"damage": 20,
	"force" : 100,
	"lvl"   : 0,
	"damage_type":  "����"
]),
([      "skill_name":    "ǧ������",
	"action":  "$N����$wͻȻ�佣��һ�£�����һ���׺磬������ΰ������Ʈ�ݣ�"
		   "������ɽ�����ľ�Ҫ���ڣ�һ�С�ǧ����������$n$lֱ�̹���",
	"dodge" : 20,
	"damage": 25,
	"force" : 150,
	"lvl"   : 20,
	"damage_type":  "����"
]),
([      "skill_name":    "���両��",
	"action":  "$N����$wͻȻ�佣��һ�£�һ�С����両�࡯����һ����⣬��"
		   "׳�ۻ룬��$n$lֱ�̹���",
	"dodge" : 25,
	"damage": 30,
	"force" : 170,
	"lvl"   : 40,
	"damage_type":  "����"
]),
([      "skill_name":    "������",
	"action":  "$N����$w����һ�£�һ�С������ء��������࣬������ΰ����"
		   "$n$lֱ�̹���",
	"dodge" : 20,
	"damage": 40,
	"force" : 210,
	"lvl"   : 60,
	"damage_type":  "����"
]),
([      "skill_name":    "���ż�ɽ",
	"action":  "$N��������һ�֣�����$w�����ӳ���ʹ������ɽ�ɽ��������ż�"
		   "ɽ��",
	"dodge" : 15,
	"damage": 40,
	"force" : 220,
	"lvl"   : 80,
	"damage_type":  "����"
]),
([      "skill_name":    "������ɽ",
	"action":  "$N����$w���϶��µ���$nֱ����ȥ��һ�С�������ɽ��������ʯ"
		   "���쾪�����ƣ�����ɽ����֮�������ӵ����쾡��",
	"dodge" : -10,
	"damage": 50,
	"force" : 230,
	"lvl"   : 100,
	"damage_type":  "����"
]),
([      "skill_name":    "��������",
	"action":  "$N����$wˢ��һ��������Ҽ�����ȥ������һ����ɽ����"
		   "�ڽ���������������������$w�԰���к��������������ֱ����"
		   "������һ������һ��",
	"dodge" : 20,
	"damage": 65,
	"force" : 290,
	"lvl"   : 150,
	"damage_type":  "����"
]),
});

int valid_learn(object me)
{
    object ob;
    if( (int)me->query("max_neili") < 150 )
	return notify_fail("�������������û�а취����ɽ������\n");

    if( !(ob = me->query_temp("weapon"))
    ||      (string)ob->query("skill_type") != "sword" )
	return notify_fail("���������һ�ѽ�������������\n");

    return 1;
}

int valid_enable(string usage)
{
    return usage=="sword" || usage=="parry";
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
    level   = (int) me->query_skill("songshan-sword",1);
    for(i = sizeof(action); i > 0; i--)
	if(level > action[i-1]["lvl"])
	    return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
    if ((int)me->query("qi") < 30)
	return notify_fail("���������������ϰ��ɽ������\n");

    if ((int)me->query("neili") < 30 )
	return notify_fail("�������������û�а취��ϰ��ɽ������\n");

    me->receive_damage("qi", 35);
    me->add("neili", -26);

    return 1;
}

string perform_action_file(string action)
{
	return __DIR__"songshan-sword/" + action;
}
