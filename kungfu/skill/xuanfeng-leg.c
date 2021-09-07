// xuanfeng-leg.c ����ɨҶ��
// modified by Venus Oct.1997

inherit SKILL;

mapping *action = ({
([      "action" : "$N˫����Σ�����͵ط���һʽ��������ӿ�����ż�ζ�����"
		   "��$n��$l",
	"force"  : 80,
	"damage" : 20,
	"dodge" : 15,
	"damage_type" : "����",
	"lvl" : 0,
	"skill_name" : "������ӿ"
]),
([      "action" : "$N��Ŷٵأ���ת�����������ߣ�ֻһɲ�Ǽ�һ�����ҽ�һʽ"
		   "���չ�������������$n��$l",
	"force"  : 120,
	"damage" : 25,
	"dodge" : 10,
	"damage_type" : "����",
	"lvl" : 15,
	"skill_name" : "�չ�����"
]),
([      "action" : "$N����һ��������Ť��ס$n�����֣��ҽ�ͬʱ�߳���������׼��һ"
		   "ʽ����Ԩ���ԡ������е�$n���ؿ�",
	"force"  : 150,
	"damage" : 30,
	"dodge" : 15,
	"damage_type" : "����",
	"lvl" : 30,
	"skill_name" : "��Ԩ����"
]),
([      "action" : "$NͻȻԾ��˫������Ȧת��һʽ�������Ҷ��������糾������"
		   "$n��ȫ��",
	"force"  : 190,
	"damage" : 35,
	"dodge" : 15,
	"damage_type" : "����",
	"lvl" : 50,
	"skill_name" : "�����Ҷ"
]),
([      "action" : "$N���ֻ��أ�˫�Ž�������һʽ����ɨ���ơ����ŽŲ���$n����������",
	"force"  : 220,
	"damage" : 40,
	"dodge" : 20,
	"damage_type" : "����",
	"lvl" : 70,
	"skill_name" : "��ɨ����"
]),
([      "action" : "$NͻȻ����ȴ�����ˣ�һ��ǰ�շ����ҽ����϶���һʽ������׹"
		   "�ء�����$n������ֱ������",
	"force"  : 250,
	"damage" : 45,
	"dodge" : 35,
	"damage_type" : "����",
	"lvl" : 90,
	"skill_name" : "����׹��"
]),
([      "action" : "$Nʹһʽ��˷�紵ѩ����ȫ��ͻȻ������ת��˫���ǰ����Ѹ��"
		   "�޼�����$n���ؿ�",
	"force"  : 280,
	"damage" : 50,
	"dodge" : 30,
	"damage_type" : "����",
	"lvl" : 110,
	"skill_name" : "˷�紵ѩ"
]),
([      "action" : "$N����Ծ�𣬿������������һ�����ˣ�һʽ���׶����졹��˫��"
		   "�����������$n��$l",
	"force"  : 300,
	"damage" : 60,
	"attack" : 45,
	"dodge" : 35,
	"damage_type" : "����",
	"lvl" : 130,
	"skill_name" : "�׶�����"
]),
});

int valid_enable(string usage) { return usage == "unarmed" ||  usage == "parry"; }

int valid_combine(string combo) { return combo == "luoying-shenzhang"; }

int valid_learn(object me)
{
	if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
		return notify_fail("ѧϰ����ɨҶ�ȱ�����֡�\n");

	if ((int)me->query_skill("force") < 80)
		return notify_fail("����ڹ���򲻹����޷�ѧ����ɨҶ�ȡ�\n");

	if ((int)me->query("max_neili") < 400)
		return notify_fail("�������̫�����޷�������ɨҶ�ȡ�\n");

	if ((int)me->query_skill("unarmed", 1) < (int)me->query_skill("xuanfeng-leg", 1))
		return notify_fail("��Ļ���ȭ��ˮƽ���ޣ��޷��������������ɨҶ�ȡ�\n");

	return 1;
}

string query_skill_name(int level)
{
	int i;
	for(i = sizeof(action) - 1; i >= 0; i--)
		if(level >= action[i]["lvl"])
			return action[i]["skill_name"];
}

mapping query_action(object me, object weapon)
{
	int i, level;
	level = (int)me->query_skill("xuanfeng-leg", 1);
	for (i = sizeof(action); i > 0; i--)
		if(level > action[i - 1]["lvl"])
			return action[NewRandom(i, 20, level / 5)];
}

int practice_skill(object me)
{
	if ((int)me->query("qi") < 60)
		return notify_fail("�������̫���ˡ�\n");

	if ((int)me->query("neili") < 60)
		return notify_fail("�����������������ɨҶ�ȡ�\n");

	me->receive_damage("qi", 45);
	me->add("neili", -51);

	return 1;
}

string perform_action_file(string action)
{
	return __DIR__"xuanfeng-leg/" + action;
}
