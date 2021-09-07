// taxue-wuhen.c ̤ѩ�޺�

inherit SKILL;

string *dodge_msg = ({
    "$n��һ����һ�Σ��漴�ص�ԭ�أ����ɵض����$N��һ�С�\n",
    "$n����Ծ��һ���շ�����˳������һ�ߡ�\n",
    "$n�������Ա�һ�ݣ�������$N�����൱�ľ��룬$N��һ����ȻʧЧ��\n",
    "$n������ϣ������Ծ��$N��������$N�ı���\n",
    "$n���μ�����б��ǰһ������Ȼ�Ѿ��㿪��$N����һ�С�\n",
    "$N��ǰһ����ȴ��$n��Ȼ�����Լ�������֮Զ��ȴû��$n��ζ���Լ��Ĺ�����\n",
    "$Nһ��������$n��û����Ӱ��$N��ת��ȴ��$n���Ƕ����Լ����֡�\n",
    "$Nһ�й�����$n��Ȼ������$NãȻ�Ĺˣ�ȴ����$n��Ӱ�ӣ�\n",
});

int valid_enable(string usage) { return (usage == "dodge") || (usage == "move"); }

int valid_learn(object me)
  { 
     if (me->query_skill("dodge",1) <= me->query_skill("taxue-wuhen",1) )
	return notify_fail("��Ļ����Ṧ�����������޷����������̤ѩ�޺ۡ�\n");
    else    return 1;
  }

string query_dodge_msg(string limb)
{
    return dodge_msg[random(sizeof(dodge_msg))];
}

int practice_skill(object me)
{
    if((int)me->query("qi") < 50 )
	return notify_fail("�������̫���ˣ�������̤ѩ�޺ۡ�\n");

    me->receive_damage("qi", 40);
    return 1;
}
