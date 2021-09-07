// sanhua-zhang.c ɢ����

inherit SHAOLIN_SKILL;

mapping *action = ({
([      "action": "$N���Ʊ���һʽ������ݾ�����˫�Ʊ�����£���������$n��$l",
	"force" : 350,
	"attack": 69,
	"dodge" : 75,
	"parry" : 50,
	"damage": 25,
	"skill_name" : "����ݾ�",
	"damage_type" : "����"
]),
([      "action": "$N��ָ������һʽ�����ж���ܰ���������ƴ��巭�ɣ�����$n��$l��ȥ",
	"force" : 360,
	"attack": 72,
	"dodge" : 60,
	"parry" : 65,
	"damage": 20,
	"skill_name" : "���ж���ܰ",
	"damage_type" : "����"
]),
([      "action": "$Nʹһʽ���ﺨ��˪�塹���������У�����է��է�ϣ��͵ز���$n��$l",
	"force" : 340,
	"attack": 79,
	"dodge" : 55,
	"parry" : 70,
	"damage": 32,
	"skill_name" : "�ﺨ��˪��",
	"damage_type" : "����"
]),
([      "action": "$N˫��Ѫ�죬һʽ��������÷�������ó�����÷����䣬������$n��ȥ",
	"force" : 370,
	"attack": 67,
	"dodge" : 50,
	"parry" : 60,
	"damage": 35,
	"skill_name" : "������÷��",
	"damage_type" : "����"
])
});

int valid_enable(string usage) { return usage == "strike" || usage == "parry"; }

int valid_combine(string combo) { return combo == "nianhua-zhi"; }

int valid_learn(object me)
{
	if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
		return notify_fail("��ɢ���Ʊ�����֡�\n");

	if ((int)me->query_skill("force", 1) < 60)
		return notify_fail("����ڹ���򲻹����޷�ѧɢ���ơ�\n");

	if ((int)me->query("max_neili") < 300)
		return notify_fail("�������̫�����޷���ɢ���ơ�\n");

	if ((int)me->query_skill("strike", 1) < (int)me->query_skill("sanhua-zhang", 1))
		return notify_fail("��Ļ����Ʒ����ˮƽ���ޣ��޷����������ɢ���ơ�\n");

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
	if (me->query_temp("weapon") ||
	    me->query_temp("secondary_weapon"))
		return notify_fail("����������ϰ��\n");

	if ((int)me->query("qi") < 70)
		return notify_fail("�������̫���ˡ�\n");

	if ((int)me->query("neili") < 70)
		return notify_fail("�������������ɢ���ơ�\n");

	me->receive_damage("qi", 65);
	me->add("neili", -66);
	return 1;
}

string perform_action_file(string action)
{
	return __DIR__"sanhua-zhang/" + action;
}
