// yunv-jian.c ��Ů���Ľ�

inherit SKILL;

mapping *action = ({
([      "action" : "$Nһ�С�����б����������б�ɣ�����$w�������$n��$l",
	"force"  : 2,
	"dodge"  : 20,
	"parry"  : 10,
	"damage" : 5,
	"lvl"    : 0,
	"damage_type" : "����"
]),
([      "action" : "$N��Ծ���𣬡��׺羭�졹��$w��Ȼ�´�",
	"force"  : 4,
	"dodge"  : 15,
	"parry"  : 10,
	"damage" : 4,
	"lvl"    : 4,
	"damage_type" : "����"
]),
([      "action" : "$Nʹ�����˼����ġ����ӽ�ֱ���������ɵ�",
	"force"  : 5,
	"attack" : 1,
	"dodge"  : 15,
	"parry"  : 10,
	"damage" : 5,
	"lvl"    : 9,
	"damage_type" : "����"
]),
([      "action" : "$Nʹ����ǰ���¡�һ�����϶��²�����ģ����ֺ�ա�����̵صĹ⾰",
	"force"  : 6,
	"attack" : 2,
	"dodge"  : 15,
	"parry"  : 10,
	"damage" : 6,
	"lvl"    : 14,
	"damage_type" : "����"
]),
([      "action" : "$N����$w���������ʻ���չ���ػ�����ֻ�ϵ�$n�ۻ����ң��벻֪�Ӻι���",
	"force"  : 8,
	"attack" : 4,
	"dodge"  : 15,
	"parry"  : 15,
	"damage" : 7,
	"lvl"    : 19,
	"damage_type" : "����"
]),
([      "action" : "$Nʹ��������С�á��������𣬽�����ָ�����������ƣ�ֱ��$n��$l",
	"force"  : 10,
	"attack" : 6,
	"dodge"  : 15,
	"parry"  : 15,
	"damage" : 8,
	"lvl"    : 24,
	"damage_type" : "����"
]),
([      "action" : "$N����$w��������һ�̣�������������ʹ����ɨѩ��衹��",
	"force"  : 20,
	"attack" : 8,
	"dodge"  : 10,
	"parry"  : 15,
	"damage" : 9,
	"lvl"    : 29,
	"damage_type" : "����"
]),
([      "action" : "$N���ƺ����ǰ��������$w����ӷ���ȴ��һ�С����ٰ�����",
	"force"  : 30,
	"attack" : 10,
	"dodge"  : 15,
	"parry"  : 15,
	"damage" : 10,
	"lvl"    : 34,
	"damage_type" : "����"
]),
([      "action" : "$Nһ�С����¶��ġ���$w���������һ���󻡣�����$n��$l",
	"force"  : 40,
	"attack" : 11,
	"dodge"  : 15,
	"parry"  : 15,
	"damage" : 12,
	"lvl"    : 39,
	"damage_type" : "����"
]),
([      "action" : "$N����������ң�������Ϊ������$n��ȴ��һ�С��رߵ��ס�",
	"force"  : 50,
	"attack" : 14,
	"dodge"  : 10,
	"parry"  : 20,
	"damage" : 13,
	"lvl" : 44,
	"damage_type" : "����"
]),
([      "action" : "$Nһ�С�������Ʈ����$w����ػ�������Բ������$n��$l��ȥ",
	"force"  : 60,
	"attack" : 15,
	"dodge"  : 15,
	"parry"  : 20,
	"damage" : 15,
	"lvl"    : 49,
	"damage_type" : "����"
]),
([      "action" : "$Nһ�С�С԰�վա�������$wѸ����$n��������������",
	"attack" : 21,
	"force"  : 70,
	"dodge"  : 15,
	"parry"  : 20,
	"damage" : 19,
	"lvl"    : 54,
	"damage_type" : "����"
]),
([      "action" : "$Nʹ��������ҹ����������$w�й�ֱ�룬����$n��$l",
	"force"  : 80,
	"attack" : 22,
	"dodge"  : 15,
	"parry"  : 20,
	"damage" : 19,
	"lvl"    : 59,
	"damage_type" : "����"
]),
([      "action" : "$N��������ҵͣ�һ�С��������䡹��$w�ڿ��л���һ���⻷������$n",
	"force"  : 90,
	"attack" : 26,
	"dodge"  : 5,
	"parry"  : 20,
	"damage" : 21,
	"lvl"    : 64,
	"damage_type" : "����"
]),
([      "action" : "$N����$w���¶��Ͼ��������������һ�㣬ȴ�ǡ������ٳء�",
	"force"  : 100,
	"attack" : 30,
	"dodge"  : 15,
	"parry"  : 20,
	"damage" : 25,
	"lvl"    : 70,
	"damage_type" : "����"
]),
([      "action" : "$N������״��һ�С�ľ�����㡹������$wֱ��$n��$l",
	"force"  : 110,
	"attack" : 31,
	"dodge"  : 20,
	"parry"  : 20,
	"damage" : 21,
	"lvl"    : 76,
	"damage_type" : "����"
]),
([      "action" : "$N���ֽ���һ�죬����$wƽƽ����$n��$l����һ�С�˫���Իء�",
	"force"  : 120,
	"attack" : 33,
	"dodge"  : 40,
	"parry"  : 20,
	"damage" : 25,
	"lvl"    : 82,
	"damage_type" : "����"
]),
([      "action" : "$N����$w�����̣�һ�С����Ƴ��ԡ���ֱָ$n��$l",
	"force"  : 130,
	"attack" : 36,
	"dodge"  : 30,
	"parry"  : 20,
	"damage" : 22,
	"lvl"    : 88,
	"damage_type" : "����"
]),
([      "action" : "$Nһ�С������չȡ���$w���������һ�ӣ���$n����˼��ĽǶȹ���",
	"force"  : 140,
	"attack" : 37,
	"dodge"  : 20,
	"parry"  : 25,
	"damage" : 25,
	"lvl"    : 94,
	"damage_type" : "����"
]),
([      "action" : "$Nʹ�����軨��·����һʱ����о���$w��Ӱ�ӣ���$n��֪��εֵ�",
	"force"  : 150,
	"attack" : 40,
	"dodge"  : 45,
	"parry"  : 25,
	"damage" : 23,
	"lvl"    : 100,
	"damage_type" : "����"
]),
([      "action" : "$Nһ�С�İ·��ɣ����$w�������㣬����$n��$l",
	"force"  : 160,
	"attack" : 43,
	"dodge"  : 35,
	"parry"  : 25,
	"damage" : 27,
	"lvl"    : 99,
	"damage_type" : "����"
]),
([      "action" : "$NͻȻ�̶�������һ�С�������������$w���¶��ϴ���$n",
	"force"  : 170,
	"attack" : 46,
	"dodge"  : 25,
	"parry"  : 25,
	"damage" : 29,
	"lvl"    : 106,
	"damage_type" : "����"
]),
([      "action" : "$N���Ų�������$wͻȻ���Լ������´̳���ȴ��һ�С����Ľ�����",
	"force"  : 180,
	"attack" : 48,
	"dodge"  : 35,
	"parry"  : 25,
	"damage" : 31,
	"lvl"    : 112,
	"damage_type" : "����"
]),
([      "action" : "$N������ˮ�滬��һ�㣬һ�С�������ҹ����ƽƽ����$n��$l��ȥ",
	"force"  : 190,
	"attack" : 51,
	"dodge"  : 40,
	"parry"  : 25,
	"damage" : 35,
	"lvl"    : 118,
	"damage_type" : "����"
]),
([      "action" : "$Nһ�С��������������$w�̵�$n������",
	"force"  : 200,
	"attack" : 53,
	"dodge"  : 45,
	"parry"  : 25,
	"damage" : 36,
	"lvl"    : 124,
	"damage_type" : "����"
]),
([      "action" : "$Nһ�С�ĵ�����᡹��$w�Ƴ�������Ȧ��ƽƽ����$n��$l��ȥ",
	"force"  : 210,
	"attack" : 57,
	"dodge"  : 45,
	"parry"  : 25,
	"damage" : 38,
	"lvl"    : 131,
	"damage_type" : "����"
]),
([      "action" : "$N��������棬������ǰһ�ˣ�һ�С���ҩ���项��$w��$n��$l��ȥ",
	"force"  : 220,
	"attack" : 58,
	"dodge"  : 45,
	"parry"  : 30,
	"damage" : 40,
	"lvl"    : 138,
	"damage_type" : "����"
]),
([      "action" : "$Nһ�С���ǰ���ࡹ������Ծ������$wɨ��$n��$l",
	"force"  : 250,
	"attack" : 61,
	"dodge"  : 45,
	"parry"  : 30,
	"damage" : 41,
	"lvl"    : 145,
	"damage_type" : "����"
]),

([      "action" : "$N������Ȼ֮ɫ������һ�С�����Բԡ���$w����$n��$l",
	"force"  : 280,
	"attack" : 63,
	"dodge"  : 35,
	"parry"  : 30,
	"damage" : 42,
	"lvl"    : 159,
	"damage_type" : "����"
]),
});

