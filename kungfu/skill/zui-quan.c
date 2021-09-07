// zui-quan.c ������ȭ

#define CN_NAME "��ȭ"

inherit SHAOLIN_SKILL;

mapping *action = ({
([      "action": "$N������ȭ����ת��һ��Ȧ���������У�����һ�С�ֻ�����졹",
	"force" : 150,
	"attack": 30,
	"dodge" : 5,
	"parry" : 5,
	"lvl"   : 0,
	"skill_name"  : "ֻ������",
	"damage_type" : "����"
]),
([      "action": "$N˳��һ�С��������ơ��������ڵأ������뷢����$n���漴����",
	"force" : 200,
	"attack": 33,
	"dodge" : 10,
	"parry" : 5,
	"lvl"   : 20,
	"skill_name"  : "��������",
	"damage_type" : "����"
]),
([      "action": "$N�Ų��б��˫�����裬����������ָǰ��󣬵���ײײ��һȭ������Ǭ������$n��ȥ",
	"force" : 150,
	"attack": 38,
	"dodge" : 15,
	"parry" : 5,
	"lvl"   : 40,
	"skill_name"  : "����Ǭ��",
	"damage_type" : "����"
]),
([      "action": "$N����������ȣ�ȭ����иʵ�����������ˣ��������ˣ���������һ�С��������",
	"force" : 200,
	"attack": 55,
	"dodge" : 10,
	"parry" : 10,
	"lvl"   : 60,
	"skill_name"  : "�������",
	"damage_type" : "����"
]),
([      "action": "$Nһ�����ڲ���ȫ����գ���������ɽʻ���һ�С���ţ���ء�����ȭ���$n$l",
	"force" : 250,
	"attack": 70,
	"dodge" : 25,
	"parry" : 15,
	"lvl"   : 80,
	"skill_name"  : "��ţ����",
	"damage_type" : "����"
]),
([      "action": "$Nһ�������ӷ�����˳����Ծ��ͬʱ������չ���������ģ������������$n��ǰ",
	"force" : 200,
	"attack": 66,
	"dodge" : 20,
	"parry" : 25,
	"lvl"   : 100,
	"skill_name"  : "���ӷ���",
	"damage_type" : "����"
]),
([      "action": "$N������𣬴ӿ��и������£�һȭ�����䳤�ա�ֱȡ$n��$l",
	"force" : 20,
	"attack": 80,
	"dodge" : 25,
	"parry" : 30,
	"lvl"   : 120,
	"skill_name"  : "���䳤��",
	"damage_type" : "����"
]),
([      "action": "$N��ס$n��·���ζ���˫ȭ���ɣ�һ�С�����̽צ����������$n$l",
	"force" : 300,
	"attack": 86,
	"dodge" : 30,
	"parry" : 45,
	"lvl"   : 140,
	"skill_name"  : "����̽צ",
	"damage_type" : "����"
]),
});

int valid_enable(string usage) { return usage == "unarmed" || usage == "parry"; }

int valid_learn(object me)
{
	if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
		return notify_fail("��" + CN_NAME + "������֡�\n");

	if ((int)me->query("max_neili") < 500)
		return notify_fail("�������̫�����޷���" + CN_NAME + "��\n");

	if (me->query_skill("unarmed", 1) < me->query_skill("zui-quan", 1))
		return notify_fail("��Ļ���ȭ��ˮƽ���ޣ��޷�����������" + CN_NAME + "��\n");

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
	level = (int) me->query_skill("zui-quan", 1);
	for (i = sizeof(action); i > 0; i--)
		if(level > action[i - 1]["lvl"])
			return action[NewRandom(i, 20, level / 5)];
}

int practice_skill(object me)
{
	if ((int)me->query("qi") < 60)
		return notify_fail("�������̫���ˡ�\n");

	if ((int)me->query("neili") < 60)
		return notify_fail("�������������" + CN_NAME + "��\n");

	me->receive_damage("qi", 55);
	me->add("neili", -48);
	return 1;
}

string perform_action_file(string action)
{
	return __DIR__"zui-quan/" + action;
}
