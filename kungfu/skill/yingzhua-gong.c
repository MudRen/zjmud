// yingzhua-gong.c -ӥצ��
// modified by Venus Oct.1997

inherit SHAOLIN_SKILL;

mapping *action = ({
([      "action": "$Nȫ��εض��𣬰����һ�����һʽ����ӥϮ�á���Ѹ�͵�ץ��$n��$l",
	"force" : 100,
	"attack": 20,
	"dodge" : 5,
	"parry" : 15,
	"damage": 10,
	"lvl" : 0,
	"skills_name" : "��ӥϮ��",
	"damage_type" : "����"
]),
([      "action": "$N����ֱ����˫��ƽ�죬һʽ����ӥչ�᡹��˫צһǰһ��£��$n��$l",
	"force" : 120,
	"attack": 40,
	"dodge" : 10,
	"parry" : 22,
	"damage": 15,
	"lvl" : 30,
	"skills_name" : "��ӥչ��",
	"damage_type" : "����"
]),
([      "action": "$Nһʽ���γ��ɡ���ȫ����б��ƽ�ɣ�����һ����˫צ����$n�ļ�ͷ",
	"force" : 150,
	"attack": 50,
	"dodge" : 10,
	"parry" : 28,
	"damage": 20,
	"lvl" : 60,
	"skills_name" : "�γ���",
	"damage_type" : "����"
]),
([      "action": "$N˫צ�����Ͼ٣�ʹһʽ��ӭ��������һ�����ֱ�Ϯ��$n����Ҹ����",
	"force" : 180,
	"attack": 55,
	"dodge" : 15,
	"parry" : 35,
	"damage": 35,
	"lvl" : 80,
	"skills_name" : "ӭ������",
	"damage_type" : "����"
]),
([      "action": "$Nȫ�������ǰ��һʽ��������צ������צͻ�������Ȱ�ץ��$n���ؿ�",
	"force" : 220,
	"attack": 65,
	"dodge" : 20,
	"parry" : 38,
	"damage": 45,
	"lvl" : 100,
	"skills_name" : "������צ",
	"damage_type" : "����"
]),
([      "action": "$N���ػ��У�һʽ������հ�ա�������Ϯ�����д�Ѩ�����ַ�ץ$n���ɲ�",
	"force" : 250,
	"attack": 60,
	"dodge" : 25,
	"parry" : 45,
	"damage": 50,
	"lvl" : 120,
	"skills_name" : "����հ��",
	"damage_type" : "����"
]),
([      "action": "$N��������צ���棬һʽ���������ա��������������ƿն�����Ѹ���ޱȵػ���$n",
	"force" : 280,
	"attack": 75,
	"dodge" : 25,
	"parry" : 52,
	"damage": 55,
	"lvl" : 140,
	"skills_name" : "��ӥϮ��",
	"damage_type" : "����"
]),
([      "action": "$N�ڿո߷����ɣ�һʽ��ӥ�����������ж�ʱ�Գ�һ������צӰ����������$n",
	"force" : 310,
	"attack": 80,
	"dodge" : 40,
	"parry" : 60,
	"damage": 60,
	"lvl" : 160,
	"skills_name" : "��ӥϮ��",
	"damage_type" : "����"
])
});

int valid_enable(string usage) { return usage == "claw" || usage == "parry"; }

int valid_combine(string combo) { return combo == "fengyun-shou"; }

int valid_learn(object me)
{
	if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
		return notify_fail("��ӥצ��������֡�\n");

	if ((int)me->query_skill("force") < 50)
		return notify_fail("����ڹ���򲻹����޷�ѧӥצ����\n");

	if ((int)me->query("max_neili") < 250)
		return notify_fail("�������̫�����޷���ӥצ����\n");

	if ((int)me->query_skill("claw", 1) < (int)me->query_skill("yingzhua-gong", 1))
		return notify_fail("��Ļ���ץ�����ˮƽ���ޣ��޷����������ӥצ����\n");

	return 1;
}

string query_skill_name(int level)
{
	int i;
	for(i = sizeof(action)-1; i >= 0; i--)
		if (level >= action[i]["lvl"])
			return action[i]["skill_name"];
}

mapping query_action(object me, object weapon)
{
	int i, level;
	level = (int) me->query_skill("yingzhua-gong",1);
	for(i = sizeof(action); i > 0; i--)
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

	if ((int)me->query("neili") < 70)
		return notify_fail("�������������ӥצ����\n");

	me->receive_damage("qi", 60);
	me->add("neili", -67);
	return 1;
}

string perform_action_file(string action)
{
	return __DIR__"yingzhua-gong/" + action;
}
