// zhuifeng-steps.c  ׷�粽
// modified by Venus Oct.1997
// by jacki

inherit SKILL;

string *dodge_msg = ({
    "$nһ���������衹������Ʈ�������������$N��һ�С�\n",
    "$n����ƮƮ��ʹ��һ�С�������ת�����ܹ���$N�Ĺ�����\n",
    "$nʹ�����Ʋ����Ρ�����ǧ��һ��������$N�Ĺ��ơ�\n",
    "$n����ƮƮ��һ�С����˷���ȥ���������ر��˿�ȥ��\n"
});

int valid_enable(string usage)
{
    return (usage == "dodge") || (usage == "move");
}

int valid_learn(object me) { return 1; }

string query_dodge_msg(string limb)
{
    return dodge_msg[random(sizeof(dodge_msg))];
}

int practice_skill(object me)
{
    if( (int)me->query("qi") < 50 )
	return notify_fail("�������̫���ˣ�������׷�粽��\n");

    me->receive_damage("qi", 40);
    return 1;
}
