// beidou-xianzong.c

inherit SKILL;

string *dodge_msg = ({
    "ֻ��$nһ�С������ȥ��������ƮȻ���ˣ������$N��һ�С�\n",
    "$nһ����������λ��������ݳ�����֮Զ���ܿ���$N���������ơ�\n",
    "$nʹ�������Ƕ���������һ��ƮȻ�ݳ��������ŵء�\n",
    "����$nһ�С��������С�������Ʈ�������ѱܿ���\n",
    "$n������ת��һ�С������硹ٿ�Ĳ�����Ӱ��\n",
    "����$n���β���������һ�С������ƿա�$N��һ�����˸��ա�\n",
    "ȴ��$n�㲻��أ�һ�С�Ⱥ���Ϳ͡����Դܿ����ߣ����˿�ȥ��\n",
    "$n����΢�Σ�һ�С��ɹ����졹�о����յرܿ���$N��һ�С�\n",
});

int valid_enable(string usage) { return (usage == "dodge") || (usage == "move");}

int valid_learn(object me) { return 1; }

string query_dodge_msg(string limb)
{
    return dodge_msg[random(sizeof(dodge_msg))];
}

int practice_skill(object me)
{
    if( (int)me->query("qi") < 50 )
       return notify_fail("�������̫���ˣ��������������ٲ�����\n");

    me->receive_damage("qi", 40);
    return 1;
}
