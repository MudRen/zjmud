// sleepbag.c
inherit ITEM;
protected void wakeup(object me,object where);
protected void del_sleeped(object me);
#include <ansi.h>
void create()
{
	set_name("����",({"sleepbag"}));
	set_weight(7000);
	set_max_encumbrance(8000);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("long",
			"һ�����񣬽�����ʿ������Ұ��˯���õġ�\n");
		set("unit","��");
		set("value", 1000);
	}
}
int is_container() { return 1; }
void init()
{
	if (environment()==this_player())
				add_action("do_sleep","sleep",1);
}
int do_sleep(string arg)
{
	int rnd;
	object me = this_player();
		object where = environment(me);
	if (arg) return 0;
		if( where->query("sleep_room") || where->query("freeze"))		 return 0;
	if( where->query("no_sleep_room"))  return 0;
		if ( me->query("family/family_name") == "ؤ��") return 0;
		if (me->is_busy())
			  { write("����һ������δ��ɣ�\n"); return 1;}
		if( me->is_fighting() )
			  { write("ս����˯��������ѽ��\n"); return 1;}
		if (me->query_temp("sleeped"))
			  { write("���˯��һ��, ��˯�������к�����! \n");return 1;}
	message_vision("$Nչ��һ���������˽�ȥ����һ��ͽ��������磡\n",me);
	rnd=random(100/me->query_con()+10);
	where->add_temp("sleeping_person", 1);
	me->set_temp("block_msg/all",1);
	me->set_temp("sleeped",1);
	me->disable_player("<��Ϣ��>");
	if ( rnd < 1 ) rnd = 0;
	call_out("wakeup", rnd + 10, me, where);
	return 1;
}
protected void wakeup(object me,object where)
{
		while( environment(me)->is_character() )
				me->move(environment(environment(me)));
		me->enable_player();
	me->set_temp("block_msg/all",1);
	me->move(environment(me));
		me->delete_temp("block_msg");
	if ( userp(me) && (!me->query("food") || !me->query("water")) ){
				message("vision",me->name()+"һ��������������������ģ�û�а�㾫��\n",environment(me),({me}));
				write("��һ��������������������ģ�û�а�㾫�񡣿�����Ҫȥ�ҵ�Ե��ˣ�\n");
		}else{
				message("vision",me->name()+"һ����������������ػ��һ�½�ǡ�\n",environment(me),({me}));
				write("��һ��������ֻ���������档�ûһ���ˡ�\n");
				me->set("qi",	me->query("eff_qi"));
				me->set("jing",  me->query("eff_jing"));
		}  
		 call_out("del_sleeped",10+random(5),me);
	if (where)
				where->add_temp("sleeping_person", -1);
		me->delete("no_get");   
		me->delete("no_get_from");	  
 
}
protected void del_sleeped(object me)
{
		if (objectp(me))
				me->delete_temp("sleeped");
}

