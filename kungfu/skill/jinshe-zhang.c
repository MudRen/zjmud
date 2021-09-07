// jinshe-zhang.c

inherit SKILL;

mapping *action = ({
([      "skill_name": "ǧ�߳���",
	"action": "$N˫��һ��һ�С�ǧ�߳������ó�������Ӱ£��$n��$l",
	"force" : 240,
	"attack": 31,
	"dodge" : 30,
	"parry" : 10,
	"damage": 60,
	"damage_type": "����"
]),
([      "skill_name": "ħ�����",
	"action": "$N����һ����˫�������Ƴ���һ�С��������ߡ�ǿ�����Ʒ�ֱ��$n��$l",
	"force" : 240,
	"attack": 22,
	"dodge" : 30,
	"parry" : 10,
	"damage": 55,
	"damage_type": "����"
]),
([      "skill_name": "˫������",
	"action": "$N˫�Ʒ׷ɣ�һ�С�˫�����项ֱȡ$n��$l",
	"force" : 240,
	"attack": 29,
	"dodge" : 10,
	"parry" : 30,
	"damage": 45,
	"damage_type": "����"
]),
([      "skill_name": "����ʽ",
	"action": "$N�����������ߣ�һ�С�����ʽ����ɭɭ�Ʒ��޿ײ����ػ���$n��$l",
	"force" : 240,
	"attack": 30,
	"dodge" : 10,
	"parry" : 50,
	"damage": 70,
	"damage_type": "����"
]),
([      "skill_name": "����ʽ",
	"action": "$N�������˫��ƽ�ƣ����������һ�С�����ʽ������$n��$l",
	"force" : 210,
	"attack": 38,
	"dodge" : 30,
	"parry" : 70,
	"damage": 50,
	"damage_type": "����"
]),
([      "skill_name": "��������",
	"action": "$N����������ǰ�������Ƴ���һ�С��������ơ�����$n$l",
	"force" : 210,
	"attack": 32,
	"dodge" : 30,
	"parry" : 70,
	"damage": 51,
	"damage_type": "����"
]),
([      "skill_name": "���߷���ҧ",
	"action": "$Nʹ�������߷���ҧ����������շ��𣬴ӿ��е�ͷ��$n��$l���ƹ���",
	"force" : 210,
	"attack": 25,
	"dodge" : 30,
	"parry" : 70,
	"damage": 42,
	"damage_type": "����"
]),
([      "skill_name": "������Ӱ",
	"action": "$Nʹ��һ�С�������Ӱ�������ƻ���Ϊʵ����$n��$l",
	"force" : 210,
	"attack": 38,
	"dodge" : 30,
	"parry" : 70,
	"damage": 50,
	"damage_type": "����"
]),
([      "skill_name": "���߲�˿��",
	"action": "$N���ƻ��˸�ȦȦ�������Ƴ���һ�С����߲�˿�֡�����$n$l",
	"force" : 210,
	"attack": 28,
	"dodge" : 30,
	"parry" : 70,
	"damage": 53,
	"damage_type": "����"
]),
([      "skill_name": "�����ΰ˷�",
	"action": "$Nʹ���������ΰ˷���������ɢ���˴�ͬʱ��$n��$l���ƹ���",
	"force" : 210,
	"attack": 27,
	"dodge" : 30,
	"parry" : 70,
	"damage": 47,
	"damage_type": "����"
]),
([      "skill_name": "����̽ͷ",
	"action": "$Nʹ�����������Ʒ�������̽ͷ��������Ȱ�����$n��ǰ��һ������$n��$l",
	"force" : 210,
	"attack": 31,
	"dodge" : 30,
	"parry" : 70,
	"damage": 55,
	"damage_type": "����"
]),
([      "skill_name": "��������",
	"action": "$N�������ᣬȫ�����һ�С��������졹��˫��������£�$n��ȫ��������������֮��",
	"force" : 210,
	"attack": 35,
	"dodge" : 30,
	"parry" : 70,
	"damage": 45,
	"damage_type": "����"
]),
});

int valid_learn(object me)
{
	if (me->query_temp("weapon") || me->query_temp("secondary_weapon")) 
		return notify_fail("��ϰ���������Ʊ�����֡�\n"); 

	if ((int)me->query("max_neili") < 500)
		return notify_fail("����������㣬�޷������������ơ�\n");

	if ((int)me->query_skill("force") < 80)
		return notify_fail("����ڹ���򲻹����޷������������ơ�\n");

	if ((int)me->query_skill("strike", 1) < (int)me->query_skill("jinshe-zhang", 1))
		return notify_fail("��Ļ����Ʒ�ˮƽ���ޣ��޷���������Ľ��������ơ�\n");

	return 1;
}

int valid_enable(string usage) { return usage=="strike" || usage=="parry"; }

mapping query_action(object me, object weapon)
{
	return action[random(sizeof(action))];
}

int practice_skill(object me)
{
	if( (int)me->query("qi") < 70 )
		return notify_fail("������������ˣ���Ϣһ�������ɡ�\n");

	if( (int)me->query("neili") < 55 )
		return notify_fail("������������ˣ���Ϣһ�������ɡ�\n");

	me->receive_damage("qi", 55);
	me->add("neili", -53);
	return 1;
}

int effective_level() { return 10;}
 
string *parry_msg = ({
	"$nʹ����ճ���־���˫��һ������ƫ��$N��$w��\n",
});

string *unarmed_parry_msg = ({
	"$nʩչ�����������ƣ����赭д�Ļ�����$N�Ĺ��ơ�\n",
});

string query_parry_msg(object weapon)
{
	if (weapon)
		return parry_msg[random(sizeof(parry_msg))];
	else
		return unarmed_parry_msg[random(sizeof(unarmed_parry_msg))];
}

string perform_action_file(string action)
{
	return __DIR__"jinshe-zhang/" + action;
}
