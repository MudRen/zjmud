// huashan-ken.c ��ɽȭ��
// Modified by Venus Oct.1997

inherit SKILL;

mapping *action = ({
    ([  "action": "$Nʹһ�С�����Ǭ������ȭ������������ʽʹ�ϣ�"
		  "��ȭ�Ѵ���ȭ֮�״�������׼$n��$l��������һȭ",
	"dodge": 10,
	"parry": 20,
	"force": 40,
	"damage_type":  "����"
    ]),
    ([  "action": "$N��ȭͻȻ�ſ���ȭ�����ƣ�ֱ����Ϊ��ɨ��"
		  "һ�С����￴��������$n��$l�к���ȥ",
	"dodge": -5,
	"parry": 15,
	"force": 45,
	"damage_type":  "����"
    ]),
    ([  "action": "$N���ֻ�����ԣ�����һȦ��һ�С����������"
		  "��$n��$l����",
	"dodge": 15,
	"parry": 20,
	"force": 35,
	"damage_type":  "����"
    ]),
    ([  "action": "$N����һ������ȭ���һ�У���ȭʹ����÷��"
		  "ŪӰ������$n$l",
	"dodge": -10,
	"parry": -10,
	"force": 50,
	"damage_type":  "����"
    ]),
});

int valid_learn(object me)
{
    if( me->query_temp("weapon") || me->query_temp("secondary_weapon") )
	return notify_fail("����ɽȭ��������֡�\n");

    return 1;
}

int valid_enable(string usage)
{
    return usage=="unarmed" || usage=="parry";
}

int valid_combine(string combo) { return combo=="huashan-zhangfa"; }

mapping query_action(object me, object weapon)
{
    return action[random(sizeof(action))];
}

int practice_skill(object me)
{
    if( (int)me->query("qi") < 40 )
	return notify_fail("������������ˣ���Ϣһ�������ɡ�\n");

    me->receive_damage("qi", 35);
    return 1;
}
