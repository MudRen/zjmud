// tianluo-diwang ���޵�����

#include <ansi.h>;

inherit SKILL;

mapping *action = ({
([      "action" : "$N���ƻ�һ��Բ�����ƻ�����һ��Բ���ʺ�£֮�ƣ�����$n����ǰ��Ѩ",
	"force"  : 160,
	"attack" : 10,
	"parry"  : 10,
	"dodge"  : 10,
	"damage" : 10,
	"lvl"    : 0,
	"damage_type" : "����",
]),
([      "action" : "$N���ƻ��أ���ȭ�����󷢣�����һ��������������$n��$l",
	"force"  : 185,
	"attack" : 20,
	"parry"  : 15,
	"dodge"  : 15,
	"damage" : 15,
	"damage_type" : "����",
	"lvl"    : 30,
]),
([      "action" : "$N������ǰ��ȥ��һ�¼��弲�����������۽���δ��֮�ʣ�˫�ֱ���$n��$l",
	"force"  : 200,
	"attack" : 30,
	"parry"  : 20,
	"dodge"  : 20,
	"damage" : 22,
	"lvl"    : 60,
	"damage_type" : "����"
]),
([      "action" : "$N�������»��أ�����ͻȻһ�䣬��Ȼ��Ϊ�������꣬����$n",
	"force"  : 280,
	"attack" : 40,
	"parry"  : 30,
	"dodge"  : 20,
	"damage" : 30,
	"damage_type" : "����",
	"lvl"    : 90,     
]),
([      "action" : "$N����Ӵ�����������˳���$nֻ�����ܲ�͸�磬��������ӡ����ôҲ���㲻��",
	"force"  : 340,
	"attack" : 50,
	"parry"  : 35,
	"dodge"  : 35, 
	"damage" : 35,
	"lvl"    : 120,	
	"damage_type" : "����"
]),
([      "action" : "$N˫�۷��裬��ֻ�������ƻ�����ǧ��ǧ�ƣ���$n���Ծ�����㣬ʼ�շɲ���ֻ����Χ����ȦȦ", 
	"force"  : 350,
	"attack" : 65,
	"parry"  : 40,
	"dodge"  : 40,
	"damage" : 50,
	"lvl"    : 150,
	"damage_type" : "����"
]), 
});

int valid_enable(string usage) { return usage == "strike" || usage == "parry"; }

int valid_combine(string combo) { return combo == "meinv-quan"; }

int valid_learn(object me)
{
	if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
		return notify_fail("�������ַ�����ϰ���޵����ơ�\n");

	if ((int)me->query_skill("force") < 80)
		return notify_fail("����ڹ������������޷���ϰ���޵����ơ�\n");

	if ((int)me->query_skill("strike", 1) < 30)
		return notify_fail("��Ļ����Ʒ�ˮƽ̫�ͣ��޷���ϰ���޵����ơ�\n");

	if ((int)me->query_skill("strike", 1) < me->query_skill("tianluo-diwang", 1))
		return notify_fail("��Ļ����Ʒ�ˮƽˮƽ���ޣ��޷���ϰ����������޵����ơ�\n");

	return 1;
}

mapping query_action(object me, object weapon)
{
	int i, level;

	level = (int)me->query_skill("tianluo-diwang", 1);

	for (i = sizeof(action); i > 0; i--)
		if (level > action[i - 1]["lvl"])
			return action[NewRandom(i, 20, level / 5)];
}

int practice_skill(object me)
{
	if ((int)me->query("qi") < 50)
		return notify_fail("�������̫���ˡ�\n");

	if ((int)me->query("neili") < 40)
		return notify_fail("������������ˡ�\n");

	me->receive_damage("qi", 40);
	me->add("neili", -25);
	return 1;
}

string perform_action_file(string action)
{
	return __DIR__"tianluo-diwang/" + action;
}