int valid_enable(string usage) { return usage == "sword" || usage == "parry"; }

int valid_learn(object me)
{
	if ((int)me->query_skill("force") < 60)
		return notify_fail("����ڹ���򲻵����޷�ѧϰ��Ů���Ľ�����\n");

	if ((int)me->query("neili") < 300)
		return notify_fail("�������̫��޷�ѧϰ��Ů���Ľ�����\n");

	if (me->query_skill("sword", 1) < me->query_skill("yunv-jian", 1))
		return notify_fail("��Ļ�������ˮƽ���ޣ��޷������������Ů������\n");

	return 1;
}

mapping query_action(object me, object weapon)
{
	int i, level;  
	level = (int) me->query_skill("yunv-jian", 1);
	for (i = sizeof(action); i > 0; i--)
		if (level > action[i-1]["lvl"])
			return action[NewRandom(i, 20, level / 5)];

}

int practice_skill(object me)
{
	object weapon;

	if (! objectp(weapon = me->query_temp("weapon")) ||
	    (string)weapon->query("skill_type") != "sword")
		return notify_fail("��ʹ�õ��������ԡ�\n");

	if ((int)me->query("qi") < 65)
		return notify_fail("���������������Ů������\n");

	if ((int)me->query("neili") < 65)
		return notify_fail("�����������������Ů������\n");

	me->receive_damage("qi", 52);
	me->add("neili", -58);
	return 1;
}

string perform_action_file(string action)
{
	return __DIR__"yunv-jian/" + action;
}
