// huashan-zhangfa.c ��ɽ�Ʒ�

inherit SKILL;

mapping *action = ({
([	"action" : "$Nһʽ�����Ƴ�ᶡ���˫�Ƽ�����һ�ŵ����İ�����������$n��$l",
	"force" : 50,
	"dodge" : 5,
	"parry" : 10,
	"damage": 5,
	"lvl" : 0,
	"skill_name" : "���Ƴ��",
	"damage_type" : "����"
]),
([	"action" : "$N��ָ�罣��һʽ���׺���ա�������$n��$l��ȥ",
	"force" : 60,
	"dodge" : -5,
	"parry" : 15,
	"damage": 5,
	"lvl" : 10,
	"skill_name" : "�׺����",
	"damage_type" : "����"
]),
([	"action" : "$Nʹһʽ���ƶ����롹������΢��������է��է�ϣ��͵ز���$n��$l",
	"force" : 65,
	"dodge" : 5,
	"parry" : 10,
	"damage": 10,
	"lvl" : 20,
	"skill_name" : "�ƶ�����",
	"damage_type" : "����"
]),
([	"action" : "$N˫����������������һʽ�����ɴ�䡹���ó�������̵����룬������$n��ȥ",
	"force" : 70,
	"dodge" : 10,
	"parry" : 20,
	"damage": 15,
	"lvl" : 30,
	"skill_name" : "���ɴ��",
	"damage_type" : "����"
]),
([	"action" : "$N��������һ�ݣ�ʹ��һʽ������������˫�Ʋ�£����ֱ����$n��$l��ȥ",
	"force" : 75,
	"dodge" : 15,
	"parry" : 10,
	"damage": 15,
	"lvl" : 40,
	"skill_name" : "������",
	"damage_type" : "����"
]),
([	"action" : "$N����һ�䣬ʹһʽ���ޱ���ľ����˫�ƴ�����ɲ�ľ������͵ػ���$n��$l",
	"force" : 80,
	"dodge" : 15,
	"parry" : 15,
	"damage": 20,
	"lvl" : 50,
	"skill_name" : "�ޱ���ľ",
	"damage_type" : "����"
]),
([	"action" : "$Nʹһʽ����ɽ��ˮ�����������أ�������ӯ��ͬʱ��$n��$l��ȥ",
	"force" : 85,
	"dodge" : 20,
	"parry" : 15,
	"damage": 20,
	"lvl" : 60,
	"skill_name" : "��ɽ��ˮ",
	"damage_type" : "����"
]),
([	"action" : "$Nͻ��һ�С��������á���˫��Ю��һ�����֮�ƣ��͵�����$n��$l",
	"force" : 90,
	"dodge" : 20,
	"parry" : 20,
	"damage": 25,
	"lvl" : 70,
	"skill_name" : "��������",
	"damage_type" : "����"
]),
([	"action" : "$Nһʽ��������ơ���˫�������һ����裬�����ѻ���$n��$l��",
	"force" : 110,
	"dodge" : 15,
	"parry" : 20,
	"damage": 25,
	"lvl" : 80,
	"skill_name" : "�������",
	"damage_type" : "����"
]),
([	"action" : "$Nһʽ������Ʈ�졹����������������˫��һ��һ�ͣ����Ƽ򵥣�ȴ��$n�޷�����",
	"force" : 120,
	"dodge" : 25,
	"parry" : 10,
	"damage": 30,
	"lvl" : 90,
	"skill_name" : "����Ʈ��",
	"damage_type" : "����"
])
});

int valid_enable(string usage) { return usage=="strike" || usage=="parry"; }

int valid_combine(string combo) { return combo=="huashan-quanfa"; }

int valid_learn(object me)
{
	if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
		return notify_fail("����ɽ�Ʒ�������֡�\n");

	if ((int)me->query_skill("force") < 20)
		return notify_fail("����ڹ���򲻹����޷�ѧ��ɽ�Ʒ���\n");

	if ((int)me->query("max_neili") < 100)
		return notify_fail("�������̫�����޷�����ɽ�Ʒ���\n");
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
	level   = (int) me->query_skill("huashan-zhangfa",1);
	for(i = sizeof(action); i > 0; i--)
		if(level > action[i-1]["lvl"])
			return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
	if ((int)me->query("qi") < 40)
		return notify_fail("�������̫���ˡ�\n");

	if ((int)me->query("neili") < 30)
		return notify_fail("���������������ɽ�Ʒ���\n");

	me->receive_damage("qi", 30);
	me->add("neili", -6);
	return 1;
}

string perform_action_file(string action)
{
	return __DIR__"huashan-zhangfa/" + action;
}
