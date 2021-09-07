// inherit object: liandan_lin.c

#include <ansi.h> 

inherit ROOM;

int do_cai(string arg);

void init()
{
	add_action("do_cai","cai");
	set("item_desc", ([
		"����ҩ��" : "������������һ��С�ݣ��߽�һ��ȴ����Щ��ͬѰ����\n"
		ZJOBACTS2"��ҩ:cai yao\n",
	]));
}

int do_cai(string arg)
{
	object me = this_player();
	object ob;
	object ob1;

	if (query("last_cai")&&(time()-query("last_cai"))<30)
		return notify_fail("��ҩ�����У�"+(query("last_cai")+30-time())+"����֮����졣\n");

	if (arg != "yao" && arg != "caoyao")
		return notify_fail("��Ҫ��ʲô��\n");

	if (me->query("combat_exp")<1000000)
		return notify_fail("�㻹��������Լ���ʵս����������ҩ�ɣ�\n");

	if (me->is_busy()||me->is_fighting()||me->query_temp("cai_yao"))
		return notify_fail("����æ���أ�æ����˵�ɣ�\n");
       
	if (query_temp("cai_user"))
		return notify_fail(query_temp("cai_user")->query("name")+"���ڲɼ��ء�\n");

	if ((int)me->query("jing") < 40)
		return notify_fail("��̫ƣ���ˣ���Ϣһ�°ɡ�\n");

	if ((int)me->query("qi") < 40)
		return notify_fail("��̫���ˣ���Ϣһ�°ɡ�\n");

	message_vision("$Nſ�ڵ��ϣ��ɴ����۾��ڲݴ���С������ο�ʼ��ժ��ҩ��\n", me);
	me->set_temp("cai_yao",10);
	set_temp("cai_user",me);
	call_out("cai", 1, me);
	return 1;
}

int cai(object me)
{ 
	object ob;
	object ob1;
      int exp,pot;

	if (present(me->query("id"),this_object())) 
		delete_temp("cai_user");

	if (! objectp(me) ||  ! living(me) ) {
		delete_temp("cai_user");
		return 0;
	}

	if ( present("du she", this_object()) || present("du langzhong", this_object()) || me->is_fighting() || environment(me) != this_object() ) {
		me->delete_temp("cai_yao");
		delete_temp("cai_user");
		tell_object(me,HIM"�ɼ�����ϣ�"NOR"\n");
		return 1;
	}

	if(me->query_temp("cai_yao")>0)
	{
		me->receive_damage("jing", 5);
		me->receive_damage("qi", 5);
		me->add_temp("cai_yao",-1);
		message_vision(HIY"$N"NOR"�ɼ���ҩ�У�"HIG+repeat_string("��",10-me->query_temp("cai_yao"))+repeat_string("��",me->query_temp("cai_yao"))+NOR"\n",me);
		call_out("cai", 1, me);
	}
	else
	{
		message_sort(HIG "$N" HIG"С���������ڽ���ҩ���˳�����"NOR"\n", me);
            exp=20+random(11);
		me->add("combat_exp", exp);
		pot=me->improve_potential(exp-random(10));
		tell_object(me,  "������һ�겻֪����ҩ��"NOR"\n" );
		tell_object(me,  "������" + chinese_number(exp) +	"�㾭���" + chinese_number(pot) + "��Ǳ�ܡ�"NOR"\n" );
		ob1 = new("/d/beijing/npc/dan/caoyao");
		ob1->move(me, 1);
		me->delete_temp("cai_yao");
		delete_temp("cai_user");
		set("last_cai",time());
		return 1;
	}

	if (random(100) > 98)
	{	 
		tell_room(environment(me), HIR "�ݴ���һ��ζ���ͻȻ���һ�����ߡ�"NOR"\n");
		ob = new("/d/beijing/npc/liandan_dushe");
		ob->move(this_object());
		ob->kill_ob(me);
		me->kill_ob(ob);
	}
	else if (random(100)>98)
	{	 
		tell_room(environment(me), HIR "���Ӻ���ͻȻ����һ�������ɲ�����ӣ�����һ�Ѷ̵�����������"NOR"\n");
		ob = new("/d/beijing/npc/liandan_langzhong");
		ob->move(this_object());
		ob->kill_ob(me);
		me->kill_ob(ob);
	} 
	return 1;
}

