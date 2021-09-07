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

	if ((int)me->query_temp("caiyao") < 1)
		return notify_fail("�������˷�ʱ���ˣ����߰ɡ�\n");

	if (arg != "yao" && arg != "caoyao")
		return notify_fail("��Ҫ��ʲô��\n");

	if (me->is_busy()) {
	call_out("cai", 3 + random(5), me);
	return 1;
        }
       
	if ((int)me->query("jing") < 40)
		return notify_fail("��̫ƣ���ˣ���Ϣһ�°ɡ�\n");

	if ((int)me->query("qi") < 40)
		return notify_fail("��̫���ˣ���Ϣһ�°ɡ�\n");

	if ((int)me->query_temp("caiyao") == 2) {
		tell_object(me,"��ʱ���ҩ���ˡ�\n");
		me->move("/d/beijing/huichuntang");
		tell_object(me,ZJFORCECMD("e")+ZJFORCECMD("give cao yao to xiao tong"));
		return 1;
	}

	message_vision("$Nſ�ڵ��ϣ��ɴ����۾��ڲݴ�����Ѱ��ҩ�ݣ�����©����Ŀ�ꡣ\n", me);
	call_out("cai", 4 + random(5), me);
	me->start_busy(2);
	return 1;
}
 
int cai(object me)
{ 
	object ob;
	object ob1;

	if (! objectp(me) ||  ! living(me) )
		return 0;

	if ( present("du she", this_object()) || present("du langzhong", this_object()) || me->is_fighting() || environment(me) != this_object() ) {
		call_out("cai", 5 + random(5), me);
		return 1;
	}

	if (random(10) < 4 )
	{
		me->receive_damage("jing", 10 + random(20));
		me->receive_damage("qi", 10 + random(20));
		message_vision(CYN "һ�������󣬲ݴ����ƺ�û��$NҪ�ҵĶ�����$Nʧ����̾�˿�����"NOR"\n"
					"$N����ſ�ڵ��ϣ��ɴ����۾��ڲݴ�����Ѱ��ҩ�ݣ�����©����Ŀ�ꡣ"NOR"\n", me);
		call_out("cai", 5 + random(5), me);
		return 1;
	}

	if (random(10) > 8)
	{	 
		tell_room(environment(me), HIR "�ݴ���һ��ζ���ͻȻ���һ�����ߡ�"NOR"\n");
		ob = new("/d/beijing/npc/liandan_dushe");
		ob->move(this_object());
		ob->kill_ob(me);
		me->kill_ob(ob);
		call_out("cai", 5 + random(5), me);
		return 1;
	} 
	else if (random(10)>8) {	 
		tell_room(environment(me), HIR "���Ӻ���ͻȻ����һ�������ɲ�����ӣ�����һ�Ѷ̵�����������"NOR"\n");
		ob = new("/d/beijing/npc/liandan_langzhong");
		ob->move(this_object());
		ob->kill_ob(me);
		me->kill_ob(ob);
		call_out("cai", 5 + random(5), me);
		return 1;
	} 
	else { 
		ob1 = new("/d/beijing/npc/dan/caoyao");
		ob1->move(me, 1);
		me->receive_damage("jing", 10 + random(20));
		me->receive_damage("qi", 10 + random(20));
		me->set_temp("caiyao", 2);
		message_sort(HIG "$N" HIG"���˰��죬���ڷ�������һ������������Ĳ����в�ͬ��С������ؽ������˳�����"NOR"\n", me); 
		tell_object(me,"��ʱ���ҩ���ˡ�\n");
		me->move("/d/beijing/huichuntang");
		tell_object(me,ZJFORCECMD("e")+ZJFORCECMD("give cao yao to xiao tong"));
	}
	return 1;
}

