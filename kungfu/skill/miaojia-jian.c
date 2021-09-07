#include <ansi.h>

inherit SKILL;

mapping *action = ({
([   "action" : "$N��¶΢Ц������$wһ�������Ⱪ��������$n��$l",
     "force"  : 50,
     "attack" : 15,
     "dodge"  : 10,
     "parry"  : 25,
     "damage" : 10,
     "lvl"    : 0,
     "damage_type":  "����"
]),
([   "action" : "$N����ͻ�������ж��䣬����$w��һ�����벻���ķ�λб����$n��$l",
     "force"  : 70,
     "attack" : 25,
     "dodge"  : 25,
     "parry"  : 30,
     "damage" : 5,
     "lvl"    : 10,
     "damage_type":  "����"
]),
([   "action" : "$N�������ߣ����׸������������$w��Ȼ���ϣ�����$n��$l",
     "force"  : 75,
     "attack" : 33,
     "dodge"  : 22,
     "parry"  : 32,
     "damage" : 20,
     "lvl"    : 20,
     "damage_type":  "����"
]),
([   "action" : "$N����һ�Σ����Ӷ��ϣ�����$w����һ������׼$n��$l��������",
     "force"  : 90,
     "attack" : 39,
     "dodge"  : 40,
     "parry"  : 35,
     "damage" : 25,
     "lvl"    : 30,
     "damage_type":  "����"
]),
([   "action" : "$Nһ����������$n����Ӱ���棬����$w���Ȼ��������$n��$l��ȥ",
     "force"  : 100,
     "attack" : 43,
     "dodge"  : 60,
     "parry"  : 40,
     "damage" : 25,
     "lvl"    : 40,
     "damage_type":  "����"
]),
([   "action" : "$Nһ����������$w����б������ֱָ$n��$l",
     "force"  : 130,
     "attack" : 51,
     "dodge"  : 50,
     "parry"  : 45,
     "damage" : 30,
     "lvl"    : 50,
     "damage_type":  "����"
]),
([   "action" : "$N΢΢һ��ת������$wȴ�������´���������$n��$l",
     "force"  : 150,
     "attack" : 62,
     "dodge"  : 40,
     "parry"  : 47,
     "damage" : 30,
     "lvl"    : 60,
     "damage_type":  "����"
]),
([   "action" : "$N��ɫ΢�䣬һ�С����ﳯ���������ж�ʱ��������ޱȣ�����$w��ƥ\n"
		"��������$n��$l",
     "force"  : 180,
     "attack" : 71,
     "dodge"  : 30,
     "parry"  : 52,
     "damage" : 40,
     "lvl"    : 70,
     "damage_type":  "����"
]),
([   "action" : "$N�������ף�����һ�С�ϴ�����б��¡�������$w�й�ֱ����Ѹ���ޱ�\n"
		"����$n��$l��ȥ",
     "force"  : 200,
     "attack" : 85,
     "dodge"  : 20,
     "parry"  : 54,
     "damage" : 35,
     "lvl"    : 80,
     "damage_type":  "����"
]),
([   "action" : "$N�ݲ����ߣ������͵�����$n���䣬$n��Ҫ����ط���ֻ��ɲ�Ǽ佣��һ����$Nһ\n"
		"�С�ӭ���ȷ�����ɽ����$w�Ѿ���������",
     "force"  : 220,
     "attack" : 88,
     "dodge"  : 30,
     "parry"  : 62,
     "damage" : 47,
     "lvl"    : 90,
     "damage_type":  "����"
]),
([   "action" : "$N����ಽ��һ�С�������´��ʡ�������$w���ּ�����������ৡ���һ����$n��$l��ȥ",
     "force"  : 240,
     "attack" : 91,
     "dodge"  : 65,
     "parry"  : 65,
     "damage" : 58,
     "lvl"    : 100,
     "damage_type":  "����"
]),
([   "action" : "$Nһ�С�����ת�����롹����ؼ���һ�����ֳ�ǰ����������$w��Ϊһ�������Ļ���\n"
		"��$n��$l��ȥ",
     "force"  : 265,
     "attack" : 93,
     "dodge"  : 40,
     "parry"  : 68,
     "damage" : 62,
     "lvl"    : 110,
     "damage_type":  "����"
]),
([   "action" : "$Nһ�С��ϲ��Ʊ�ժ�¡�������Ծ�𣬲�����Ӱ������ȴ�ִӰ���д��£�˫������\n"
		"$w�����Ʊ��˵ش���$n��$l",
     "force"  : 290,
     "attack" : 97,
     "dodge"  : 60,
     "parry"  : 72,
     "damage" : 68,
     "lvl"    : 120,
     "damage_type":  "����"
]),
([   "action" : "$Nһ�С����ý��׺���᡹������$w���͡���һ��б������գ��漴���¡��ৡ����£�\n"
		"����һ�����֣���$n��$l��ȥ",
     "force"  : 310,
     "attack" : 100,
     "dodge"  : 45,
     "parry"  : 75,
     "damage" : 76,
     "lvl"    : 130,
     "damage_type":  "����"
]),
([   "action" : "$N����΢̧��һ�С����������ر��������������������$w�͵����·����𣬼���һ��\n"
		"���練��$n��$l",
     "force"  : 330,
     "attack" : 105,
     "dodge"  : 50,
     "parry"  : 82,
     "damage" : 85,
     "lvl"    : 140,
     "damage_type":  "����"
]),
});

int valid_enable(string usage) {return usage == "sword" || usage == "parry";}

int valid_learn(object me)
{
	if ((int)me->query("max_neili") < 700)
		return notify_fail("�������������\n");

	if ((int)me->query_skill("force") < 90)
		return notify_fail("����ڹ����̫ǳ��\n");

	if ((int)me->query_skill("sword", 1) < 100)
		return notify_fail("��Ļ���������򲻹����޷�ѧϰ��ҽ�����\n");

	if ((int)me->query_skill("sword", 1) < (int)me->query_skill("miaojia-jian", 1))
		return notify_fail("��Ļ�������ˮƽ���ޣ��޷������������ҽ�����\n");

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
	level   = (int) me->query_skill("miaojia-jian",1);
	for(i = sizeof(action); i > 0; i--)
		if(level > action[i-1]["lvl"])
			return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
	object weapon;

	if (!objectp(weapon = me->query_temp("weapon")) ||
	    (string)weapon->query("skill_type") != "sword")
		return notify_fail("��ʹ�õ��������ԡ�\n");

	if ((int)me->query("qi") < 60)
		return notify_fail("�������Ŀǰû�а취��ϰ��ҽ�����\n");

	if ((int)me->query("neili") < 70)
		return notify_fail("��������������޷���ϰ��ҽ�����\n");
	
	me->add("qi", -50);
	me->add("neili", -62);
	return 1;
}

string perform_action_file(string action)
{
	return __DIR__"miaojia-jian/" + action;
}

