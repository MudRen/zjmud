// jiaohua-bangfa.c �л�����
// Modified by Venus Oct.1997

inherit SKILL;

mapping *action = ({
([  "action" : "$Nб���ǰһ���������죬����$w��ɨ$n��$l",
    "force" : 220,
    "damage": 40,
    "dodge" : 50,
    "damage_type" : "����"
]),
([  "action" : "$N��Ȼֱ������գ��ܾ�Ҳ������Ӱ��$n����Ѱ�䣬$N��"
	       "�������£�$w����$n��$l",
    "force" : 210,
    "damage": 45,
    "dodge" : 55,
    "damage_type" : "����"
]),
([  "action" : "$Nԭ��һ���������ȴ����ص�һɲ�ǣ�������$nƽ�ɹ�"
	       "ȥ������$wָ��$n��$l",
    "force" : 210,
    "damage": 35,
    "dodge" : 60,
    "damage_type" : "����"
]),
([  "action" : "$NͻȻһ����ת��$w��ɨһȦ��Ю�����ҵľ�������$n��$l",    
    "force" : 200,
    "damage": 45,
    "dodge" : 65,
    "damage_type" : "����"
]),
([  "action" : "$N��ǰ�˳���˳��һ�������ŷ�����������$wб���ϻ���$n��$l",
    "force" : 220,
    "damage": 30,
    "dodge" : 55,
    "damage_type" : "����"
])
});

int valid_enable(string usage)
{
	return usage=="staff" ||
	       usage=="parry" ;
}

int valid_learn(object me)
{
    if ((int)me->query("max_neili") < 250)
	return notify_fail("�������̫�����޷����л�������\n");

    if ((int)me->query_dex() < 26)
	return notify_fail("������������޷����л�������\n");

    return 1;
}

mapping query_action(object me, object weapon)
{
    return action[random(sizeof(action))];
}

int practice_skill(object me)
{
	object weapon;

    if ((int)me->query("qi") < 60)
	return notify_fail("�������̫���ˡ�\n");

    if ((int)me->query("neili") < 50)
	return notify_fail("��������������л�������\n");

	if (! objectp(weapon = me->query_temp("weapon")) ||
	    (string)weapon->query("skill_type") != "staff")
		return notify_fail("��ʹ�õ��������ԡ�\n");

    me->receive_damage("qi", 45);
    me->add("neili", -38);
    return 1;
}

