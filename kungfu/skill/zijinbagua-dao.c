// zijinbagua-dao.c
// Designed by qdz
//

inherit SKILL;

mapping *action = ({
([      "action" : "$N��̤���Է�λ������$w���ƣ�����������$n��ȥ",
	"force"  : 145,
	"attack" : 35,
	"dodge"  : 30,
	"parry"  : 12,
	"lvl"    : 0,
	"damage" : 32,
	"damage_type" : "����",
]),
([      "action" : "$N�������¶��ϻ��˸��뻡��$wһ��һ�գ�ƽ�л���$n�ľ���",
	"force"  : 173,
	"attack" : 42,
	"dodge"  : 40,
	"parry"  : 15,
	"lvl"    : 30,
	"damage" : 38,
	"damage_type" : "����",
]),
([      "action" : "$N��̤���Է�λ��б����ǰ����$w��������һ��ѹ��$n",
	"force"  : 198,
	"attack" : 51,
	"dodge"  : 45,
	"parry"  : 17,
	"lvl"    : 50,
	"damage" : 44,
	"damage_type" : "����",
]),
([      "action" : "$Nת��Ƕ��λ�����ס�λ��$w������б����$n��ȥ",
	"force"  : 237,
	"attack" : 55,
	"dodge"  : 55,
	"parry"  : 21,
	"lvl"    : 80,
	"damage" : 50,
	"damage_type" : "����",
]),
([      "action" : "$N����$w��ת��Ծ��һ���׹�����$n���ؿ�",
	"force"  : 261,
	"attack" : 55,
	"dodge"  : 27,
	"parry"  : 32,
	"lvl"    : 100,
	"damage" : 65,
	"damage_type" : "����",
]),
([      "action" : "$N����$w���������ã����ҿ�����������$n",
	"force"  : 287,
	"attack" : 70,
	"dodge"  : 30,
	"parry"  : 35,
	"lvl"    : 120,
	"damage" : 70,
	"damage_type" : "����",
]),
([      "action" : "$N���Ծ����أ�$w˳����ǰ��Ю��������$n��$l",
	"force"  : 360,
	"attack" : 80,
	"dodge"  : 45,
	"parry"  : 35,
	"lvl"    : 140,
	"damage" : 86,
	"damage_type" : "����",
]),
([      "action" : "$N���ʹһ�С����԰��󡹣���ʱ�����������䵶��������˷�ӿ��$nȫ��",
	"force"  : 410,
	"attack" : 95,
	"dodge"  : 64,
	"parry"  : 32,
	"lvl"    : 160,
	"damage" : 89,
	"damage_type" : "����",
]),
});

int valid_enable(string usage) { return usage == "blade" || usage == "parry"; }

int valid_learn(object me)
{
	if ((int)me->query("max_neili") < 1200)
		return notify_fail("���������Ϊ��ǳ���޷���ϰ�Ͻ���Ե���\n");

	if ((int)me->query_skill("force") < 150)
		return notify_fail("����ڹ����̫ǳ��\n");

	if ((int)me->query_skill("blade", 1) < 120 )
		return notify_fail("��Ļ�������ˮƽ���ޣ��޷���ϰ�Ͻ���Ե���\n");

	if ((int)me->query_skill("blade", 1) < (int)me->query_skill("zijinbagua-dao", 1))
		return notify_fail("��Ļ�������ˮƽ���ޣ��޷�����������Ͻ���Ե���\n");

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
	level   = (int) me->query_skill("zijinbagua-dao", 1);
	for(i = sizeof(action); i > 0; i--)
		if(level > action[i-1]["lvl"])
			return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
	object weapon;

	if (!objectp(weapon = me->query_temp("weapon"))
	|| (string)weapon->query("skill_type") != "blade")
		return notify_fail("��ʹ�õ��������ԡ�\n");

	if ((int)me->query("qi") < 90)
		return notify_fail("��������������������Ͻ���Ե���\n");

	if ((int)me->query("neili") < 150)
		return notify_fail("��������������������Ͻ���Ե���\n");

	me->receive_damage("qi", 85);
	me->add("neili", -100);
	return 1;
}

string perform_action_file(string action)
{
	return __DIR__"zijinbagua-dao/" + action;
}


