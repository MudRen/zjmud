// houquan.c ��ȭ

inherit SKILL;

mapping *action = ({
([      "action" : "$N����΢����������ǰ�˳���һʽ���ɺ�ժ�ҡ�����צֱ����ץ��$n��˫��",
	"force" : 180,
	"dodge" : 5,
	"damage": 10,
	"damage_type" : "ץ��",
	"lvl" : 0,
	"skill_name" : "��ճ���"
]),
([      "action" : "$N������Σ�һʽ�������֦��������ֱ��������$n�ļ羮��Ѩ",
	"force" : 200,
	"dodge" : 10,
	"damage": 20,
	"lvl" : 30,
	"skill_name" : "�����֦",
	"damage_type" : "����"
]),
([      "action" : "$Nһ��ǰ�죬һ�ۺ�ָ��һʽ��Գ�����桹������$n������",
	"force" : 230,
	"dodge" : 10,
	"damage": 25,
	"lvl" : 40,
	"skill_name" : "Գ������",
	"damage_type" : "����"
]),
([      "action" : "$N��Ȼ����һ�ţ�ʹһʽ���˷���Ӱ����˫�������޶���һצץ��$n���ؿ�",
	"force" : 230,
	"dodge" : 25,
	"damage": 20,
	"lvl" : 50,
	"skill_name" : "�˷���Ӱ",
	"damage_type" : "����"
]),
([      "action" : "$N����һ������һ������ʹһʽ��ˮ�����¡���˫צ������$n��С��",
	"force" : 220,
	"dodge" : 15,
	"damage": 10,
	"damage_type" : "����",
	"lvl" : 60,
	"skill_name" : "ˮ������"
]),
([      "action" : "$N�͵����ϸ߸�Ծ��һʽ�����ժ�ǡ����Ӹ����£�һצ����$n��ͷ��",
	"force" : 240,
	"dodge" : 20,
	"damage": 20,
	"damage_type" : "ץ��",
	"lvl" : 70,
	"skill_name" : "���ժ��"
]),
});

int valid_enable(string usage) { return usage=="unarmed" ||  usage=="parry"|| usage=="hand"; }

int valid_learn(object me)
{
	if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
		return notify_fail("����ȭ������֡�\n");

	if ((int)me->query_skill("force", 1) < 30)
		return notify_fail("��Ļ����ڹ���򲻹����޷�ѧ��ȭ��\n");

	if ((int)me->query("max_neili") < 200)
		return notify_fail("�������̫�����޷�����ȭ��\n");

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
	level = (int)me->query_skill("houquan", 1);
	for(i = sizeof(action); i > 0; i--)
		if(level > action[i-1]["lvl"])
			return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
	if ((int)me->query("qi") < 40)
		return notify_fail("�������̫���ˡ�\n");

	if ((int)me->query("neili") < 20)
		return notify_fail("���������������ȭ��\n");

	me->receive_damage("qi", 25);
	me->add("neili", -18);
	return 1;
}

string perform_action_file(string action)
{
	return __DIR__"houquan/" + action;
}


