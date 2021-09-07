// hengshan-sword.c
// Modified by Java Sep.1998
#include <ansi.h>

inherit SKILL;

mapping *action = ({
([
	"skill_name" : "��ҹ����",
	"action": "$N����$w����ָ����ͻȻ���ڿ���һ������������֮�������ű���"
		  "��������������$w���Ⱪ������$n��$l��ȥ",
	"force" : 80,
	"dodge" : 50,
	"damage": 17,
	"lvl"   : 0,
	"damage_type":  "����"
]),
([      "skill_name" : "��������",
	"action": "$N����$w������ȣ���Ȼ���Ƶ���$n����$n��æת������ֻ��"
		  "����������",
	"force" : 100,
	"dodge" : 70,
	"damage": 22,
	"lvl"   : 10,
	"damage_type":  "����"
]),
([      "skill_name":    "�ٱ�ǧ��",
	"action": "$N����$w���ⶸ�������е�$w���͵ط��̣�ֱָ$n�ؿڡ���һ��"
		  "���п켫������������ã����ǡ��ٱ�ǧ�ú�ɽ����ʮ��ʽ���еľ���",
	"force" : 110,
	"dodge" : 40,
	"damage": 29,
	"lvl"   : 20,
	"damage_type":  "����"
]),
([      "skill_name":    "Ȫ��ܽ��",
	"action": "$N�����Է�������·������$wˢ��һ����Ȫ��ܽ�ء�����$nС"
		  "����ȥ",
	"force" : 130,
	"dodge" : 40,
	"damage": 30,
	"lvl"   : 40,
	"damage_type":  "����"
]),
([      "skill_name":    "�����ϸ�",
	"action": "$N�����Է�������·������$wˢ��һ���������ϸǡ�����$n��"
		  "ͷ��ȥ",
	"force" : 150,
	"dodge" : 40,
	"damage": 4,
	"lvl"   : 60,
	"damage_type":  "����"
]),
([      "skill_name":    "ʯ������",
	"action": "$N����$wٿ�ش̳������ƴ����ػأ�������ã�����һ�С�ʯ����������"
		  "��$n$l��ȥ",
	"force" : 160,
	"dodge" : 60,
	"damage": 40,
	"lvl"   : 80,
	"damage_type":  "����"
]),
([      "skill_name":    "��������",
	"action": "$N����$wٿ�ش̳�����������֮���£������޶�������׽��������"
		  "һ�С�������������ָ��$n$l",
	"force" : 180,
	"dodge" : 60,
	"damage": 45,
	"lvl"   : 100,
	"damage_type":  "����"
]),
([      "skill_name":    "���ף��",
	"action": "$N����Ծ�𣬡����ף�ڡ�����$w����һ�������Ӱ��������$n��$l",
	"force" : 210,
	"dodge" : 60,
	"damage": 50,
	"lvl"   : 120,
	"damage_type":  "����"
]),
});

int valid_learn(object me)
{
    object ob;

    if ((int)me->query("max_neili") < 200)
	return notify_fail("�������������û�а취����ɽ������\n");

    if ((int)me->query_skill("force") < 40)
	return notify_fail("����ڹ���򲻹���û�а취����ɽ������\n");

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
    level   = (int) me->query_skill("hengshan-sword",1);
    for(i = sizeof(action); i > 0; i--)
	if(level > action[i-1]["lvl"])
	    return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
    if( (int)me->query("qi") < 40)
	return notify_fail("�����������������û�а취��ϰ��ɽ������\n");

    if( (int)me->query("neili") < 40)
	return notify_fail("�����������������û�а취��ϰ��ɽ������\n");

    me->receive_damage("qi", 30);
    me->add("neili", -18);
    return 1;
}

string perform_action_file(string action)
{
	return __DIR__"hengshan-sword/" + action;
}
