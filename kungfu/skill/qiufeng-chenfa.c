// qiufeng-chenfa.c ������

#include <ansi.h>

inherit SKILL;

mapping *action = ({
([	"action": "$N����������һ�С�����Ҷ��������$w����һ�ɾ��磬����$n������",
	"force" : 40,
	"dodge" : 20,
	"damage": 20,
	"lvl"   : 0,
	"skill_name" : "����Ҷ",
	"damage_type":	"����"
]),
([	"action": "$N����һ�ӣ�һ�С����Χ����������$wֱ����$n�����",
	"force" : 70,
	"dodge" : 15,
	"damage": 30,
	"lvl"   : 20,
	"skill_name" : "���Χ��",
	"damage_type":	"����"
]),
([	"action": "$N����һת��һ�С����ƶϴ���������$w��������ڿ�һ���͵���$n��ͷ����",
	"force" : 80,
	"dodge" : 25,
	"damage": 35,
	"lvl"   : 40,
	"skill_name" : "���ƶϴ�",
	"damage_type":	"����"
]),
([	"action": "$N���᳾�ң�һ�С����绯�꡹������$w��������Ӱ����ɽ������ɨ��$nȫ��",
	"force" : 100,
	"dodge" : 15,
	"damage": 50,
	"lvl"   : 50,
	"skill_name" : "���绯��",
	"damage_type":	"����"
]),
([	"action": "$N������ǰһԾ��һ�С�Ұ����ס�������$w�ֻ�$n����",
	"force" : 110,
	"dodge" : 30,
	"damage": 55,
	"lvl"   : 60,
	"skill_name" : "Ұ�����",
	"damage_type":	"����"
]),
([	"action": "$N������ǰ��һ�С���Ӱɨ�ס�������$w��������$nǰ��",
	"force" : 130,
	"dodge" : 20,
	"damage": 60,
	"lvl"   : 70,
	"skill_name" : "��Ӱɨ��",
	"damage_type":	"����"
])
});

int valid_enable(string usage) { return (usage == "whip") || (usage == "parry"); }

int valid_learn(object me)
{
	object weapon;

	if ( !objectp(weapon = me->query_temp("weapon"))
	|| ( string)weapon->query("skill_type") != "whip" )
		return notify_fail("���������һ������������������\n");

	if( (int)me->query("max_neili") < 300 )
		return notify_fail("����������㣬û�а취����糾��, ����Щ���������ɡ�\n");

	if ((int)me->query_skill("force") < 60)
		return notify_fail("����ڹ����̫ǳ��\n");

	if ((int)me->query_skill("whip", 1) < (int)me->query_skill("qiufeng-chenfa", 1))
		return notify_fail("��Ļ����޷�����㣬���������������糾����\n");
	return 1;
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
	level = (int) me->query_skill("qiufeng-chenfa", 1);
	for (i = sizeof(action); i > 0; i--)
		if (level > action[i-1]["lvl"])
			return action[NewRandom(i, 20, level / 5)];
}

int practice_skill(object me)
{
	object weapon;

	if (!objectp(weapon = me->query_temp("weapon"))
	|| (string)weapon->query("skill_type") != "whip")
		return notify_fail("��ʹ�õ��������ԡ�\n");

	if ((int)me->query("qi") < 50)
		return notify_fail("���������������糾����\n");

	if ((int)me->query("neili") < 30)
		return notify_fail("���������������糾����\n");

	me->receive_damage("qi", 35);
	me->add("neili", -10);
	return 1;
}

string perform_action_file(string action)
{
	if ( this_player()->query_skill("qiufeng-chenfa", 1) >= 40 )
		return __DIR__"qiufeng-chenfa/" + action;
}
