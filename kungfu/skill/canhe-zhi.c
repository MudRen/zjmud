// canhezhi.c �κ�ָ

inherit SKILL;

mapping *action = ({
([      "action": "$N˫ָ��£��һʽ�����ķپ�����һָ����$n���ظ���",
	"force" : 340,
	"attack": 85,
	"dodge" : 75,
	"parry" : 70,
	"damage": 72,
	"skill_name" : "���ķپ�",
	"damage_type" : "����"
]),
([      "action": "$N���ƻ��أ�һʽ�������Բt����������ָǰ���˸��뻡���͵�һ˦������$n��$l",
	"force" : 370,
	"attack": 65,
	"dodge" : 80,
	"parry" : 85,
	"damage": 65,
	"skill_name" : "�����Բt",
	"damage_type" : "����"
]),
([      "action": "$N����������һʽ����Ҷ��������˫��ʮָͬʱ"
		  "����$n��ȫ��ҪѨ",
	"force" : 360,
	"attack": 85,
	"dodge" : 70,
	"parry" : 75,
	"damage": 90,
	"skill_name" : "��Ҷ����",
	"damage_type" : "����"
]),
([      "action": "$Nһʽ��������������������ȭ���⣬����Ĵֱָ����ң"
		  "ң����$nһ��",
	"force" : 380,
	"attack": 95,
	"dodge" : 75,
	"parry" : 85,
	"damage": 70,
	"skill_name" : "��������",
	"damage_type" : "����"
])
});

int valid_enable(string usage) { return usage == "finger" || usage == "parry"; }

int valid_combine(string combo) { return combo == "qixing-quan"; }

int valid_learn(object me)
{
	if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
		return notify_fail("���κ�ָ������֡�\n");

	if ((int)me->query_skill("force") < 100)
		return notify_fail("����ڹ���򲻹����޷�ѧ�κ�ָ��\n");

	if ((int)me->query("max_neili") < 500)
		return notify_fail("�������̫�����޷����κ�ָ��\n");

	if ((int)me->query_skill("finger", 1) < (int)me->query_skill("canhe-zhi", 1))
		return notify_fail("��Ļ���ָ��ˮƽ���ޣ��޷���������Ĳκ�ָ��\n");

	return 1;
}

string query_skill_name(int level)
{
	return action[random(sizeof(action))]["skill_name"];
}

mapping query_action(object me, object weapon)
{
	return action[random(sizeof(action))];
}

int practice_skill(object me)
{
	if ((int)me->query("qi") < 70)
		return notify_fail("�������̫���ˡ�\n");

	if ((int)me->query("neili") < 80)
		return notify_fail("��������������κ�ָ��\n");

	me->receive_damage("qi", 62);
	me->add("neili", -70);
	return 1;
}

string perform_action_file(string action)
{
	return __DIR__"canhe-zhi/" + action;
}
