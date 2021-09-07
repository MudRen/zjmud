inherit ROOM;
#include <ansi.h>
#include <room.h>

void create()
{
	set("short", "�����ɾ�");
	 set("long", @LONG
�·�֮���ƺ�Ʈ�죬�������ƣ�ʱ��΢��ϴ�档�����续����·���
����������Դ��
LONG    );

	set("valid_startroom",1);
	set("sleep_room", 1);
	set("close_room", 1);
	set("no_fight", 1);
	set("exits", ([
		"north": "/u/sxjian/liangong",
		"east": "/d/wizard/guest_room"
	]));
	setup();
}

void init()
{
	object ob, me; 
	string room;

	ob = this_player();

	if (objectp(ob) && userp(ob)
	&& !ob->query_temp("workroom/sxjian")
	&& ob->query("id") != "sxjian")
	{
		if (objectp(me=present("leave",this_object())))
			tell_object(me, ob->name() + "��ͼ����"HIY"�����ɾ�"NOR"ʧ�ܡ�\n");
		if (environment(ob) && environment(ob) != this_object()
		&&  stringp(room = base_name(environment(ob)))) {
			tell_object(ob, HIY "\n��û�еõ����˵����룬�޷���ý��������ɾ���;����"NOR"\n"
					    "\n��ֻ���ֻص���" + environment(ob)->query("short") + "��\n");
			ob->move(room);
			return;
		} else {
			tell_object(ob, HIY "\n��û�еõ����˵����룬�޷���ý��������ɾ���;����"NOR"\n"
					    "\n��ֻ��ѭ����Ϥ��;���������ݿ�ջ��"NOR"\n");
			ob->move("/d/city/kedian");
			return;
		}
	}

	if (objectp(me=present("sxjian",this_object())) && objectp(ob) && me != ob
	&&  ob->query("id")!="sxjian" && living(ob))
			tell_object(me, ob->name() + "������"HIW"�����ɾ�"NOR"��\n");

	add_action("do_move", "move");
	add_action("do_look", ({ "look", "l" }));
	add_action("do_kick", ({ "kick", "ti" }));
	add_action("do_yaoqing", ({ "yaoqing", "qing" }));
	add_action("do_action", "");
}

int do_move(string arg)
{
	object me=this_player();

	if (! arg || arg=="") return 0;

       if (me->query("id") != "sxjian" && !me->query_temp("workroom/sxjian"))
		return notify_fail("˵��������˵�߾��ߣ�����Ϊ�ɵ����㣿\n");

	if (arg=="down") 
	{
		message_vision(HIW "����ͻȻ�ѿ�һ�����ӣ�$Nһ���ӵ��˽�ȥ��"NOR"\n", me);
			me->move("/d/city/kedian");
		message("vision", HIW "����ͻȻ�ѿ�һ�����ӣ�ͻȻ�������������" + me->name() +
				  HIW ""NOR"\n", environment(me), me);
		return 1;
	}

	if( arg=="up") 
	{
		message_vision(HIY "�����ͻȻ����һ��������$Nһ������ʧ��ҫ�۵�ǿ���С�"NOR"\n", me);
		me->move("/d/wizard/guest_room.c");
		message("vision", GRN "����ͻȻ����һ�����ӣ�ͻȻ������ð������" + me->name() +
				  GRN ""NOR"\n", environment(me), me);
		return 1;
	}

	if (arg == me->query("id"))
	{
		message("vision",me->name() + "�ƿ���֪�δ���һ��С�����˳�ȥ��\n", environment(me), ({me}) );
		if (me->query("id") != "sxjian") {
			if (load_object("/u/"+me->query("id")+"/workroom")) {
				me->move("/u/"+me->query("id")+"/workroom");
				message("vision", me->name() + "�ƿ�С�Żص����Լ��ļ��С�\n",
				environment(me), ({me}) );
			} else {
			      me->move("/d/city/kedian");
				message("vision", me->name() + "�ƿ�С��������ջ��\n",
				environment(me), ({me}) );
			}
		} else {
			me->move("/d/city/kedian");
			if (! me->query("env/invisibility"))
			message("vision", me->name() + "�ƿ�С��������ջ��\n",
			environment(me), ({me}) );
		}
		return 1;
	}
	return notify_fail("�� type move ("+me->query("id")+")��\n");
}

int do_look()
{
	object me = this_player();
	mixed *local;
	local = localtime(time() * 60);
	if(local[2] < 4 || local[2] >= 21) {
	write(BLU"���ܺ�����һƬ���������ֳ�һ�㡢�������ɫ�����⣬��������Խ"
	     "��Խ�࣬ת�۱㲼���������䣬�е�����өƮ�ɣ��е��緱����˸��"NOR"\n", me);
	}
	if(local[2] >= 4 && local[2] < 8)  {
	write(HIR"�����Ǹո�����һ����΢�׵Ĺ��ڶ����Ʋ����֣�һ�ֺ����е���"
	     "������ǧ�����ʱ�ڲ���ӳ���³��ֳ�����������"NOR"\n", me);
	}
	if(local[2] >= 8 && local[2] <= 13) {
	write(HIC"������ˣ��ƺƵ�����������Ұ��Զ����ʡ��ƺ��ᵴʱ����ֻ����"
	     "��̤���ƣ�����ƮƮ����֮�С�������Ѹ��ӿ��ʱ��ֻ���ú�����棬��"
	     "���г�������֮�⡣"NOR"\n", me);
	}
	if(local[2] > 13 && local[2] < 14) {
	write(YEL"�����羲���ƺ�ƽ�̣������Լ��������â���䣬���˷����֮��ͷ"
	      "ӡ��һ��Ѥ���Ĳʺ磬���ƺ������Լ�����Ӱ�����س���������ϡ�"NOR"\n", me);
	}
	if(local[2] >= 14 && local[2] < 21) {
	write(HIY"������ˣ��ƺƵ�����������Ұ��Զ����ʡ�ʱ��������ӿ�������"
	     "����ɳ��ʱ���ع��񾲣�����һƬ���֮�С�"NOR"\n", me);
	}
}


