// flower_poison.c

#include <ansi.h>

int dispel(object me, object ob)
{
	if (me == ob)
	{
		tell_object(me, "����ͼ�˹�����ϳ�������ͻȻһ�е�"
				"��˺���ѷε���ʹ���������ʡ�\n");
		return -1;
	}

	tell_object(me, "�㽫��������" + ob->name() + "���У�ȴ����"
			"������ת�쳣���죬������⣬\nͻȻ��" + ob->name() +
			"�������£���æס�֡�\n");
	tell_object(ob, "�����" + me->name() + "�����������������"
			"��������Ȼһ��˺���ѷεľ�ʹ��\n��ʤ�ϳ���"
			"��������ʱ�����㼸�����ʡ�\n");
	return -1;
}

int update_condition(object me, int duration)
{
	if(me->query_temp("nopoison")) return 0;

	message("vision", HIG + me->name() + "һ��ҡ�Σ�����"
			  "������"NOR"\n",
		environment(me), me);

	if(! living(me) &&
	   (me->query("qi") < 25 || me->query("jing") < 25))
	{
      		me->set_temp("die_reason", "�ϳ���������������������");
      		me->die();
      		return 0;
	}

	me->receive_wound("jing", 25 + random(25));
	me->receive_damage("jing", 25 + random(25));
	me->receive_wound("qi", 50 + random(50));
	me->receive_damage("qi", 50 + random(50));
	if (me->query_skill("force") >= 300)
		me->apply_condition("flower_poison", duration - 1);
	tell_object(me, HIG "���е�" HIR "�ϳ�����" HIG "�����ˣ�"NOR"\n" );
	if( duration < 1 )
	{
		tell_object(me, HIR "���Ŀ�һ���ʹ������һ����ѣ����"
			    "��о�ȴ����һЩ��"NOR"\n");
		return 0;
	}
	return 1;
}

