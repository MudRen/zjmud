// anying-fuxiang.c  ��Ӱ����

inherit SKILL;

string *dodge_msg = ({
    "$nһ������������ͷ��������$N�Ĺ���Ʈ�𣬴��ݶ����һ�С�\n",
    "$nʹ��һ�С���Į����ֱ������Ȼ�������࣬���$N���˸��ա�\n",
    "$n����һҡ���ó�������Ӱ��һ�С���Ӱ��б���������$N�Ĺ��ơ�\n",
    "$nһ�С���������ˮ������Ծ��ٿ��������$N���\n",
    "$n��һҡ����һ�Σ�һ�С����֪����������������\n",
    "$n˫��һ�㣬бб����ʹ����б���ӻ��ɡ�������$N��ࡣ\n",
});

int valid_enable(string usage) 
{ 
    return usage == "dodge" || usage == "move";
}

int valid_learn(object me)
  { 
     if (me->query_skill("dodge",1) <= me->query_skill("anying-fuxiang",1) )
	return notify_fail("��Ļ����Ṧ�����������޷���������İ�Ӱ���㡣\n");
    else    return 1;
  }

string query_dodge_msg(string limb)
{
	return dodge_msg[random(sizeof(dodge_msg))];
}

int practice_skill(object me)
{
	if ((int)me->query("qi") < 50)
	    return notify_fail("�������̫���ˣ���������Ӱ���㡣\n");

	if (me->query_skill("anying-fuxiang", 1) < 30)
		me->receive_damage("qi", 10);
	else
	if (me->query_skill("anying-fuxiang", 1) < 50)
		me->receive_damage("qi", 25);
	else
		me->receive_damage("qi", 40);

	return 1;
}
