// tanzhi.c ��ָ��ͨ

inherit SKILL;

mapping *action_finger = ({
([      "action" : "$N��ָ���˸���Ȧ��һʽ�������ѵء����϶��»���$n��ȫ��",
	"force" : 440,
	"attack": 100,
	"parry" : 50,
	"dodge" : 75,
	"damage": 65,
	"skill_name" : "�����ѵ�",
	"damage_type" : "����"
]),
([      "action" : "$N���ƻ��أ�һ�С��������ơ�����ָ��������ָ��$n�Ķ�ͷ",
	"force" : 410,
	"attack": 90,
	"parry" : 65,
	"dodge" : 90,
	"skill_name" : "��������",
	"damage_type" : "����"
]),
([      "action" : "$N˫�������һʽ��ǧ����ָ������ָ��$n��$l",
	"force" : 420,
	"attack": 110,
	"parry" : 65,
	"dodge" : 85,
	"damage": 65,
	"skill_name" : "ǧ����ָ",
	"damage_type" : "����"
]),
([      "action" : "$N����һ̾��һ�С���ָ��������˫�ֻó�����ָӰ������$n��$l",
	"force" : 400,
	"attack": 100,
	"parry" : 70,
	"dodge" : 95,
	"damage": 70,
	"skill_name" : "��ָ����",
	"damage_type" : "����"
]),
([      "action" : "$Nһʽ��Цָ���ϡ���������ʽ����ָ����һ��ָ�����$n��$l",
	"force" : 430,
	"attack": 95,
	"parry" : 45,
	"dodge" : 100,
	"damage": 75,
	"skill_name" : "Цָ����",
	"damage_type" : "����"
]),
([      "action" : "$N�ó�������һָ�����ȫ��������һָ����$n��$l",
	"force" : 450,
	"attack": 105,
	"parry" : 65,
	"dodge" : 90,
	"damage": 80,
	"skill_name" : "����һָ",
	"damage_type" : "����"
]),
});

int valid_enable(string usage)
{
	return usage == "finger" ||
	       usage == "parry" ||
	       usage == "throwing";
}

int valid_combine(string combo) { return combo == "lanhua-shou"; }

int valid_learn(object me)
{
	if ((int)me->query_skill("force") < 150)
		return notify_fail("����ڹ���򲻹����޷�ѧ��ָ��ͨ��\n");

	if ((int)me->query("max_neili") < 1000)
		return notify_fail("�������̫�����޷�����ָ��ͨ��\n");

	if ((int)me->query_skill("finger", 1) < 100)
		return notify_fail("��Ļ���ָ����򲻹����޷�ѧ��ָ��ͨ��\n");

	if ((int)me->query_skill("finger", 1) < (int)me->query_skill("tanzhi-shentong", 1))
		return notify_fail("��Ļ���ָ��ˮƽ���ޣ��޷���������ĵ�ָ��ͨ��\n");

	return 1;
}

string query_skill_name(int level)
{
	return action_finger[random(sizeof(action_finger))]["skill_name"];
}

mapping query_action(object me, object weapon)
{
	return action_finger[random(sizeof(action_finger))];
}

int practice_skill(object me)
{
	if ((int)me->query("qi") < 80)
		return notify_fail("���������������Ϣһ�������ɡ�\n");

	if ((int)me->query("neili") < 80)
		return notify_fail("���������������ָ��ͨ��\n");

	me->receive_damage("qi", 68);
	me->add("neili", -67);
	return 1;
}

string perform_action_file(string action)
{
	return __DIR__"tanzhi-shentong/" + action;
}
