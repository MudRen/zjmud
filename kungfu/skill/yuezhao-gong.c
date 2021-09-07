#include <ansi.h>
inherit SKILL;
 
mapping *action = ({
([      "action": "�ں��������У�$Nʹһ�С�Խצ�֡���˫���繳��ꫣ�����$n��$l",
	"force" : 100,
	"attack": 28,
	"dodge" : 17,
	"parry" : 0,
	"damage": 13,
	"lvl"   : 0,
	"skill_name" : "Խצ��" ,
	"damage_type" : "ץ��"
]),
([      "action": "$N����һԾ���������ϣ�ʹ��һ�С�׷���֡�������ֱֱץ��$n��$l",
	"force" : 130,
	"attack": 35,
	"dodge" : 20,
	"parry" : 5,
	"damage": 20,
	"lvl"   : 10,
	"skill_name" : "׷����" ,
	"damage_type" : "ץ��"
]),
([      "action": "$N˫��ƽ�죬ʮָ΢΢���¶�����һ�С�����֡�����$n��$l",    
	"force" : 160,
	"attack": 39,
	"dodge" : 32,
	"parry" : 10,
	"damage": 25,
	"lvl"   : 20,
	"skill_name" : "�����" ,
	"damage_type" : "ץ��"
]),
([      "action": "$Nʹ��һ�С�׷����硹��������Ϣ��������$n��ǰ���͵�һצ����ץ��$n��$l",
	"force" : 172,
	"attack": 42,
	"dodge" : 38,
	"parry" : 19,
	"damage": 29,
	"lvl"   : 40,
	"skill_name" : "׷�����" ,
	"damage_type" : "ץ��"
]),
([      "action": "$N˫��ƽ����ǰ�����ֻ�ס���ţ�һ�С��������᡹��������$n��$l",
	"force" : 187,
	"attack": 45,
	"dodge" : 41,
	"parry" : 21,
	"damage": 33,
	"lvl"   : 60,
	"skill_name" : "��������" ,
	"damage_type" : "ץ��"
]),
([      "action": "$Nʹ����˫�����ơ����ͺ�һ����˫�ֻ���Ϊצ��һǰһ��ץ��$n��$l",
	"force" : 203,
	"attack": 51,
	"dodge" : 49,
	"parry" : 22,
	"damage": 36,
	"lvl"   : 80,
	"skill_name" : "˫������" ,
	"damage_type" : "ץ��"
]),
([      "action": "$N����б��$n����֮�䣬һ�С�����é®��������ȡĿ�����ַ���$n���ɲ�",
	"force" : 245,
	"attack": 56,
	"dodge" : 53,
	"parry" : 27,
	"damage": 41,
	"lvl"   : 100,
	"skill_name" : "����é®" ,
	"damage_type" : "ץ��"
]),
([      "action": "$Nʹ������н��������˫צ����������׼$n��$l����ץ��",
	"force" : 270,
	"attack": 61,
	"dodge" : 58,
	"parry" : 38,
	"damage": 45,
	"lvl"   : 120,
	"skill_name" : "��н����" ,
	"damage_type" : "ץ��"
])
});

int valid_enable(string usage) { return usage == "claw" ||  usage == "parry"; }

int valid_learn(object me)
{
	if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
		return notify_fail("��Խצ��������֡�\n");

	if ((int)me->query_skill("force") < 50)
		return notify_fail("����ڹ���򲻹����޷�ѧԽצ����\n");

	if ((int)me->query("max_neili") < 400)
		return notify_fail("���������Ϊ̫�����޷���Խצ����\n");

	if ((int)me->query_skill("claw") < 30)
		return notify_fail("��Ļ���צ���ȼ�̫�ͣ��޷�ѧԽצ����\n");

	if ((int)me->query_skill("claw", 1) < (int)me->query_skill("yuezhao-gong", 1))
		return notify_fail("��Ļ���צ�����ˮƽ���ޣ��޷����������Խצ����\n");

	return 1;
}

string query_skill_name(int level)
{
	int i;
	for (i = sizeof(action); i > 0; i--)
		if (level >= action[i-1]["lvl"])
			return action[i-1]["skill_name"];
}

mapping query_action(object me, object weapon)
{
	int i, level;
	level = (int) me->query_skill("yuezhao-gong",1);
	for (i = sizeof(action); i > 0; i--)
		if (level > action[i-1]["lvl"])
			return action[NewRandom(i, 20, level / 5)];

}

int practice_skill(object me)
{
	if (me->query_temp("weapon") ||
	    me->query_temp("secondary_weapon"))
		return notify_fail("Խצ�����������ϰ��\n");

	if ((int)me->query("qi") < 70)
		return notify_fail("�������̫���ˡ�\n");

	if ((int)me->query("neili") < 80)
		return notify_fail("�������������Խצ����\n");

	me->receive_damage("qi", 60);
	me->add("neili", -69);
	return 1;
}

string perform_action_file(string action)
{
	return __DIR__"yuezhao-gong/" + action;
}