int do_action(string arg)
{
	object me,*ob,ob1;
	int i;
	me = this_player();
	ob = all_inventory(environment(me));

	if (me && me->query("id") != "sxjian" && !me->query_temp("workroom/sxjian"))
	{
		string action = query_verb();
		switch (action) {
			case "set":
			case "steal":
			case "force":
			case "slap":
			case "dest":
			case "call":
			case "full":
			case "pk":
			case "kickout":
			case "vs":
			case "clone":
			case "more":
			case "home":
			case "get":
			case "call":
			case "qiangpo":
			case "hit":
			case "kill":
			case "fight":
			case "da":
			case "club":
			case "kiss":
			case "jyin":
			case "mo":
			case "18mo":
			case "rumor":
			case "rumor*":
			case "chat*":
			case "reply":
			case "sos":
			case "sys":
			case "drop":
			case "use":
			case "smash":
			case "copy":
			case "summon":
			write(HIM"��������...��"NOR"\n");
			return 1;
		}
	}
	if (arg != "")
	{
		for(i=0; i<sizeof(ob); i++)
		{
			ob1 = query_snoop(ob[i]);
			if (! living(ob[i]) ) continue;
			if (objectp(ob1) && (ob[i]->query("id") == "sxjian"
			|| ob[i]->query_temp("workroom/leave")) && ob1->query("id")!= "sxjian")
			{
				snoop(ob1);
				tell_object(ob[i], HIW + ob1->name(1) + HIW "�������������ֹ��"NOR"\n");
				break;
			}
		}
	}
	return 0;
}

int do_kick(string arg)
{
	object me = this_player();
	object ob;

	if (! arg) return notify_fail("��Ҫ��ʲô��\n");

	if (me->query("id")!="sxjian")
		return notify_fail("�ڱ��˵ĵ���,��Ƿ��ѽ�� \n");

	if (!(ob=present(arg,environment(me)))) return notify_fail("��Ҫ�ߵ��˲������\n");

	if (ob==me) return notify_fail("��Ҫ���Լ���������....\n");

	if (ob->query("id") == "sxjian") return notify_fail("���������������ġ�\n");

	message_vision(CYN "$N����һ�ţ���������$n��ƨ���ϡ�"NOR"\n", me, ob);
	tell_room(environment(ob), ob->name() + "Ƥ���Ƶĵ�������ɽ�¹�ȥ��\n", ob);
			ob->move("/d/city/kedian");
	tell_room(environment(ob), "ֻ������д���ɱ���Ƶ�һ���Һ���\n", ({me, ob}));
	tell_room(environment(ob), ob->name() + "����һ����ʯ���Ӱ���е���������\n", ({me, ob}));
	tell_object(ob, me->name() + "����һ������ɽ����\n");
	ob->delete_temp("workroom/leave");
	       return 1;
}

int do_yaoqing(string arg)
{

	object target, me, ob;
	me = this_player();
     
	if (! arg || ! interactive(target = find_player(arg)))
		return notify_fail("��... ���������\n");
	if (target == me->query("id") && me->query("id")!="sxjian")
		return notify_fail("����ô�������Լ��أ�\n");
	if (target->query_temp("workroom/sxjian"))
		return notify_fail("���Ѿ�������ˣ�\n");
       if (me->query("id") != "sxjian" && !me->query_temp("workroom/sxjian"))
		return notify_fail("����ɲ�����ĵ��̣�Ƿ�Ⱑ��\n");
	if (environment(target) == environment(me) && me->query("id")!="sxjian")
		return notify_fail(target->name() + "��������ߡ�\n");
	message("vision", me->name() + "����һ�һֻ�Ÿ���˳�ȥ��\n",environment(me), ({me}) );
	tell_object(me, HIY "���������" + target->name() + HIY "ȥ�������ͣ�"NOR"\n");
	tell_object(target, HIY "ͻȻ�䣬һ�ű��������뺯Ʈ�������ǰ��ֻ���������ţ�"NOR"\n"
				WHT "����������������������������������������������������������\n"
				"�� " + WHT + target->query("name") + WHT"���£�			    "WHT"\n"
				"��    ���������ӣ�ϧ��Եʶ��					 "WHT"\n"
				"��    �����ر�����Ů���죬�����ݹ���			       "WHT"\n"
				"��    Ը����۾�������ܣ�һ����				   "WHT"\n"
				"��		    "+me->query("title")+"��"CYN+me->query("name")+WHT"     \n"
				"����������������������������������������������������������"NOR"\n");
	target->set_temp("workroom/sxjian", 1);

	return 1;
}
