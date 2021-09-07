// yunlong-zhua.c -����צ

inherit SKILL;

mapping *action = ({
([	"action" : "$Nȫ��εض��𣬰����һ�����һʽ����ӥϮ�á���Ѹ�͵�ץ��$n��$l",
	"force" : 70,
	"dodge" : 15,
	"parry" : 10,
	"damage": 10,
	"lvl" : 0,
	"skills_name" : "��ӥϮ��",
	"damage_type" : "ץ��"
]),
([	"action" : "$N����ֱ����˫��ƽ�죬һʽ����ӥչ�᡹��˫צһǰһ��£��$n��$l",
	"force" : 90,
	"dodge" : 20,
	"parry" : 15,
	"damage": 15,
	"lvl" : 30,
	"skills_name" : "��ӥչ��",
	"damage_type" : "ץ��"
]),
([	"action" : "$Nһʽ���γ�ӥ�ɡ���ȫ����б��ƽ�ɣ�����һ����˫צ����$n�ļ�ͷ",
	"force" : 100,
	"dodge" : 20,
	"parry" : 20,
	"damage": 20,
	"lvl" : 40,
	"skills_name" : "�γ�ӥ��",
	"damage_type" : "����"
]),
([	"action" : "$N˫צ�����Ͼ٣�ʹһʽ��ӭ��������һ�����ֱ�Ϯ��$n����Ҹ����",
	"force" : 120,
	"dodge" : 25,
	"parry" : 20,
	"damage": 30,
	"lvl" : 60,
	"skills_name" : "ӭ������",
	"damage_type" : "����"
]),
([	"action" : "$Nȫ�������ǰ��һʽ��������צ������צͻ�������Ȱ�ץ��$n���ؿ�",
	"force" : 140,
	"dodge" : 30,
	"parry" : 25,
	"damage": 40,
	"lvl" : 80,
	"skills_name" : "������צ",
	"damage_type" : "����"
]),
([	"action" : "$N���ػ��У�һʽ���������ء�������Ϯ�����д�Ѩ�����ַ�ץ$n���ɲ�",
	"force" : 150,
	"dodge" : 35,
	"parry" : 25,
	"damage": 50,
	"lvl" : 100,
	"skills_name" : "��������",
	"damage_type" : "����"
]),
([	"action" : "$N��������צ���棬һʽ���������ա��������������ƿն�����Ѹ���ޱȵػ���$n",
	"force" : 180,
	"dodge" : 55,
	"parry" : 55,
	"damage": 65,
	"lvl" : 120,
	"skills_name" : "��������",
	"damage_type" : "����"
]),
([	"action" : "$N�ڿո߷����ɣ�һʽ��ӥ�����������ж�ʱ�Գ�һ������צӰ����������$n",
	"force" : 230,
	"dodge" : 40,
	"parry" : 40,
	"damage": 60,
	"lvl" : 140,
	"skills_name" : "ӥ������",
	"damage_type" : "����"
]),
([	"action" : "$N���Ĳ��ض���ʹһʽ��������ˮ�������λ���һ����������$n",
	"force" : 270,
	"dodge" : 50,
	"parry" : 50,
	"damage": 80,
	"lvl" : 160,
	"skills_name" : "������ˮ",
	"damage_type" : "����"
]),
([	"action" : "$N΢΢һЦ��ʹһʽ������ڡ���˫�ֻó�������,ֱ����$n��$l",
	"force" : 310,
	"dodge" : 60,
	"parry" : 60,
	"damage": 100,
	"lvl" : 180,
	"skills_name" : "�����",
	"damage_type" : "����"
])
});

int valid_enable(string usage) { return usage=="claw" || usage=="unarmed"; }

int valid_combine(string combo) { return combo=="yunlong-shou"; }

int valid_learn(object me)
{
	if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
		return notify_fail("������צ������֡�\n");

	if ((int)me->query_skill("force") < 100)
		return notify_fail("��������񹦻�򲻹����޷�ѧ����צ��\n");

	if ((int)me->query("max_neili") < 800)
		return notify_fail("�������̫�����޷�������צ��\n");

	if ((int)me->query_skill("claw",1) < 100)
		return notify_fail("��Ļ���צ����򲻹����޷�ѧ����צ��\n");

	if ((int)me->query_skill("claw",1) < (int)me->query_skill("yunlong-zhua",1))
		return notify_fail("��Ļ���צ��ˮƽ���ޣ��޷�����ѧ����צ��\n");

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
	level   = (int) me->query_skill("yunlong-zhua",1);
	for(i = sizeof(action); i > 0; i--)
		if(level > action[i-1]["lvl"])
			return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
	if ((int)me->query("qi") < 70)
		return notify_fail("�������̫���ˡ�\n");

	if ((int)me->query("neili") < 70)
		return notify_fail("�����������������צ��\n");

	me->receive_damage("qi", 55);
	me->add("neili", -62);
	return 1;
}

string perform_action_file(string action)
{
	return __DIR__"yunlong-zhua/" + action;
}
