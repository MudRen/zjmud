// rouyun-steps.c  ���Ʋ���
// modified by Venus Oct.1997
// Made by deaner
#include <ansi.h>
inherit SKILL;

string *dodge_msg = ({
      "$nʹһʽ"+HIW"�����к�Ӱ��"NOR+"����������������ߣ������$N��һ�С�\n",
      "$n����ƮƮ��ʹ��һʽ"+MAG"���Ʋ�Ʈ����"NOR+"���ܹ���$N�Ĺ�����\n",
      "$nʹ��һʽ"+HIB"���������ơ�"NOR+"��$N��ǰ��û��$n����Ӱ��\n",
      "$nʩչ��һʽ"+HIG"�����겻����"NOR+"����Ӱ���ϣ���ǧ��һ��������$N�Ĺ��ơ�\n",
      "$n����ƮƮ��һʽ"+HIY"������ϼε��"NOR+"������ر��˿�ȥ��\n",
      "$n����ʹ��һʽ"+YEL"���ƺ�������"NOR+"�����绬����΢����Ӱ���ܿ���$N�Ĺ�����\n",
      "$n����ʹһʽ"+BLU"����Ӱ��ǧ��"NOR+"�����κ������ˣ�������ң�$N�Ĺ�����Ȼ��Ч��\n",
});

int valid_enable(string usage)
{
    return (usage == "dodge") || (usage == "move");
}

int valid_learn(object me)
{
    if ((int)me->query_dex() <= 30)
	return notify_fail("���������������������Ʋ�����");

    return 1;
}

string query_dodge_msg()
{
    return dodge_msg[random(sizeof(dodge_msg))];
}

int practice_skill(object me)
{
    if( (int)me->query("qi") < 50 )
	return notify_fail(HIC"�������̫���ˣ����������Ʋ�����"NOR"\n");

    if( (int)me->query("neili") < 50 )
	return notify_fail(HIC"�������̫���ˣ����������Ʋ�����"NOR"\n");

    me->receive_damage("qi", 45);
    me->add("neili", -20);
    return 1;
}

string perform_action_file(string action)
{
    return __DIR__"rouyun-steps/" + action;
}
