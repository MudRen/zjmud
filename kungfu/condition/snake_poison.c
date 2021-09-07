// snake_poison.c
// by jeeny

#include <ansi.h>

inherit F_CLEAN_UP;

int dispel(object me, object ob, int duration)
{
	int n;

	if (me != ob)
	{
		if (me->query_skill_mapped("finger") != "sun-finger" &&
		    me->query("max_neili") < 3500)
		{
			tell_object(ob, "�㷢��" + me->name() + "�������������������ڣ���" 
				    "��ֻ����ʹ��ʣ���ͷ����һ��������ĺ��顣\n"); 
			tell_object(me, "����ͼ����" + ob->name() + "���������ھ綾��"
				    "����" + ob->name() + "�������£���æס�֡�\n"); 
			return -1;
		}

	} else
	{
		tell_object(me, "����ͼ�˹��������߾޶�����������" 
				"��������˺���ѷε���ʹ����ôҲ���۲���������\n"); 
		return -1;
	}

	n = ob->query_condition("snake_poison") -
	    (int)me->query_skill("sun-finger", 1);

	if (n < 1)
	{
		ob->clear_condition("snake_poison");
		me->add("max_neili", -(2000 + random(1000)));
	} else
		ob->apply_condition("snake_poison", n);

	tell_object(me, "������һ��ָ�񹦣�����" + ob->name() + "�������ڵľ綾��\n");

	return 1;
}

int update_condition(object me, int duration)
{
	int limit;

	if(! living(me) &&
	   (me->query("qi") < 25 || me->query("jing") < 25))
	{
		me->set_temp("die_reason", "���߾綾����������������");
		me->die();
		return 0;
	} else
	{
		me->receive_wound("jing", 25 + random(25));
		me->receive_damage("jing", 25 + random(25));
		me->receive_wound("qi", 50 + random(50));
		me->receive_damage("qi", 50 + random(50));
		tell_object(me, HIG "���е�" HIR "���߾綾" HIG "�����ˣ�"NOR"\n" );
		message("vision", HIG + me->name() + "һ��ҡ�Σ�����"
				  "������"NOR"\n",
			environment(me), me);
	}
	return 1;
}
