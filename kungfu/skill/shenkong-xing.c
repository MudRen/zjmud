// shenkong-xing.c �����
// written by That
//


inherit SKILL;

string *dodge_msg = ({
      "$nʹ��һ�С��Ŀա�����������Ʈȥ��\n",
      "$nʹ��һ�С����Կա���˫��һ�㣬Ծ������֮�⡣\n",
      "$nʹ��һ�С����ա�������һ�䣬����$N���\n",
      "$n���һ����ʹ��һ�С��󰲿ա�����$Nͷ��Խ����\n",
      "$nʹ��һ�С���ա���������Ʈȥ��˲��������$N��ǰ��\n",
      "$nʹ��һ�С���տա�����ʱ$N��Χ����$n����Ӱ��\n",
});

int valid_enable(string usage) { return (usage == "dodge") || (usage == "move");
 }

int valid_learn(object me) { return 1; }

string query_dodge_msg(string limb)
{
    return dodge_msg[random(sizeof(dodge_msg))];
}

int practice_skill(object me)
{
      if((int)me->query("qi") < 50 )
	   return notify_fail("�������̫���ˣ�����������С�\n");

      me->receive_damage("qi", 40);
      return 1;
}
