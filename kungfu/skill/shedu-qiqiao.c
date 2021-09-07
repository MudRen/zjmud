// shedu-qiqiao.c
inherit SKILL;

mapping *action = ({
([      "action" : "$N��ָ�ӳ���һʽ������ͦ��������$n����Ե",
	"force" : 80,
	"dodge" : 5,
	"lvl" : 0,
	"skill_name" : "����ͦ��",
	"damage_type" : "����"
]),
([      "action" : "$Nȫ��֮������һָ��һʽ���������š���ָ��$n����ǰ",
	"force" : 100,
	"dodge" : 5,
	"lvl" : 15,
	"damage" : 25,
	"skill_name" : "��������",
	"damage_type" : "����"
]),
([      "action" : "$N�����������Ѩ������һʽ�����߰�β������$n��$l����",
	"force" : 120,
	"dodge" : 8,
	"lvl" : 25,
	"damage" : 55,
	"skill_name" : "���߰�β",
	"damage_type" : "����"
]),
([      "action" : "$N˫Ŀŭ�ӣ�һʽ�����߲�ʳ����˫ָ����$n�Ķ�����硢�ۡ��ء���",
	"force" : 150,
	"dodge" : 5,
	"damage": 65,
	"lvl" : 45,
	"skill_name" : "���߲�ʳ",
	"damage_type" : "����"
]),
([      "action" : "$Nһʽ���������С��������������⣬��ָ���Ƶ���$n��$l",
	"force" : 180,
	"dodge" : 15,
	"damage": 80,
	"lvl" : 60,
	"skill_name" : "��������",
	"damage_type" : "����"
]),
([      "action" : "$N���������ʮָ�濪��һʽ�����߳�������Сָ����$n��̫ԨѨ",
	"force" : 200,
	"dodge" : 20,
	"damage": 100,
	"lvl" : 70,
	"skill_name" : "���߳���",
	"damage_type" : "����"
]),
([      "action" : "$N˫�ų�������������һʽ��ǧ�߲�������$n��ȫ��",
	"force" : 220,
	"dodge" : 25,
	"damage": 120,
	"lvl" : 80,
	"skill_name" : "ǧ�߲���",
	"damage_type" : "����"
]),
});

int valid_enable(string usage) { return usage=="finger" || usage=="poison"; }

int valid_combine(string combo) { return combo == "lingshe-quan"; }

int valid_learn(object me)
{
	if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
		return notify_fail("���߶����ɱ�����֡�\n");

	if ((int)me->query_skill("force") < 80)
		return notify_fail("����ڹ���򲻹����޷�ѧ�߶����ɡ�\n");

	if ((int)me->query("max_neili") < 350)
		return notify_fail("�������̫�����޷����߶����ɡ�\n");

	if ((int)me->query_skill("poison", 1) < 30)
		return notify_fail("��Ļ���������򲻹����޷�ѧ�߶����ɡ�\n");

	if ((int)me->query_skill("poison", 1) < (int)me->query_skill("shedu-qiqiao", 1))
		return notify_fail("��Ļ�������ˮƽ���ޣ��޷�����������߶����ɡ�\n");

	if ((int)me->query_skill("finger", 1) < (int)me->query_skill("shedu-qiqiao", 1))
		return notify_fail("��Ļ���ָ��ˮƽ���ޣ��޷�����������߶����ɡ�\n");

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
	level = (int) me->query_skill("shedu-qiqiao",1);
	for (i = sizeof(action); i > 0; i--)
		if (level > action[i-1]["lvl"])
			return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
	if ((int)me->query("qi") < 70)
		return notify_fail("�������̫���ˡ�\n");

	if ((int)me->query("neili") < 55)
		return notify_fail("��������������߶����ɡ�\n");

	me->receive_damage("qi", 52);
	me->add("neili", -44);
	return 1;
}

string perform_action_file(string action)
{
	return __DIR__"shedu-qiqiao/" + action;
}
