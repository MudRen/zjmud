// xiang.c
#include <ansi.h>
inherit ITEM;
void init()
{
	add_action("do_array","array");
}

void create()
{
	set_name("������", ({ "buzhen xiang", "xiang" }) );
    	set_weight(4000);
	if( clonep() )
		set_default_object(__FILE__);
	else {
	set("unit", "��");
		set("value", 0);
	set("jian",5) ;
		set("material", "steel");
	set("long", "�����һ�������ר�õĵ��ߣ��������䡹�������и��ָ�����\n"
		    "���ߣ�������������\n") ;
	}
	setup();
}

int do_array(string arg)
{
    	object me, obj;
    	int myexp, objexp ;
    	int mylev, objlev ;
    	int steps;

    	me = this_player();

    	if (! arg)
		return notify_fail("�����˭����\n");

    	if (environment(me)->query("no_fight"))
       		return notify_fail("�����ﲻ�ܹ������ˡ�\n");

	if (me->is_busy())
		return notify_fail("��������æ��\n");

    	if (this_object()->query("jian") < 1)
		return notify_fail("������ĵ����Ѿ��ù��ˡ�\n");

	if (! objectp(obj = present(arg, environment(me))))
		return notify_fail("����û������ˡ�\n");

	if (! obj->is_character() || obj->is_corpse() ||
	    obj->query("not_living"))
		return notify_fail("�����һ�㣬�ǲ����ǻ��\n");

	if (obj == me)
		return notify_fail("������ɱ�� :P\n");

	if (obj->is_busy())
		return notify_fail(obj->name() + "������æ���أ�����Ĵ󵨵Ľ����ɣ�\n");

    	myexp =  me->query("combat_exp");
    	objexp = obj->query("combat_exp");
    	mylev =  me->query_skill("qimen-wuxing", 1);
    	objlev = obj->query_skill("qimen-wuxing", 1);

    	if (mylev < 100)
		return notify_fail("�㲻��ͨ��������֮�������ܲ���\n");

    	if (myexp < 1) myexp = 1;
    	myexp = 30 * (objexp + 10000) / (myexp + 10000);
    	if (myexp < 30) myexp = 30;

    	if ((int)me->query("jing") < myexp)
		return notify_fail("��ľ������ˣ�\n");

    	add("jian", -1);
    	steps = (mylev - objlev) / 10;
    	if (steps < 2) steps = 2;
    	if (steps > 8) steps = 8;
    	message_vision(HIY "$N�������䣬��$n��ΧѸ�ٰ���ʲô����......��\n" 
		   "��$n�ѹ�����ȴ�����Լ��������У��������ã�"NOR"\n",
		   me, obj);
    	me->start_busy(3);
	me->want_kill(obj);
	obj->kill_ob(me);
	me->fight_ob(obj);

    	if (random (mylev) < objlev / 2)
      		message_vision("��$n�ܿ��ʶ����$N���󷨣�����"
			       "���������\n" , me, obj);
    	else
      	{
	 	tell_object(obj, HIR "\n���в��ϻó����ָ����Ĺ��ޣ�һ��"
				 "��������צ\n������������ֻ�ܼ���������"
				 "�����ಫ��"NOR"\n");
	 	obj->receive_damage("jing", steps * 10, me);
	 	obj->start_busy(1 + random(steps));
      	}
    	me->receive_damage("jing", myexp);
    	return 1;
}
