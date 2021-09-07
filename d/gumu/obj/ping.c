// ping.c �佬ƿ
// ��������ʹ������֮������ʹ���
// By Lgg,1998.9

#include <ansi.h>

inherit ITEM;

void init()
{
	add_action("do_qufeng","qufeng");
}

void create()
{
	set_name("�佬ƿ", ({ "fengjiang ping", "ping" }) );
	set_weight(4500);
	if( clonep() )
		set_default_object(__FILE__);
	else {
	set("unit", "��");
	set("value", 0);
	set("jian",5) ;
	set("material", "��");
	set("long", "����һ�����Ϲ������ɵ�Сƿ����δ�ο�ƿ�����Ϳ����ŵ�\n"
		    "һ��Ũ������ζ�������������䡣\n") ;
	}
	setup();
}

int do_qufeng(string arg)
{
	object me, obj;
	int myexp , objexp ;
	int mylev , objlev ;
	int myforce , obforce ;
	int steps ;

	me = this_player();
	if (environment(me)->query("no_fight"))
		return notify_fail("�����ֹս����\n");

	if (! arg)
		return notify_fail("�������乥��˭��\n");

	if (this_object()->query("jian") < 1)
		return notify_fail("Сƿ���������Ѿ����ù��ˡ�\n");

	if (! objectp(obj = present(arg, environment(me))))
		return notify_fail("����û������ˡ�\n");

	if (! obj->is_character() || obj->is_corpse())
		return notify_fail("�����һ�㣬�ǲ����ǻ��\n");

	if (me->is_busy())
		return notify_fail("��������æ��û��ʱ�����䡣\n");

	if (obj == me)
		return notify_fail("��䲻�ܹ����㡣\n");

	if (! me->is_fighting(obj))
		return notify_fail("����ֻ����ս���жԶ���ʹ�á�\n");

	myexp =  me->query ("combat_exp" );
	objexp = obj->query ("combat_exp" );
	mylev =  me->query_skill("qufeng" );
	objlev = obj->query_skill("qufeng" );
	myforce =  me->query_skill("force" );
	obforce = obj->query_skill("force" );

	if (mylev <= 0)
		return notify_fail("�㲻������֮����������ʹ���Ϊ�㹥�����ˣ�\n");

	myexp = 30 * objexp / myexp ;
	if (myexp < 30) myexp = 30 ;

	if ((int) me->query("jing") < myexp)
		return notify_fail("��ľ���������������˵У�\n");

	if (myforce + 15 <= obforce)
		return notify_fail("���ֵ��ڹ�̫����ˣ������������������ã�\n");

	this_object()->add("jian", -1);
	steps = (mylev - objlev) / 10;
	if (steps < 2) steps = 2 ;
	if (steps > 6) steps = 6 ;
	message_vision(HIY "$N" HIY "�ο���ƿ����������ƿǱ��������ʹ"
		       "��ƿ�е�����ԶԶƮ�˿�ȥ��\nͻȻ����֮��������"
		       "��֪�����������һ��Ⱥ��䣬��$n" HIY "Χ�˹�ȥ��"NOR"\n",
		       me, obj);
	me->start_busy(3);

	if (random(mylev) < objlev * 2 / 3)
		message_vision(YEL "��$n" YEL "�鴽һХ������ƺ���"
			       "���˺��ԶԶ���˿�ȥ��"NOR"\n", me, obj);
	else
	{
		tell_object(obj, HIR "����Χɲ�Ǽ価�����Χ�ƣ�һֻֻ��亷��η��������\n"
				 "���˹�������ֻ���ñ���΢΢һʹ���ѱ�������У�"NOR"\n"  ) ;
		obj->receive_damage("jing", steps * 5, me);
		obj->receive_damage("qi", steps * 6, me);
		if (! obj->is_busy()) obj->start_busy(3);
		me->start_busy(1);
	}
	me->receive_damage("jing", myexp);
	return 1;
}

