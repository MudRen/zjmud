// fengyun-shou.c -������
// Modified by Venus Oct.1997

inherit SHAOLIN_SKILL;

mapping *action = ({
([      "action": "$Nһʽ���������ա������ƻ�צ����ָ�繳��ֱ��$n������ҪѨ",
	"force" : 90,
	"attack": 25,
	"dodge" : 5,
	"damage": 15,
	"parry" : 40,
	"lvl"   : 0,
	"skill_name" : "��������",
	"damage_type" : "����"
]),
([      "action": "$N������Σ�һʽ���һ����ơ�����������ֱ��������$n�ļ羮��Ѩ",
	"force" : 120,
	"attack": 32,
	"dodge" : 10,
	"damage": 20,
	"parry" : 42,
	"lvl"   : 30,
	"skill_name" : "�һ�����",
	"damage_type" : "����"
]),
([      "action": "$Nʹһʽ���������󡹣���ָ��������ò�ʩ������$n����·Ҫ��",
	"force" : 150,
	"attack": 41,
	"dodge" : 15,
	"parry" : 45,
	"damage": 30,
	"lvl"   : 60,
	"skill_name" : "��������",
	"damage_type" : "����"
]),
([      "action": "$N����ӥץ�������߾٣�һʽ����Ŀ�ѻԡ�����$n���нڴ���",
	"force" : 180,
	"attack": 45,
	"dodge" : 20,
	"parry" : 46,
	"damage": 40,
	"lvl"   : 90,
	"skill_name" : "��Ŀ�ѻ�",
	"damage_type" : "����"
]),
([      "action": "$Nʹһʽ�������ķ���������˷�����������Ӱ��һצͻ����ץ��$n���ؿ�",
	"force" : 220,
	"attack": 53,
	"dodge" : 25,
	"parry" : 54,
	"damage": 50,
	"lvl" : 120,
	"skill_name" : "�����ķ�",
	"damage_type" : "����"
]),
([      "action": "$N���ֻ��ۣ�ȫ��ؽ�žž���죬һʽ��ˮ�����ɡ�������$n��$l",
	"force" : 270,
	"attack": 58,
	"dodge" : 30,
	"parry" : 58,
	"damage": 60,
	"lvl" : 140,
	"skill_name" : "ˮ������",
	"damage_type" : "����"
]),
([      "action": "$Nһʽ��ɽ�����ܡ���ʮָ���죬������հ������$n��ȫ��ҪѨ",
	"force" : 330,
	"attack": 70,
	"dodge" : 35,
	"parry" : 62,
	"damage": 70,
	"lvl" : 160,
	"skill_name" : "ɽ������",
	"damage_type" : "����"
]),
([      "action": "$N�������ţ�һʽ��������ġ�����һ�������У�˫��ͬʱ����$n"
		  "���ߵ���Ѩ",
	"force" : 360,
	"attack": 77,
	"dodge" : 50,
	"parry" : 65,
	"damage": 80,
	"lvl" : 180,
	"skill_name" : "�������",
	"damage_type" : "����"
])
});

int valid_enable(string usage) { return usage == "hand" || usage == "parry"; }

int valid_combine(string combo) { return combo == "yingzhua-gong"; }

int valid_learn(object me)
{
	if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
		return notify_fail("�������ֱ�����֡�\n");

	if ((int)me->query_skill("force") < 40)
		return notify_fail("����ڹ���򲻹����޷�ѧ�����֡�\n");

	if ((int)me->query("max_neili") < 200)
		return notify_fail("�������̫�����޷��������֡�\n");

	if ((int)me->query_skill("hand", 1) < (int)me->query_skill("fengyun-shou", 1))
		return notify_fail("��Ļ����ַ�ˮƽ���ޣ��޷���������ķ����֡�\n");

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
	level = (int) me->query_skill("fengyun-shou",1);
	for (i = sizeof(action); i > 0; i--)
		if (level > action[i-1]["lvl"])
			return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
	if (me->query_temp("weapon") ||
	    me->query_temp("secondary_weapon"))
		return notify_fail("����������ϰ��\n");

	if ((int)me->query("qi") < 70)
		return notify_fail("�������̫���ˡ�\n");

	if ((int)me->query("neili") < 80)
		return notify_fail("������������������֡�\n");

	me->receive_damage("qi", 65);
	me->add("neili", -69);
	return 1;
}

string perform_action_file(string action)
{
	return __DIR__"fengyun-shou/" + action;
}
