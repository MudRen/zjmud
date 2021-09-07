// qianye-shou.c ����ǧҶ��
// modified by Venus Oct.1997

inherit SHAOLIN_SKILL;

mapping *action = ({
([      "action" : "$Nһʽ���Ϻ���𡹣�������Σ���������ͻȻ����$n�ı����Ѩ",
	"force"  : 90,
	"attack" : 15,
	"dodge"  : 10,
	"parry"  : 25,
	"lvl"    : 0,
	"skill_name" : "�Ϻ����",
	"damage_type" : "����"
]),
([      "action" : "$N����һ�Σ�һʽ����������������������$n�ļ�ͷ����ȭ����$n���ؿ�",
	"force"  : 110,
	"attack" : 18,
	"dodge"  : 10,
	"parry"  : 35,
	"lvl"    : 30,
	"skill_name" : "��������",
	"damage_type" : "����"
]),
([      "action" : "$Nһʽ�����������������ֻ�£��צ��һ���־����$n���ʺ�Ҫ��",
	"force"  : 140,
	"attack" : 25,
	"dodge"  : 20,
	"parry"  : 50,
	"damage" : 5,
	"lvl"    : 60,
	"skill_name" : "��������",
	"damage_type" : "����"
]),
([      "action" : "$N�������У�����ֱ����һʽ�������Ӱ������Ʈ��������$n������",
	"force"  : 180,
	"attack" : 31,
	"dodge"  : 20,
	"parry"  : 60,
	"damage" : 10,
	"lvl"    : 90,
	"skill_name" : "�����Ӱ",
	"damage_type" : "����"
]),
([      "action" : "$Nʹһʽ��ˮ��׽�¡�����ȭ�ϸ�����̽��ͻ����ץ��$n���ɲ�",
	"force"  : 240,
	"attack" : 42,
	"dodge"  : 30,
	"parry"  : 62,
	"damage" : 15,
	"lvl"    : 110,
	"skill_name" : "ˮ��׽��",
	"damage_type" : "����"
]),
([      "action" : "$N˫ȭ���裬һʽ������ȥ���������ֻ��ۣ�£��Ȧ״���ͻ�$n�����",
	"force"  : 310,
	"attack" : 55,
	"dodge"  : 30,
	"parry"  : 67,
	"damage" : 20,
	"lvl"    : 130,
	"skill_name" : "����ȥ��",
	"damage_type" : "����"
]),
([      "action" : "$Nһʽ��ˮ�ݳ�û����ʮָ����������ʵʵ��Ϯ��$n��ȫ��ҪѨ",  
	"force"  : 340,
	"attack" : 58,
	"dodge"  : 35,
	"parry"  : 71,
	"damage" : 25,
	"lvl"    : 140,
	"skill_name" : "ˮ�ݳ�û",
	"damage_type" : "����"
]),
([      "action" : "$N˫�ֱ�ȭ��һʽ����������������Ӱ���ɣ�ͬʱ��$nʩ���žŰ�ʮһ��",
	"force"  : 380,
	"attack" : 62,
	"dodge"  : 41,
	"parry"  : 72,
	"damage" : 30,
	"lvl"    : 150,
	"skill_name" : "��������",
	"damage_type" : "����"
]),
([      "action" : "$Nһʽ������տա���ȭ���������֣��������ޣ�����������$n�ĵ���",
	"force"  : 410,
	"attack" : 69,
	"dodge"  : 40,
	"parry"  : 78,
	"damage" : 35,
	"lvl"    : 160,
	"skill_name" : "����տ�",
	"damage_type" : "����"
]),
});

int valid_enable(string usage) { return usage == "hand" || usage == "parry"; }

int valid_combine(string combo) { return combo == "longzhua-gong"; }

int valid_learn(object me)
{
	if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
		return notify_fail("������ǧҶ�ֱ�����֡�\n");

	if ((int)me->query_skill("force") < 40)
		return notify_fail("����ڹ���򲻹����޷�ѧ����ǧҶ�֡�\n");

	if ((int)me->query("max_neili") < 200)
		return notify_fail("�������̫�����޷�������ǧҶ�֡�\n");

	if ((int)me->query_skill("hand", 1) < (int)me->query_skill("qianye-shou", 1))
		return notify_fail("��Ļ����ַ�ˮƽ���ޣ��޷��������������ǧҶ�֡�\n");

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
	level = (int) me->query_skill("qianye-shou",1);
	for (i = sizeof(action); i > 0; i--)
		if (level > action[i-1]["lvl"])
			return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
	if (me->query_temp("weapon") ||
	    me->query_temp("secondary_weapon"))
		return notify_fail("����������ϰ��\n");

	if ((int)me->query("qi") < 75)
		return notify_fail("�������̫���ˡ�\n");

	if ((int)me->query("neili") < 70)
		return notify_fail("�����������������ǧҶ�֡�\n");

	me->receive_damage("qi", 68);
	me->add("neili", -64);
	return 1;
}

string perform_action_file(string action)
{
	return __DIR__"qianye-shou/" + action;
}
