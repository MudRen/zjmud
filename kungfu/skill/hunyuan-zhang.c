// hunyuan-zhang.c ��Ԫ��

inherit SKILL;

mapping *action = ({
([	"action" : "$Nһʽ�����Ƴ�ᶡ���˫�Ƽ�����һ�ŵ����İ�����������$n��$l",
	"force" : 60,
	"dodge" : 5,
	"parry" : 10,
	"damage": 10,
	"lvl" : 0,
	"skill_name" : "���Ƴ��",
	"damage_type" : "����"
]),
([	"action" : "$N��ָ�罣��һʽ���׺���ա�������$n��$l��ȥ",
	"force" : 80,
	"dodge" : 10,
	"parry" : 10,
	"damage": 20,
	"lvl" : 10,
	"skill_name" : "�׺����",
	"damage_type" : "����"
]),
([	"action" : "$Nʹһʽ���ƶ����롹������΢��������է��է�ϣ��͵ز���$n��$l",
	"force" : 100,
	"dodge" : 15,
	"parry" : 15,
	"damage": 30,
	"lvl" : 20,
	"skill_name" : "�ƶ�����",
	"damage_type" : "����"
]),
([	"action" : "$N˫����������������һʽ�����ɴ�䡹���ó�������̵����룬������$n��ȥ",
	"force" : 120,
	"dodge" : 20,
	"parry" : 15,
	"damage": 35,
	"lvl" : 30,
	"skill_name" : "���ɴ��",
	"damage_type" : "����"
]),
([	"action" : "$N��������һ�ݣ�ʹ��һʽ������������˫�Ʋ�£����ֱ����$n��$l��ȥ",
	"force" : 140,
	"dodge" : 20,
	"parry" : 20,
	"damage": 40,
	"lvl" : 50,
	"skill_name" : "������",
	"damage_type" : "����"
]),
([	"action" : "$N����һ�䣬ʹһʽ���ޱ���ľ����˫�ƴ�����ɲ�ľ������͵ػ���$n��$l",
	"force" : 180,
	"dodge" : 20,
	"parry" : 25,
	"damage": 45,
	"lvl" : 70,
	"skill_name" : "�ޱ���ľ",
	"damage_type" : "����"
]),
([	"action" : "$Nʹһʽ����ɽ��ˮ�����������أ�������ӯ��ͬʱ��$n��$l��ȥ",
	"force" : 220,
	"dodge" : 20,
	"parry" : 30,
	"damage": 50,
	"lvl" : 90,
	"skill_name" : "��ɽ��ˮ",
	"damage_type" : "����"
]),
([	"action" : "$Nͻ��һ�С��������á���˫��Ю��һ�����֮�ƣ��͵�����$n��$l",
	"force" : 260,
	"dodge" : 20,
	"parry" : 25,
	"damage": 55,
	"lvl" : 110,
	"skill_name" : "��������",
	"damage_type" : "����"
]),
([	"action" : "$Nһʽ��������ơ���˫�������һ����裬�����ѻ���$n��$l��",
	"force" : 300,
	"dodge" : 30,
	"parry" : 35,
	"damage": 60,
	"lvl" : 120,
	"skill_name" : "�������",
	"damage_type" : "����"
]),
([	"action" : "$Nһʽ������Ʈ�졹����������������˫��һ��һ�ͣ����Ƽ򵥣�ȴ��$n�޷�����",
	"force" : 340,
	"dodge" : 35,
	"parry" : 40,
	"damage": 65,
	"lvl" : 130,
	"skill_name" : "����Ʈ��",
	"damage_type" : "����"
])
});

int valid_enable(string usage) { return usage == "parry" || usage == "strike"; }

int valid_combine(string combo) { return combo == "poyu-quan"; }

int valid_learn(object me)
{
	if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
		return notify_fail("����Ԫ�Ʊ�����֡�\n");

	if ((int)me->query_skill("force") < 30)
		return notify_fail("����ڹ���򲻹����޷�ѧ��Ԫ�ơ�\n");

	if ((int)me->query("max_neili") < 150)
		return notify_fail("�������̫�����޷�����Ԫ�ơ�\n");

	if (me->query_skill("strike", 1) < me->query_skill("hunyuan-zhang", 1))
		return notify_fail("��Ļ����Ʒ�ˮƽ���ޣ��޷���������Ļ�Ԫ�ơ�");

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

	level = (int) me->query_skill("hunyuan-zhang",1);
	for (i = sizeof(action); i > 0; i--)
		if (level > action[i - 1]["lvl"])
			return action[NewRandom(i, 20, level / 5)];
}

int practice_skill(object me)
{
	if ((int)me->query("qi") < 50)
		return notify_fail("�������̫���ˡ�\n");

	if ((int)me->query("neili") < 60)
		return notify_fail("���������������Ԫ�ơ�\n");

	me->receive_damage("qi", 40);
	me->add("neili", -53);
	return 1;
}

string perform_action_file(string action)
{
	return __DIR__"hunyuan-zhang/" + action;
}
