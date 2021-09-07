//liangyi-jian.c ���ǽ���

inherit SKILL;

mapping *action = ({
([      "skill_name":   "��������",
	"action" : "$N���⽣â������һ�С��������ء�������$w�����´󿪴��أ�"
		   "һ��б�ϴ���$n��$l",
	"force"  : 60,
	"dodge"  : 20,
	"damage" : 10,
	"lvl"    : 0,
	"damage_type" : "����"
]),
([      "skill_name":   "��������",
	"action" : "$N����Ȧת������$w��ճ������ƽƽչչ�ӳ���һ�С�������"
		   "�������Ữ��$n��$l",
	"force"  : 90,
	"dodge"  : 20,
	"damage" : 20,
	"lvl"    : 20,
	"damage_type" : "����"
]),
([      "skill_name":   "Ԩ����ǳ",
	"action" : "$N��������������������������$wʹ��һʽ��Ԩ����ǳ������"
		   "$n��$l",
	"force"  : 110,
	"dodge"  : 15,
	"damage" : 25,
	"lvl"    : 40,
	"damage_type" : "����"
]),
([      "skill_name":   "ˮ�����",
	"action" : "$N������ָ��������ת��һ�С�ˮ����ơ�ֱȡ$n��$l",
	"force"  : 140,
	"dodge"  : 15,
	"damage" : 30,
	"lvl"    : 60,
	"damage_type" : "����"
]),
([      "skill_name":   "�ƺ�����",
	"action" : "$N��â���£��������ߣ�����$wʹ��һʽ���ƺ����¡������Ƽ�"
		   "���������$n��$l",
	"force"  : 160,
	"dodge"  : 25,
	"damage" : 35,
	"lvl"    : 80,
	"damage_type" : "����"
]),
([      "skill_name":   "���ѵ�ׯ",
	"action" : "$N�����ƽ���������ʵ��׷ɣ��ó�����ǹ⣬����$wʹ��һʽ"
		   "�����ѵ�ׯ��ԾԾ����Ʈ��$n��$l",
	"force"  : 190,
	"dodge"  : 25,
	"damage" : 40,
	"lvl"    : 100,
	"damage_type" : "����"
]),
([      "skill_name":   "��������",
	"action" : "$N�ӽ��ֻ�����������ǰԾ��������$wһʽ���������ǡ�������"
		   "����֮�ƣ�����$n��$l",
	"force"  : 210,
	"dodge"  : 15,
	"damage" : 45,
	"lvl"    : 120,
	"damage_type" : "����"
]),
([      "skill_name":   "��ϵ�̳�",
	"action" : "$N�˲������ֽ�ָ��ת������һŤ������$wһ�ǡ���ϵ�̳�������"
		   "���ϴ���$n��$l",
	"force"  : 240,
	"dodge"  : 35,
	"damage" : 50,
	"lvl"    : 140,
	"damage_type" : "����"
]),
});

int valid_enable(string usage) {return (usage== "sword") || (usage== "parry"); }

int valid_learn(object me)
{
	if ((int)me->query("max_neili") < 200)
		return notify_fail("�������������\n");

	if ((int)me->query_skill("force") < 30)
		return notify_fail("����ڹ����̫ǳ��\n");

	return 1;
}

mapping query_action(object me, object weapon)
{
	int i, level;
	level   = (int) me->query_skill("liangyi-jian",1);
	for(i = sizeof(action); i > 0; i--)
		if(level > action[i-1]["lvl"])
		       return action[NewRandom(i, 20, level/5)];

}

int practice_skill(object me)
{
	object weapon;

	if (!objectp(weapon = me->query_temp("weapon"))
	|| (string)weapon->query("skill_type") != "sword")
		return notify_fail("��ʹ�õ��������ԡ�\n");

	if ((int)me->query("qi") < 50)
		return notify_fail("����������������ǽ�����\n");

	if ((int)me->query("neili") < 30)
		return notify_fail("����������������ǽ�����\n");

	me->receive_damage("qi", 40);
	me->add("neili", -25);
	return 1;
}

string perform_action_file(string action)
{
	return __DIR__"liangyi-jian/" + action;
}
