// xuanming_poison.c
// by jeeny

#include <ansi.h>

inherit F_CLEAN_UP;

int dispel(object me, object ob, int duration)
{
	int n;

	n = ob->query_condition("xuanming_poison") -
	    (int)me->query_skill("jiuyang-shengong", 1) - 
	    (int)me->query_skill("force") / 100;

	if (n < 1)
		ob->clear_condition("xuanming_poison");
	else
		ob->apply_condition("xuanming_poison", n);

	if (me != ob)
		tell_object(me, "�������ڹ�������" + ob->name() + "�������ڵĺ�����\n");  
	else
		tell_object(me, "�������ڹ�����ʼ�������ڵĺ�����\n");  
	
	return 1;
}

int update_condition(object me)
{
	int limit;

	if (! living(me) && (me->query("eff_qi") < 20 || me->query("eff_jing") < 10))
	{
		me->set_temp("������ڤ�ƶ�������������"); 
		me->die();
		return 0;
	} else
	{
		me->receive_wound("qi", 50);
		me->receive_wound("jing", 50);
		tell_object(me, MAG"���е���ڤ����֮�������ˡ�"NOR"\n");
		message("vision", MAG + me->name() + MAG "����ֱ�������"
			"��������ͣ��"NOR"\n",
			environment(me), ({ me }));
	}
	
	return 1;
}
