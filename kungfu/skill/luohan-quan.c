// luohan-quan.c �޺�ȭ
// modified by Venus Oct.1997
inherit SHAOLIN_SKILL;

mapping *action = ({
([      "action": "$N�����ϲ���һʽ����ݺ��ܡ��������ַֿ�����ȭΪ�ƣ�����$n��$l",
	"force" : 80,
	"attack": 12,
	"parry" : 14,
	"dodge" : 5,
	"lvl"   : 0,
	"skill_name" : "��ݺ���",
	"damage_type" : "����"
]),
([      "action": "$N�����̤��ȫ����ת��һ�С����ﳯ�����������͵ز���$n��$l",
	"force" : 100,
	"attack": 15,
	"parry" : 16,
	"dodge" : 10,
	"lvl"   : 8,
	"skill_name" : "���ﳯ��",
	"damage_type" : "����"
]),
([      "action": "$N˫�ִ󿪴��أ����߾٣�ʹһ�С����Ӷ�Ӧ����˫ȭ��$n��$l��ȥ",
	"force" : 120,
	"attack": 18,
	"parry" : 19,
	"dodge" : 5,
	"lvl"   : 15,
	"skill_name" : "���Ӷ�Ӧ",
	"damage_type" : "����"
]),
([      "action": "$N����Ȧ���������⵱�أ����ڳ��ϣ�һ�С�ƫ�����ǡ�����$n��$l",
	"force" : 140,
	"attack": 20,
	"parry" : 20,
	"dodge" : 10,
	"lvl"   : 24,
	"skill_name" : "ƫ������",
	"damage_type" : "����"
]),
([      "action": "$Nʹһ�С��ຣ��ͷ��������ǰ̽��˫�ֻ��˸���Ȧ������$n��$l",
	"force" : 150,
	"attack": 22,
	"parry" : 23,
	"dodge" : 15,
	"lvl"   : 33,
	"skill_name" : "�ຣ��ͷ",
	"damage_type" : "����"
]),
([      "action": "$N˫�ƻ�����һ�ǡ�Юɽ���������Ƴ���磬һ�����е�$n������",
	"force" : 170,
	"attack": 23,
	"parry" : 24,
	"dodge" : 10,
	"lvl"   : 42,
	"skill_name" : "Юɽ����",
	"damage_type" : "����"
]),
([      "action": "$Nʩ��������������˫ȭȭ����磬ͬʱ����$nͷ���أ�������Ҫ��",
	"force" : 200,
	"attack": 25,
	"parry" : 24,
	"dodge" : 5,
	"lvl"   : 50,
	"skill_name" : "������",
	"damage_type" : "����"
]),
([      "action": "$N����ڿۣ�����������һʽ�������������˫�����밴��$n���ؿ�",
	"force" : 210,
	"attack": 28,
	"parry" : 25,
	"dodge" : 10,
	"lvl"   : 58,
	"skill_name" : "�������",
	"damage_type" : "����"
]),
});

int valid_enable(string usage) { return usage == "cuff" || usage == "parry"; }

int valid_learn(object me)
{
	if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
		return notify_fail("���޺�ȭ������֡�\n");

	if ((int)me->query_skill("force") < 20)
		return notify_fail("����ڹ���򲻹����޷�ѧ�޺�ȭ��\n");

	if ((int)me->query("max_neili") < 50)
		return notify_fail("�������̫�����޷����޺�ȭ��\n");

	if ((int)me->query_skill("cuff", 1) < (int)me->query_skill("luohan-quan", 1))
		return notify_fail("��Ļ���ȭ��ˮƽ���ޣ��޷�����������޺�ȭ��\n");

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
	level = (int) me->query_skill("luohan-quan", 1);
	for (i = sizeof(action); i > 0; i--)
		if (level > action[i - 1]["lvl"])
			return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
	if (me->query_temp("weapon") ||
	    me->query_temp("secondary_weapon"))
		return notify_fail("����������ϰ��\n");

	if ((int)me->query("qi") < 35)
		return notify_fail("�������̫���ˡ�\n");

	if ((int)me->query("neili") < 10)
		return notify_fail("��������������޺�ȭ��\n");

	me->receive_damage("qi", 25);
	me->add("neili", -6);
	return 1;
}

string perform_action_file(string action)
{
	return __DIR__ "luohan-quan/" + action;
}
