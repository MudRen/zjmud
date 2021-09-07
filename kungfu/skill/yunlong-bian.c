// yunlong-bian.c �����޷�

#include <ansi.h>

inherit SKILL;

mapping *action = ({
([	"action":		"$N����һ�һ�С�����ٵء�������$w���ñ�ֱ����׼$n��ͷ����",
	"force":		100,
	"dodge":		10,
	"lvl" : 0,
	"skill_name" : "����ٵ�",
	"damage_type":	"����"
]),
([	"action":		"$N����һת��һ�С������ĺ���������$w��������ڿ�һ���͵ػ���$n̫��Ѩ",
	"force":		120,
	"dodge":		10,
	"damage":		5,
	"lvl" : 30,
	"skill_name" : "�����ĺ�",
	"damage_type":	"����"
]),
([	"action":		"$N৵�һ�����ޣ�һ�С�������ˮ��������$w���ñ�ֱ������$n˫��",
	"force":		140,
	"dodge":		30,
	"damage":		10,
	"lvl" : 60,
	"skill_name" : "������ˮ",
	"damage_type":	"����"
]),
([	"action":		"$N������ң�һ�С����Ƽ��ա�������$w��������Ӱ����ɽ������ɨ��$nȫ��",
	"force":		160,
	"dodge":		40,
	"damage":		20,
	"lvl" : 80,
	"skill_name" : "���Ƽ���",
	"damage_type":	"����"
]),
([	"action":		"$N��������һ�С���ɽ��ʯ��������$w��һ��ͭ����ֱ����$n",
	"force":		180,
	"dodge":		50,
	"damage":		30,
	"lvl" : 100,
	"skill_name" : "��ɽ��ʯ",
	"damage_type":	"����"
]),
([	"action":		"$N����һ�ӣ�һ�С����Χ����������$wֱ����$n����",
	"force":		200,
	"dodge":		-20,
	"damage":		35,
	"lvl" : 120,
	"skill_name" : "���Χ��",
	"damage_type":	"����"
]),
([	"action":		"$N�߸�Ծ��һ�С���Į���̡�������$w��ֱ��$n��ͷ����",
	"force":		220,
	"dodge":		-50,
	"damage":		40,
	"lvl" : 140,
	"skill_name" : "��Į����",
	"damage_type":	"����"
])
});

int valid_enable(string usage) { return (usage == "whip") || (usage == "parry"); }

int valid_learn(object me)
{
	object weapon;

	if ( !objectp(weapon = me->query_temp("weapon"))
	|| ( string)weapon->query("skill_type") != "whip" )
		return notify_fail("���������һ�����Ӳ������޷���\n");

	if( (int)me->query("max_neili") < 600 )
		return notify_fail("����������㣬û�а취�������޷���\n");

	if ((int)me->query_skill("force") < 80)
		return notify_fail("����ڹ����̫ǳ��\n");

	if ((int)me->query_skill("whip", 1) < 80)
		return notify_fail("��Ļ����޷����̫ǳ��\n");

	if ((int)me->query_skill("whip", 1) < (int)me->query_skill("yunlong-bian", 1))
		return notify_fail("��Ļ����޷�ˮƽ���ޣ��޷���������������޷���\n");

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
	level   = (int) me->query_skill("yunlong-bian",1);
	for(i = sizeof(action); i > 0; i--)
		if(level > action[i-1]["lvl"])
			return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
	object weapon;

	if (!objectp(weapon = me->query_temp("weapon"))
	|| (string)weapon->query("skill_type") != "whip")
		return notify_fail("��ʹ�õ��������ԡ�\n");

	if ((int)me->query("qi") < 60)
		return notify_fail("������������������޷���\n");

	if ((int)me->query("neili") < 60)
		return notify_fail("������������������޷���\n");

	me->receive_damage("qi", 45);
	me->add("neili", -48);
	return 1;
}

string perform_action_file(string action)
{
	return __DIR__"yunlong-bian/" + action;
}
