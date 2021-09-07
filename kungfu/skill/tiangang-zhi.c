// tiangang-zhi.c ���ָѨ��
// modified by Venus Oct.1997
#include <ansi.h>
inherit SKILL;

mapping *action = ({
([      "action": "$N�������Ღ����������ָ���쵯������һʽ��������ġ���"
		  "����$n��$l",
	"force" : 90,
	"dodge" : 5,
	"damage": 15,
	"lvl"   : 0,
	"damage_type" : "����",
	"skill_name" : "�������"
]),
([      "action": "$N˫���������䣬��������$n��һʽ��������̶�������ֻ��Ƴ�ָ��"
		  "��ӿϮ��$n��$l",
	"force" : 140,
	"attack": 5,
	"parry" : 5,
	"dodge" : 5,
	"damage": 20,
	"lvl" : 40,
	"damage_type" : "����",
	"skill_name" : "������̶"
]),
([      "action": "$N������ȭ���ƣ�����Ť�������ߣ�һʽ�����߾��ɡ������Ҳ��ã�"
		  "����$n��$l",
	"force" : 170,
	"attack": 10,
	"parry" : 10,
	"dodge" : 15,
	"damage": 30,
	"lvl"   : 60,
	"damage_type" : "����",
	"skill_name" : "���߾���"
]),
([      "action": "$Nһʽ��������ɽ�������ֳ�أ�����ǰ̽���ָ����$n��$l",    
	"force" : 190,
	"attack": 20,
	"parry" : 15,
	"dodge" : 25,
	"damage": 40,
	"lvl"   : 80,
	"damage_type" : "����",
	"skill_name" : "������ɽ"
]),
([      "action": "$Nʹһʽ����������������Ӱ��ò���������$n����͵�����$n��$l",
	"force" : 220,
	"attack": 30,
	"parry" : 20,
	"dodge" : 30,
	"damage": 50,
	"lvl"   : 100,
	"damage_type" : "����",
	"skill_name" : "��������"
]),
([      "action": "$N���۴󿪴��أ���һ������һʽ���ض�ɽҡ��������͸����˫�ֿ�"
		  "��һ��������������������$n��$l",
	"force" : 270,
	"attack": 40,
	"parry" : 25,
	"dodge" : 45,
	"damage": 55,
	"lvl"   : 120,
	"damage_type" : "����",
	"skill_name" : "�ض�ɽҡ"
]),
([      "action": "$N������������Ʈ����˫�������Ķ���һʽ��ˮ�����¡����Ӹ���"
		  "�£����಻������$n��$l",
	"force" : 300,
	"attack": 50,
	"parry" : 20,
	"dodge" : 50,
	"damage": 60,
	"lvl"   : 140,
	"damage_type" : "����",
	"skill_name" : "ˮ������"
]),
([      "action": "$N�ڿն���˫�ƺ�һ��ʮָ�繳��һ�С�̩ɽѹ����������$n�Ļ�"
		  "�䣬�Ƶ������Ѽ�",
	"force" : 320,
	"attack": 60,
	"parry" : 25,
	"dodge" : 55,
	"damage": 70,
	"lvl"   : 160,
	"damage_type" : "����",
	"skill_name" : "̩ɽѹ��"
])
});

int valid_enable(string usage) { return usage == "finger" ||  usage == "parry"; }

int valid_combine(string combo) { return combo == "jinding-zhang"; }

int valid_learn(object me)
{
	if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
		return notify_fail(HIC"�����ָѨ��������֡�"NOR"\n");

	if ((int)me->query_skill("force") < 100)
		return notify_fail("����ڹ���򲻹����޷�ѧ���ָѨ����\n");

	if ((int)me->query("max_neili") < 500)
		return notify_fail("�������̫�����޷������ָѨ����\n");

	if (me->query_skill("finger", 1) < me->query_skill("tiangang-zhi", 1))
		return notify_fail("��Ļ���ָ��̫��޷�������������ָѨ����\n");

	return 1;
}

string query_skill_name(int level)
{
	int i;
	for(i = sizeof(action) - 1; i >= 0; i--)
		if (level >= action[i]["lvl"])
			return action[i]["skill_name"];
}

mapping query_action(object me, object weapon)
{
	int i, level;
	level = (int)me->query_skill("tiangang-zhi", 1);
	for (i = sizeof(action); i > 0; i--)
		if (level > action[i-1]["lvl"])
			return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
	if ((int)me->query("qi") < 70)
		return notify_fail("�������̫���ˣ��޷������ָѨ����\n");

	if ((int)me->query("neili") < 70)
		return notify_fail("��������������޷������ָѨ����\n");

	me->receive_damage("qi", 55);
	me->add("neili", -51);
	return 1;
}

string perform_action_file(string action)
{
	return __DIR__"tiangang-zhi/" + action;
}
