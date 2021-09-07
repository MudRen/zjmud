// taishan-sword.c
// Modified by Java Sep.1998
#include <ansi.h>

inherit SKILL;

mapping *action = ({
([      "skill_name":    "��������",
	"action":  "$N����$wһ�Σ����һ���������һ�С��������ơ���ת����������"
		   "��΢����$w��$nбб��ȥ",
	"force" : 80,
	"dodge" : 20,
	"damage": 12,
	"lvl"   : 0,
	"damage_type":  "����"
]),
([      "skill_name":    "������",
	"action": "$N����$wȦת��һ�С������ա�ȥ���漲�������������$n��$l",
	"force" : 100,
	"dodge" : 30,
	"damage": 15,
	"lvl"   : 30,
	"damage_type":  "����"
]),
([      "skill_name":    "̩ɽʮ����",
	"action": "$Nչ�����ƣ����潣�ߣ����һ�գ��ұ�һ�䣬ԽתԽ�����͵�"
		  "$w���Ⱪ����һ�С�̩ɽʮ���̡���$n$l��ȥ",
	"force" : 120,
	"dodge" : 40,
	"damage": 20,
	"lvl"   : 60,
	"damage_type":  "����"
]),
([      "skill_name":    "����",
	"action": "$N����$wٿ�ش̳���һ���彣��ÿһ���Ľ��нԲ�Ȼ�й��⡣����"
		  "���ӣ��ڲ���䣬���ǡ����򽣡�",
	"force" : 140,
	"dodge" : 45,
	"damage": 30,
	"lvl"   : 90,
	"damage_type":  "����"
]),
([      "skill_name":    "������",
	"action": "$N����$wбָ���£�������ָ������ָ��������һ�����壬�ն���ȭ����"
		  "��Ĵָ������ζ�ʳָ��������ָȫչ����������Ĵָ����ʳָ��������"
		  "ָ��Ȼ������$w���Ⱪ������$n��$l��ȥ",
	"force" : 220,
	"attack": 100,
	"dodge" : 80,
	"damage": 80,
	"lvl"   : 180,
	"damage_type":  "����"
]),
});

int valid_learn(object me)
{
    object ob;
    if( (int)me->query("max_neili") < 150 )
	return notify_fail("�������������û�а취��̩ɽ������\n");

    if( (int)me->query_skill("force") < 30 )
	return notify_fail("�������������û�а취��̩ɽ������\n");

    if( !(ob = me->query_temp("weapon"))
    ||      (string)ob->query("skill_type") != "sword" )
	return notify_fail("���������һ�ѽ�������������\n");

    return 1;
}

int valid_enable(string usage)
{
    return usage=="sword" || usage=="parry";
}

mapping query_action(object me, object weapon)
{
    return action[random(sizeof(action))];
}

int practice_skill(object me)
{
    if ((int)me->query("qi") < 40)
	return notify_fail("�����������������û�а취��ϰ̩ɽ������\n");

    if ((int)me->query("neili") < 35)
	return notify_fail("�����������������û�а취��ϰ̩ɽ������\n");

    me->receive_damage("qi", 30);
    me->add("neili", -11);
    return 1;
}

string perform_action_file(string action)
{
	return __DIR__"taishan-sword/" + action;
}
