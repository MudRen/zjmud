// lanhua-shou.c -������Ѩ��
// Modified by Venus Oct.1997
#include <ansi.h>
inherit SKILL;

mapping *action = ({
([      "action": "$N������ָ�ֿ���΢΢һ�����ٲ�£����һ����һʽ�������Ƶ�����"
		  "����$n������ҪѨ",
	"force" : 100,
	"dodge" : 15,
	"damage": 15,
	"lvl"   : 0,
	"damage_type" : "����",
	"skill_name" : "�����Ƶ�"
]),
([      "action": "$N��������$n��һʽ�����Ʊ��¡���������ָ������������$n����ǰ��Ѩ",
	"force" : 130,
	"dodge" : 20,
	"damage": 30,
	"lvl"   : 30,
	"damage_type" : "����",
	"skill_name" : "���Ʊ���"
]),
([      "action": "$Nʹһʽ�������������������鹥�����ֲ�ָбǰ����������$n�ļ羮Ѩ",
	"force" : 170,
	"dodge" : 25,
	"damage": 40,
	"lvl"   : 60,
	"damage_type" : "����",
	"skill_name" : "��������"
]),
([      "action": "$N���ƻ��أ�΢΢�������ƹ��ϣ�һʽ������ŪӰ������������$n����ͻѨ",
	"force" : 190,
	"dodge" : 25,
	"damage": 45,
	"lvl"   : 80,
	"damage_type" : "����",
	"skill_name" : "����ŪӰ"
]),
([      "action": "$Nʹһʽ���������塹����Ӱ����������$n����͵�����$n�Ĵ�׵Ѩ",
	"force" : 220,
	"dodge" : 30,
	"damage": 50,
	"lvl"   : 100,
	"damage_type" : "����",
	"skill_name" : "��������"
]),
([      "action": "$N���������������ϵ�����ǰ������ָ�η��ϣ�΢��һ������һʽ��"
		  "�����뷼����˫���������һ��������������������$n�Ļ��ǡ���ᡢ�Ϲ�������Ѩ",
	"force" : 250,
	"dodge" : 35,
	"damage": 55,
	"lvl"   : 120,
	"damage_type" : "����",
	"skill_name" : "�����뷼"
]),
([      "action": "$N����ƮƮ������Ծ��һʽ����Ӱ���㡹���Ӹ����£�����һ����"
		  "������$n�İٻ��Ѩ",
	"force" : 280,
	"dodge" : 40,
	"damage": 65,
	"lvl"   : 140,
	"damage_type" : "����",
	"skill_name" : "��Ӱ����"
]),
([      "action": "$N����ʩչ����������Բ����˫�ּ�����һ�����ľ�������$n������"
		  "�¸���ҪѨ",
	"force" : 320,
	"dodge" : 45,
	"damage": 70,
	"lvl"   : 160,
	"damage_type" : "����",
	"skill_name" : "������Բ"
])
});

int valid_enable(string usage) { return usage == "hand" ||  usage == "parry"; }

int valid_combine(string combo) { return combo == "tanzhi-shentong"; }

int valid_learn(object me)
{
	if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
		return notify_fail(HIC"��������Ѩ�ֱ�����֡�"NOR"\n");

	if ((int)me->query_skill("force") < 60)
		return notify_fail("����ڹ���򲻹����޷�ѧ������Ѩ�֡�\n");

	if ((int)me->query("max_neili") < 450)
		return notify_fail("�������̫�����޷���������Ѩ�֡�\n");

	if ((int)me->query_skill("hand", 1) < 50)
		return notify_fail("��Ļ����ַ�̫��޷�ѧϰ������Ѩ�֡�\n");

	if ((int)me->query_skill("hand", 1) < (int)me->query_skill("lanhua-shou", 1))
		return notify_fail("��Ļ����ַ���򲻹����޷����������������Ѩ�֡�\n");

	return 1;
}

string query_skill_name(int level)
{
	int i;
	for (i = sizeof(action) - 1; i >= 0; i--)
		if (level >= action[i]["lvl"])
			return action[i]["skill_name"];
}

mapping query_action(object me, object weapon)
{
	int i, level;
	level = (int)me->query_skill("lanhua-shou", 1);
	for (i = sizeof(action); i > 0; i--)
		if(level > action[i - 1]["lvl"])
			return action[NewRandom(i, 20, level / 5)];
}

int practice_skill(object me)
{
	if ((int)me->query("qi") < 60)
		return notify_fail("�������̫���ˣ��޷���������Ѩ�֡�\n");

	if ((int)me->query("neili") < 60)
		return notify_fail("�������̫���ˣ��޷���������Ѩ�֡�\n");

	me->receive_damage("qi", 50);
	me->add("neili", -53);
	return 1;
}

string perform_action_file(string action)
{
	return __DIR__"lanhua-shou/" + action;
}
