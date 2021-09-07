//
// yujiamu-quan.c ������ĸȭ
// Designed by secret(����)
//

inherit SKILL;

mapping *action = ({
([      "action" : "$N����˫ȭ��ʹ��һ�С��ඥ������ͷ����$n��$l  ",
	"skill_name" : "�ඥ",
	"force" : 160,
	"dodge" : 5,
	"lvl" : 0,
	"damage_type" : "����",
]),
([      "action" : "$Nʹ��һ�С���ࡹ������һ�ͣ����ֻ���������һȭ����$n���ɲ�  ",
	"skill_name" : "���",
	"force" : 200,
	"dodge" : -5,
	"lvl" : 30,
	"damage_type" : "����",
]),
([      "action" : "$Nʹ��һ�С��ü������ȭ���$n��ǰ�أ�һ������ȭ��ɨ$n��̫��Ѩ  ",
	"skill_name" : "�ü",
	"force" : 220,
	"dodge" : 10,
	"lvl" : 60,
	"damage_type" : "����",
]),
([      "action" : "$N���ι��죬ʹһ�С�������˫ȭ���»���$n��$l  ",
	"skill_name" : "���",
	"force" : 250,
	"dodge" : 5,
	"lvl" : 80,
	"damage_type" : "����",
]),
([      "action" : "$Nʹ��һ�С����š���˫ȭ������������������ֱָ$n��$l  ",
	"skill_name" : "����",
	"force" : 270,
	"dodge" : -5,
	"lvl" : 100,
	"damage_type" : "����",
]),
([      "action" : "$N΢΢һЦ��ʹ��һʽ����������˫ȭǰ�������ֱȡ$n������  ",
	"skill_name" : "����",
	"force" : 300,
	"dodge" : 10,
	"lvl" : 120,
	"damage_type" : "����",
]),
([      "action" : "$Nʹ��һ�С����ġ���ȫ��ת��˫ȭ��ɨ$n��$l  ",
	"skill_name" : "����",
	"force" : 310,
	"dodge" : 20,
	"lvl" : 140,
	"damage_type" : "����",
]),
([      "action" : "$N����һԾ��ʹ��һ�С���ʤ����һȭ�ͻ�$n�ʺ�  ",
	"skill_name" : "��ʤ",
	"force" : 330,
	"dodge" : 5,
	"lvl" : 160,
	"damage_type" : "����",
]),
});

int valid_enable(string usage) { return usage == "cuff" || usage == "parry"; }

int valid_combine(string combo)
{
	return combo=="dashou-yin" ||
	       combo=="huoyan-dao";
}

int valid_learn(object me)
{
	if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
		return notify_fail("��������ĸȭ������֡�\n");

	if ((int)me->query("max_neili") < 600)
		return notify_fail("�������������\n");

	if ((int)me->query_skill("force") < 100)
		return notify_fail("����ڹ���򲻹���\n");

	if ((int)me->query_skill("cuff", 1) < (int)me->query_skill("yujiamu-quan",1))
		return notify_fail("��Ļ���ȭ��ˮƽ���ޣ��޷���������Ľ�����ĸȭ��\n");

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
	level   = (int) me->query_skill("yujiamu-quan",1);
	for(i = sizeof(action); i > 0; i--)
		if(level > action[i-1]["lvl"])
			return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
	object weapon;

	if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
		return notify_fail("��������ĸȭ������֡�\n");

	if ((int)me->query("qi") < 60)
		return notify_fail("������������������˽�����ĸȭ��\n");

	if ((int)me->query("neili") < 70)
		return notify_fail("������������������˽�����ĸȭ��\n");

	me->receive_damage("qi", 50);
	me->add("neili", -61);
	return 1;
}

string perform_action_file(string action)
{
       return __DIR__"yujiamu-quan/" + action;
}
