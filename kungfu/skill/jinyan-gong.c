// jinyan-gong.c ���㹦
// By Lgg,1998.10

inherit SKILL;

string *dodge_msg = ({
	"$n����ڵ���һ�㣬���ΰεض��𣬶㿪����һ�С�\n",
	"ȴ����$n����һת��ͻȻת����$N�����\n",
	"$n����$N��������ʽƮ������������һƬ΢���е�����һ�㡣\n",
	"$n������һ�Ρ���һ������֪��ô�ģ��ӹ����ļ�϶�����˳�����\n",
	"$n�㲻��ص�Χ��$N����������Ȧ����$N��һ�б��˿�ȥ��\n",
	"$n����������Ȧ����������һ����Ȧ�����θ߸ߵذ���������\n",
});

int valid_enable(string usage)
{
	return (usage == "dodge") || (usage == "move");
}

int valid_learn(object me)
  { 
     if (me->query_skill("dodge",1) <= me->query_skill("jinyan-gong",1) )
	return notify_fail("��Ļ����Ṧ�����������޷���������Ľ��㹦��\n");
    else    return 1;
  }

string query_dodge_msg(string limb)
{
	return dodge_msg[random(sizeof(dodge_msg))];
}

int practice_skill(object me)
{
	if( (int)me->query("qi") < 50 )
		return notify_fail("�������̫���ˣ�������ϰ���㹦��\n");

	me->receive_damage("qi", 40);
	return 1;
}
