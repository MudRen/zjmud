// fireice-strike.c ���溮����

inherit SKILL;

mapping *action = ({
([      "action": "$N˫��һ��һ�С�������ӿ��������ɨ��$n��$l",
	"force" : 100,
	"attack": 18,
	"dodge" : 30,
	"parry" : 15,
	"damage": 40,
	"lvl"   : 0,
	"damage_type": "����"
]),
([      "action": "$Nһ�С���ѩ���졹������ͻȻ��ת��������$n��˫������$n��$l",
	"force" : 200,
	"attack": 25,
	"dodge" : 40,
	"parry" : 30,
	"damage": 45,
	"lvl"   : 30,
	"damage_type": "����"
]),
([      "action": "$N�������������֣�һ�С�����ѩƮ����Ѹ���ޱȵ�ץ��$n��$l",
	"force" : 250,
	"attack": 35,
	"dodge" : 50,
	"parry" : 55,
	"damage": 45,
	"lvl"   : 60,
	"damage_type": "����"
]),
([      "action": "$N����һ����ͻȻһ�С�ǧ����⡹����������$n��$l",
	"force" : 330,
	"attack": 42,
	"dodge" : 40,
	"parry" : 65,
	"damage": 50,
	"lvl"   : 120,
	"damage_type": "����"
]),
});

int valid_enable(string usage) { return usage == "strike" || usage == "parry"; }

int valid_combine(string combo) { return combo == "meinv-quan"; }

mapping query_action(object me, object weapon)
{
	int i, level;
	level = (int)me->query_skill("fireice-strike", 1);
	for (i = sizeof(action); i > 0; i--)
		if (level > action[i-1]["lvl"])
			return action[NewRandom(i, 20, level / 5)];
}

int valid_learn(object me)
{
	if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
		return notify_fail("�����溮���Ʊ�����֡�\n");

	if ((int)me->query_skill("force") < 100)
		return notify_fail("����ڹ���򲻹����޷������溮���ơ�\n");

	if ((int)me->query("max_neili") < 450)
		return notify_fail("�������̫�����޷������溮���ơ�\n");

	if (me->query_skill("strike", 1) < me->query_skill("fireice-strike", 1))
		return notify_fail("��Ļ����Ʒ�ˮƽ���ޣ��޷�������������溮���ơ�\n");

	return 1;
}


int practice_skill(object me)
{
	if ((int)me->query("qi") < 60)
		return notify_fail("�������̫���ˣ�����Ϣһ�°ɡ�\n");

	if ((int)me->query("neili") < 60)
		return notify_fail("����������������溮���ơ�\n");

	if (me->query_skill("hanbing-strike", 1) < 50)
		me->receive_damage("qi", 30);
	else
		me->receive_damage("qi", 50);

	me->add("neili", -54);
	return 1;
}
