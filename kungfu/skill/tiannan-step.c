// tiannan-step.c ���ϲ���

inherit SKILL;

string *dodge_msg = ({
    "ֻ��$nһ�С����ذδС����������ϱ�ֱ���������࣬�����$N��һ�С�\n",
    "$nһ��������鳲��������ݳ�����֮Զ���ܿ���$N���������ơ�\n",
    "$nʹ������������������һ��ƮȻ�ݳ��������ŵء�\n"
    "����$n����Ʈ����һ�С��������С�����һ�ݣ����ѱܿ���\n",
    "$n������ת��һ�С��˷��ȥ��ٿ����һ��Ų�������ߣ��ܹ�����һ�С�\n",
    "����$n����һ�ã�һ�С��绯������$N��һ�����˸��ա�\n",
    "ȴ��$n�㲻��أ�һ�С�����ֱ�ϡ����Դܿ����ߣ����˿�ȥ��\n",
    "$n����΢�Σ�һ�С�������졹�о����յرܿ���$N��һ�С�\n"
});

int valid_enable(string usage) { return (usage == "dodge") || (usage == "move");}

int valid_learn(object me)
  { 
     if (me->query_skill("dodge",1) <= me->query_skill("tiannan-step",1) )
	return notify_fail("��Ļ����Ṧ�����������޷�������������ϲ�����\n");
    else    return 1;
  }

string query_dodge_msg(string limb)
{
    return dodge_msg[random(sizeof(dodge_msg))];
}

int practice_skill(object me)
{
    if( (int)me->query("qi") < 50 )
       return notify_fail("�������̫���ˣ���������������\n");

    me->receive_damage("qi", 40);
    return 1;
}
