// zhongnan-zhi.c ����ָ��

inherit SKILL;

mapping *action = ({
([      "action" : "$Nһ�С���ָ��ɽ��������Ĵֱָ��$n��$l",
	"force" : 30,
	"dodge" : 10,
	"damage": 5,
	"skill_name" : "��ָ��ɽ",
	"lvl" : 0,
	"damage_type" : "����"
]),
([      "action" : "$Nʹһ�С���ĵ��ϡ�����������һ�ӣ����ִ���$n��̴�д�Ѩ",
	"force" : 60,
	"dodge" : 18,
	"damage": 10,
	"skill_name" : "��ĵ���",
	"lvl" : 20,
	"damage_type" : "����"
]),
([      "action" : "$N˫�Ʒ��ɣ�һ�С�����ʯ�á���������������ָ����$n��$l",
	"force" : 110,
	"dodge" : 16,
	"damage": 12,
	"skill_name" : "����ʯ��",
	"lvl" : 40,
	"damage_type" : "����"
]),
([      "action" : "$Nһ����ȣ�һʽ���󽭶�ȥ����˫ָ���������$n���ؿں�$l",
	"force" : 150,
	"dodge" : 14,
	"damage": 15,
	"skill_name" : "�󽭶�ȥ",
	"lvl" : 60,
	"damage_type" : "����"
]),
([      "action" : "$N����������һ�С���ȸ�Ϸɡ�����������$n������ȴ��Ϯ$n��$l",
	"force" : 170,
	"dodge" : 22,
	"damage": 25,
	"skill_name" : "��ȸ�Ϸ�",
	"lvl" : 80,
	"damage_type" : "����"
]),
([      "action" : "$N˫�ֲ�ס�ζ��������ƽ�$n��һ�С�����ǧ���������$n��$l",
	"force" : 190,
	"dodge" : 25,
	"damage": 20,
	"skill_name" : "����ǧ��",
	"lvl" : 90,
	"damage_type" : "����"
]),
([      "action" : "$Nһ�С��ٱ���ɽ������ָ��ס�ζ�������$n��$l����֮��",
	"force" : 210,
	"dodge" : 30,
	"damage": 20,
	"skill_name" : "�ٱ���ɽ",
	"lvl" : 100,
	"damage_type" : "����"
])
});

int valid_enable(string usage) { return usage == "finger" || usage == "parry"; }

int valid_combine(string combo)
{
	return combo == "haotian-zhang" ||
	       combo == "chongyang-shenzhang";
}

int valid_learn(object me)
{
	if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
		return notify_fail("������ָ��������֡�\n");

	if ((int)me->query("neili") < 250)
		return notify_fail("��������������޷�ѧ����ָ����\n");

	if ((int)me->query_skill("force") < 40)
		return notify_fail("����ڹ���򲻹����޷�ѧ����ָ����\n");

	return 1;
}

mapping query_action(object me, object weapon)
{
	int i, level;
	level = (int) me->query_skill("zhongnan-zhi", 1);
	for (i = sizeof(action); i > 0; i--)
		if (level > action[i - 1]["lvl"])
			return action[NewRandom(i, 5, level / 5)];

}

int practice_skill(object me)
{
	if ((int)me->query("qi") < 50)
		return notify_fail("�������̫���ˡ�\n");

	if ((int)me->query("neili") < 20)
		return notify_fail("�������������ϰ����ָ����\n");

	me->receive_damage("qi", 35);
	me->add("neili", -11);
	return 1;
}

string perform_action_file(string action)
{
	return __DIR__"zhongnan-zhi/" + action;
}
