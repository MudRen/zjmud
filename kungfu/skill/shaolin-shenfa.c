// shaolin-shenfa.c ������
// modified by Venus Oct.1997

inherit SKILL;

string *dodge_msg = ({
	"$nһʽ��һέ�ɽ�����ǰ��Žż�Ÿ��࿿��������������ˮ�㻬�����ࡣ\n",
	"$nһʽ�������Ӳ�����˫��ǰ�죬ȫ������ƽ�ɣ���ʱ������$N���������ơ�\n",
	"$nһʽ���Ʋ����Ρ����㲻�����ֲ�̧��һת�ۼ���Ƶ���$N�����\n",
	"$nһʽ������Ӱ����һת��䣬����˷�Ʈ����������$n����Ӱ����$N������롣\n",
	"$nһʽ���������ա���ȫ���ֱ���εض����ڰ����һת�����䵽����Զ�ĵط���\n",
	"$nһʽ������˫�ɡ��������������������ݷ����У���$Nͷ����Ծ������\n",
	"$nһʽ��������ˮ����˫�ŵ�أ�ȫ��Ϊһ����Ӱ����������$N���˼�ת��\n",
	"$nһʽ���ɷ�鳲�������������ݰ㼱ת�������γ�һ�������У���$N������䣬�������á�\n",
});

int valid_enable(string usage)
{
    return usage == "dodge" || usage == "move";
}

int valid_learn(object me)
{
    return 1;
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

