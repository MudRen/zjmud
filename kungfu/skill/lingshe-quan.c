// lingshe-quan ����ȭ

inherit SKILL;

mapping *action = ({
([	"action": "$Nһʽ�����߳�������������Σ���������ͻȻ����$n�ı����Ѩ",
	"force" : 60,
	"attack": 40,
	"dodge" : 30,
	"lvl"   : 0,
	"skill_name" : "���߳���",
	"damage_type" : "����"
]),
([	"action": "$N����һ�Σ�һʽ����ͷ��β������������$n�ļ�ͷ����ȭ����$n���ؿ�",
	"force" : 100,
	"attack": 45,
	"dodge" : 35,
	"lvl"   : 30,
	"skill_name" : "��ͷ��β",
	"damage_type" : "����"
]),
([	"action": "$Nһʽ���������㡹�����ֻ�£��צ��һ���־����$n���ʺ�Ҫ��",
	"force" : 130,
	"attack": 50,
	"dodge" : 40,
	"damage": 5,
	"lvl"   : 50,
	"skill_name" : "��������",
	"damage_type" : "����"
]),
([	"action": "$N�������У�����ֱ����һʽ��������Ӱ������Ʈ��������$n������",
	"force" : 160,
	"attack": 55,
	"dodge" : 50,
	"damage": 10,
	"lvl"   : 70,
	"skill_name" : "������Ӱ",
	"damage_type" : "����"
]),
([	"action": "$Nʹһʽ��������ܡ�����ȭ�ϸ�����̽��ͻ����ץ��$n���ɲ�",
	"force" : 210,
	"attack": 60,
	"dodge" : 65,
	"damage": 15,
	"lvl"   : 90,
	"skill_name" : "�������",
	"damage_type" : "����"
]),
([	"action": "$Nһʽ���������񡹣�ʮָ����������ʵʵ��Ϯ��$n��ȫ��ҪѨ",
	"force" : 250,
	"attack": 70,
	"dodge" : 75,
	"damage": 25,
	"lvl"   : 120,
	"skill_name" : "��������",
	"damage_type" : "����"
]),
([	"action" : "$N˫�ֱ�ȭ��һʽ��������ӿ������Ӱ���ɣ�ͬʱ��$nʩ���žŰ�ʮһ��",
	"force" : 280,
	"attack": 80,
	"dodge" : 75,
	"damage": 30,
	"lvl"   : 140,
	"skill_name" : "������ӿ",
	"damage_type" : "����"
]),
([	"action" : "$Nһʽ���������š���ȭ���������֣��������ޣ�����������$n�ĵ���",
	"force" : 300,
	"attack": 90,
	"dodge" : 80,
	"damage": 40,
	"lvl"   : 160,
	"skill_name" : "��������",
	"damage_type" : "����"
]),
});

int valid_enable(string usage) { return usage=="cuff" || usage=="strike" || usage=="parry"; }

int valid_combine(string combo) { return combo=="shedu-qiqiao"; }

int valid_learn(object me)
{
	if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
		return notify_fail("������ȭ������֡�\n");

	if ((int)me->query_skill("hamagong", 1) < 30)
		return notify_fail("��ĸ�󡹦��򲻹����޷�ѧ����ȭ��\n");

	if ((int)me->query("max_neili") < 500)
		return notify_fail("�������̫�����޷�������ȭ��\n");

	if ((int)me->query_skill("cuff", 1) < (int)me->query_skill("lingshe-quan", 1))
		return notify_fail("��Ļ���ȭ��ˮƽ���ޣ��޷��������������ȭ����\n");

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
	level   = (int) me->query_skill("lingshe-quan", 1);
	for(i = sizeof(action); i > 0; i--)
		if(level > action[i-1]["lvl"])
			return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
	if ((int)me->query("qi") < 60)
		return notify_fail("�������̫���ˡ�\n");

	if ((int)me->query("neili") < 60)
		return notify_fail("�����������������ȭ��\n");

	me->receive_damage("qi", 55);
	me->add("neili", -55);
	return 1;
}

string perform_action_file(string action)
{
	return __DIR__"lingshe-quan/" + action;
}
