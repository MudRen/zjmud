// yanxing-dao.c ���е���
// modified by Venus Oct.1997
#include <ansi.h>
inherit SKILL;

mapping *action = ({
([      "skill_name" : "���־�",
	"action": "$Nʹ�������־����������������е�бб������һ���׹�����$n��$l",
	"force" : 60,
	"attack": 10,
	"dodge" : 30,
	"damage": 15,
	"lvl"   : 0,
	"damage_type" : "����",
]),
([      "skill_name" : "���־�",
	"action": "$Nʹ�������־��������ֻ��������һ�������ֵ���ͷֱ��������һ"
		  "����âֱ��$n��$l����",
	"force" : 80,
	"attack": 15,
	"dodge" : 15,
	"damage": 21,
	"lvl"   : 10,
	"damage_type" : "����",
]),
([      "skill_name" : "���־�",
	"action": "$Nʹ�������־��������ֺ󳷣���б���мܣ�˳���¶磬������Ҹ��"
		  "��������ס�Է����󣬵��ⲻָͣ��$n��$l",
	"force" : 100,
	"dodge" : 5,
	"damage": 25,
	"lvl"   : 20,
	"damage_type" : "����",
]),
([      "skill_name" : "���־�",
	"action": "$Nʹ�������־�����������ϣ�����ͻ�������ִ����Է�$n���У���"
		  "�ֵ��͵ص�������$n���ڵ�����",
	"force" : 120,
	"attack": 25,
	"dodge" : -5,
	"damage": 32,
	"lvl"   : 30,
	"damage_type" : "����",
]),
([      "skill_name" : "���־�",
	"action": "$Nʹ�������־������������էȻһ�������ּ��ٲ�ס$n���֣�����"
		  "��һ�������磬������ס$n��$l",
	"force" : 140,
	"attack": 25,
	"dodge" : 20,
	"damage": 37,
	"lvl"   : 40,
	"damage_type" : "����",
]),
([      "skill_name" : "���־�",
	"action": "$Nʹ�������־����������䣬����Ʈ����׽����͸����$n�ۻ�����"
		  "֮�ʣ����ֵ��ⷴ����$n��$l",
	"force" : 160,
	"attack": 25,
	"dodge" : 15,
	"damage": 43,
	"lvl"   : 50,
	"damage_type" : "����",
]),
([      "skill_name" : "̽�־�",
	"action": "$Nʹ����̽�־�������ӯ��һ����ת�����ų��������ֵ�������ǰ"
		  "��ֱ��$n��$l",
	"force" : 180,
	"attack": 25,
	"dodge" : 20,
	"damage": 57,
	"lvl" : 60,
	"damage_type" : "����",
]),
([      "skill_name" : "���־�",
	"action": "$N����ʹ�������־�����������ת�������Ķ�������$n��ת�����е�"
		  "��������$n��ȫ���������Լ����µĵ����У��޴�����",
	"force" : 200,
	"attack": 28,
	"dodge" : 25,
	"damage": 60,
	"lvl" : 70,
	"damage_type" : "����",
]),
([      "skill_name" : "���־�",
	"action": "$N����ʹ�������־���������ص�������$nǰ����һ�������ⶸ�֣�"
		  "����ǧ���������ڶ���",
	"force" : 230,
	"attack": 33,
	"dodge" : 25,
	"damage": 62,
	"lvl" : 80,
	"damage_type" : "����",
]),
([      "skill_name" : "���־�",
	"action": "$N����ʹ�������־�����˫�ֽ��棬������߫��$nʵ�ڿ����嵶����"
		  "���˺����ܣ�ֻ��һ����ֱ�ƹ���",
	"force" : 250,
	"attack": 38,
	"dodge" : 25,
	"damage": 70,
	"lvl" : 90,
	"damage_type" : "����",
]),
});

int valid_enable(string usage) { return usage == "blade" ||  usage=="parry"; }

int valid_learn(object me)
{
	if ((int)me->query("max_neili") < 100)
		return notify_fail("�������������\n");

	if ((int)me->query_skill("force") < 50)
		return notify_fail("����ڹ���򲻹���\n");

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

	level = (int)me->query_skill("yanxing-dao", 1);
	for(i = sizeof(action); i > 0; i--)
		if(level > action[i-1]["lvl"])
		return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
	object weapon;

	if (! objectp(weapon = me->query_temp("weapon")) ||
	    (string)weapon->query("skill_type") != "blade")
		return notify_fail("��ʹ�õ��������ԡ�\n");

	if ((int)me->query("qi") < 60)
		return notify_fail("����������������е���\n");

	if ((int)me->query("neili") < 60)
		return notify_fail("����������������е���\n");

	me->receive_damage("qi", 53);
	me->add("neili", -51);
	return 1;
}

string perform_action_file(string action)
{
    return __DIR__"yanxing-dao/" + action;
}
