// huxin-dan.c �������ĵ�

#include <ansi.h>

inherit ITEM;

void init()
{
	add_action("do_eat", "fuyong");
}

void create()
{
	set_name(HIR"�������ĵ�"NOR, ({"huxin dan"}));
	set_weight(50);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("long","һ��"+name()+"������һ�����Ƶ�"ZJURL("cmds:fuyong huxin dan")+ZJSIZE(20)+"����"NOR"ʥҩ����������������\n");
		set("value", 2000);
		set("unit", "��");
		set("numb", 99);
		set("no_put", 1);
		set("no_get", 1);
		set("no_drop", 1);
		set("no_give", 1);
		set("no_sell", 1);
		set("no_steal", 1);
		set("no_beg", 1);
	  }
   	setup();
}

int do_eat(string arg)
{
       int q, j;

       object me, ob;      
       me=this_player();
       ob=this_object();

	if (!arg || arg!="huxin dan")
		return notify_fail("��Ҫ��ʲô?\n");

	if(me->is_busy())
		return notify_fail("����æ���ء�\n");

	if (sizeof(filter_array(me->query_enemy(),(: userp :))))
		return notify_fail("���ں���Ҷ���ս��������ʹ���������ĵ���\n");

	if(me->query("combat_exp", 1) > 2000000) 
		return notify_fail("���Ѿ������ָ����ˣ��˵�ҩ�Ѿ�����ʧȥ�����ã�\n");

	if(me->query_condition("medicine") > 0 )
		  return notify_fail("���ϴε�ҩ������û���أ��Ȼ��ٳ԰ɡ�\n");

	if (me->query("eff_qi") >= (me->query("max_qi")+me->query_gain_qi()) 
	     && me->query("eff_jing") >= me->query("max_jing") 
	     && me->query("neili") >= me->query("max_neili"))
		return notify_fail("�����ڲ���Ҫ��"+name()+"��\n");

      if( ob->query("numb") > 0){      
		me->set("eff_qi", me->query("max_qi")+me->query_gain_qi());
		me->set("eff_jing", me->query("max_jing"));

		me->set("neili",me->query("max_neili")*2);
		me->set("jingli",me->query("max_jingli"));
		me->set("food", me->max_food_capacity());
		me->set("water", me->max_water_capacity());
		me->apply_condition("medicine", 5);
		message_vision(HIG"$N����һЩ"+name()+HIG"����ʱ����Ȭ����Ѫ��ӯ��"NOR"\n" , me);
		me->start_busy(2);
		ob->add("numb", -1);

	   if(ob->query("numb") < 1){
		write(""+name()+"�Ѿ����Ե�һ˿��ʣ�ˡ�\n");
		destruct(this_object()); 
	     }
	   else write(""+name()+"���ܼ���ʹ��"+ob->query("numb")+"�Ρ�\n");
   
		return 1;
	     }
	
}


