// jinshe-jian.c

#include <ansi.h>

inherit SKILL;

mapping *action = ({
([	"skill_name": "�����Ӱ",
	"action": "$Nʹһ�С������Ӱ�������е�$w��һ��ָ������$n��$l��������",
	"force" : 190,
	"attack": 25,
	"dodge" : 20,
	"parry" : 10,
	"damage": 45,
	"damage_type": "����"
]),
([	"skill_name": "��Ӱ���",
	"action": "$Nʹһ�С���Ӱ�����������$w�����������$n��$l��������",
	"force" : 220,
	"attack": 22,
	"dodge" : 10,
	"parry" : 20,
	"damage": 47,
	"damage_type": "����"
]),
([	"skill_name": "ѩ�ط���",
	"action": "$N����һת����������Ծ������$w�鶯زԾ��һ�С�ѩ�ط��ߡ�����$n��$l",
	"force" : 170,
	"attack": 26,
	"dodge" : 10,
	"parry" : 20,
	"damage": 45,
	"damage_type": "����"
]),
([	"skill_name": "��������",
	"action": "$N����һת��һ�С��������š������е�$w����������$n��$l���˹�ȥ",
	"force" : 210,
	"attack": 18,
	"dodge" : 10,
	"parry" : 20,
	"damage": 52,
	"damage_type": "����"
]),
([	"skill_name": "���߿���",
	"action": "$N����һ����һ�С����߿��衹��$wЮ���������⣬����޷�����$n��$l",
	"force" : 180,
	"attack": 22,
	"dodge" : 10,
	"parry" : 20,
	"damage": 55,
	"damage_type": "����"
]),
([	"skill_name": "���ߵ���",
	"action": "$N������������񴦣�һ�С����ߵ�������$w���޷����ݵ��ٶ�ֱ��$n��$l",
	"force" : 250,
	"attack": 25,
	"dodge" : 10,
	"parry" : 20,
	"damage": 50,
	"damage_type": "����"
]),
([	"skill_name": "�������",
	"action": "$N����һ����һ�С�������ǡ������е�$w�������ϴ���$n��$l",
	"force" : 220,
	"attack": 24,
	"dodge" : 10,
	"parry" : 20,
	"damage": 45,
	"damage_type": "����"
]),
([	"skill_name": "���߻���",
	"action": "$N����$w���Ⱪ����һ�С����߻���������ǧ����Ы��$n$lҧȥ",
	"force" : 210,
	"attack": 31,
	"dodge" : 10,
	"parry" : 20,
	"damage": 60,
	"damage_type": "����"
]),
});

int valid_learn(object me)
{
	if ((int)me->query("max_neili") < 700)
		return notify_fail("�������������û�а취�����߽�����\n");

	if ((int)me->query_skill("force") < 90)
		return notify_fail("����ڹ���򲻹���û�а취�����߽�����\n");

	if ((int)me->query_skill("sword", 1) < (int)me->query_skill("jinshe-jian", 1))
		return notify_fail("��Ļ�������ˮƽ���ޣ��޷���������Ľ��߽�����\n");

	return 1;
}

int valid_enable(string usage)
{
	return usage == "sword" || usage == "parry";
}

string query_skill_name(int level)
{
	return action[random(sizeof(action))]["skill_name"];
}

mapping query_action(object me, object weapon)
{
	return action[random(sizeof(action))];
}

int practice_skill(object me)
{
	object ob;

	if (! (ob = me->query_temp("weapon")) ||
	    (string)ob->query("skill_type") != "sword")
		return notify_fail("���������һ�ѽ�������������\n");

	if ((int)me->query("qi") < 70)
		return notify_fail("�����������û�а취��ϰ���߽�����\n");

	if ((int)me->query("neili") < 60)
		return notify_fail("�������������û�а취��ϰ���߽�����\n");

	me->receive_damage("qi", 50);
	me->add("neili", -48);
	return 1;
}

string perform_action_file(string action)
{
	return __DIR__"jinshe-jian/" + action;
}
