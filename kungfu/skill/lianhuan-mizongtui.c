// lianhuan-mizongtui.c ����������
// Vin 6/3/2001

inherit SKILL;

string *dodge_msg = ({
	"$n����΢΢һ�Σ�˫�������߳�����$NӲ�������ˡ�\n",
	"$n����ǰ���������һ̧����$N�Ĺ���ȫ�����أ�ֻ���Ա���\n",
	"$n˫�������أ��͵İεض��𣬶㿪��$N����ʽ��\n",
});

mapping *action = ({
([      "action" : "$N˫����Σ�����͵ط���һʽ�����ܽ��������ż�ζ�������$n��$l",
	"force" : 80,
	"attack": 10,
	"dodge" : 45,
	"parry" : 45,
	"damage": 10,
	"lvl"   : 0,
	"damage_type" : "����",
	"skill_name"  : "���ܽ���"
]),
([      "action" : "$N��Ŷٵأ���ת�����������ߣ�ֻһɲ�Ǽ�һ�����ҽ�һʽ����Ӱ�ȡ�������$n��$l",
	"force" : 100,
	"attack": 20,
	"dodge" : 50,
	"parry" : 50,
	"damage": 15,
	"lvl"   : 40,
	"damage_type" : "����",
	"skill_name"  : "��Ӱ��"
]),
([      "action" : "$N����һ�����ҽŷ�һ���߳���������׼��һʽ���۾�����������е�$n���ؿ�",
	"force" : 160,
	"attack": 30,
	"dodge" : 55,
	"parry" : 55,
	"damage": 18,
	"lvl"   : 80,
	"damage_type" : "����",
	"skill_name"  : "�۾����"
]),
([      "action" : "$NͻȻԾ��˫������Ȧת��һʽ����Ӱ���١�������糾������$n��ȫ��",
	"force" : 190,
	"attack": 35,
	"dodge" : 60,
	"parry" : 60,
	"damage": 20,
	"lvl"   : 120,
	"damage_type" : "����",
	"skill_name"  : "��Ӱ����"
]),
([      "action" : "$N���ֻ��أ�˫�Ž�������һʽ��˫�����ơ����ŽŲ���$n����������",
	"force" : 220,
	"attack": 35,
	"dodge" : 70,
	"parry" : 70,
	"damage": 25,
	"lvl"   : 140,
	"damage_type" : "����",
	"skill_name"  : "˫������"
]),
([      "action" : "$NͻȻ����ȴ�����ˣ�һ��ǰ�շ����ҽ����϶���һʽ�����Ƿ�׹������$n������ֱ������",
	"force" : 260,
	"attack": 40,
	"dodge" : 90,
	"parry" : 90,
	"damage": 30,
	"lvl"   : 160,
	"damage_type" : "����",
	"skill_name"  : "���Ƿ�׹"
]),
([      "action" : "$Nʹһʽ�����ζ�λ����ȫ��ͻȻ������ת��˫���ǰ����Ѹ���޼�����$n���ؿ�",
	"force" : 290,
	"attack": 40,
	"dodge" : 100,
	"parry" : 100,
	"damage": 30,
	"lvl"   : 180,
	"damage_type" : "����",
	"skill_name"  : "���ζ�λ"
]),
([      "action" : "$N����Ծ�𣬿������������һ����һʽ���������١���˫�������������$n��$l",
	"force" : 340,
	"attack": 45,
	"dodge" : 115,
	"parry" : 115,
	"damage": 35,
	"lvl"   : 200,
	"damage_type" : "����",
	"skill_name"  : "��������"
]),
});

int valid_enable(string usage) { return usage=="unarmed" ||  usage=="parry" ||  usage=="dodge"; } 

int valid_learn(object me)
{
	if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
		return notify_fail("ѧϰ���������ȱ�����֡�\n");

	if ((int)me->query_skill("force") < 140)
		return notify_fail("����ڹ���򲻹����޷�ѧ���������ȡ�\n");

	if ((int)me->query("max_neili") < 800)
		return notify_fail("�������̫�����޷������������ȡ�\n");

	if ((int)me->query_skill("unarmed", 1) < (int)me->query_skill("lianhuan-mizongtui", 1))
		return notify_fail("��Ļ���ȭ��ˮƽ���ޣ��޷�������������������ȡ�\n");

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
	level = (int)me->query_skill("lianhuan-mizongtui", 1);
	for(i = sizeof(action); i > 0; i--)
	    if(level > action[i-1]["lvl"])
		return action[NewRandom(i, 20, level/5)];
}

string query_dodge_msg(string limb)
{
	return dodge_msg[random(sizeof(dodge_msg))];
}

int practice_skill(object me)
{
	if ((int)me->query("qi") < 100)
	       return notify_fail("�������̫���ˡ�\n");

	if ((int)me->query("neili") < 80)
	       return notify_fail("����������������������ȡ�\n");

	me->receive_damage("qi", 80);
	me->add("neili", -60);

	return 1;
}

string perform_action_file(string action)
{
	return __DIR__"lianhuan-mizongtui/" + action;
}

