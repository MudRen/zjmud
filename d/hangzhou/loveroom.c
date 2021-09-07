// loveroom.c ��Լ��

#include <ansi.h>
#include <room.h>

inherit ROOM;

varargs static void create_food(string nmstr, string* idlist, string longstr)
{
	object obj;

	obj = new("/d/city/obj/food");
	obj->set_name(nmstr, idlist);
	if (longstr)
	      obj->set("long", longstr);
	else
	      obj->set("long", "һ����������, �������"+nmstr+"��\n");
	obj->move(this_object());
}

varargs static void create_water(string nmstr, string* idlist, string cup, string longstr)
{
	object obj;

	obj = new("/d/city/obj/water");
	obj->set_name(cup, idlist);
	if (longstr)
	      obj->set("long", longstr);
	else
	      obj->set("long", "һ���ɿڵ�" + nmstr + "��\n");
	obj->set("liquid/name", nmstr);
	obj->move(this_object());
}

varargs static void create_wine(string nmstr, string* idlist, string cup, string longstr)
{
	object obj;

	obj = new("/d/city/obj/wine");
	obj->set_name(cup, idlist);
	if (longstr)
		obj->set("long", longstr);
	else
		obj->set("long", "һ��������" + nmstr + "��\n");
	obj->set("liquid/name", nmstr);
	obj->move(this_object());
}

void create()
{
	set("short", "��Լ��");
	set("long", @LONG
¥��¥����Լ��������ͨ����������棬������ů��Զ���յ�һ
�ߣ�ӳ������������ɽ��ѹ�̣����֣�������Ŷ������أ�������ɴ��
��ݺ���䡣�����׵̺�ب���ϣ������������أ����ݺ�����һ�α̳�
ƮȻ���档����һ�ž��ɵ�С��������һֽ���µĲ˵�(menu)��
LONG);
	set("exits", ([
	    "down" : __DIR__"jiulou",
	]));
	set("sleep_room", 1);
	set("item_desc", ([
	    "menu": @TEXT
	order party :   Ũ���Ļ�    (200������)

	order end   :   ������

	close door  :   �رշ���

	open door   :   �򿪷���
TEXT
	]) );
	set("no_clean_up", 0);
	setup();
	set("no_user", 1);
}

void init()
{
	object me;

	add_action("do_order", "order");
	add_action("do_close","close");
	add_action("do_open","open");
	if (query("order_owner"))
	{
		me = this_player();
		me->set("food", me->query("food") / 2);
		me->set("water", me->query("water") / 2);
	}
}

int do_order(string arg)
{
	object me, env;
	object* oblist;
	string mesg;
	int idx;

	me = this_player();
	env = this_object();
	mesg = query("order_owner");

	if (mesg && (arg == "end") && (mesg == me->query("id")))
	{
		delete_temp("plugin");
		delete("order_owner");
		delete("order_type");
		oblist = all_inventory(env);
		for(idx = 0; idx < sizeof(oblist); idx++)
		{
			if (! objectp(oblist[idx]))
				continue;
			if (userp(oblist[idx]))
				continue;
			destruct(oblist[idx]);
		}
		message_vision("$N" NOR "������üͷ���Ѿ��糷ȥ�ˡ�\n", me);
		CHANNEL_D->do_channel(this_object(), "rumor",
			   me->name() + "���Ļ����ڽ����ˡ�");
		return 1;
	}

	if (mesg)
		return notify_fail("�����Ѿ����˰����ˡ�\n");

	if (arg == "party")
	{
		mesg = "��˵" + me->name() + "�ں���¥��¥�����Ļᡣ";
		if (! me->can_afford(20000))
			return notify_fail("��û���㹻��Ǯ����Ǯ������\n");;

		me->pay_money(20000);
		create_water(CYN "������" NOR, ({ "tea" }), MAG "��ɰ����" NOR);
		create_water(HIG "���ݴ�" NOR, ({ "tea" }), MAG "��ɰյ" NOR);
		create_wine(HIY "���˻ƾ�" NOR, ({ "wine" }), HIW "������"NOR);
		create_wine(GRN "��Ҷ��" NOR, ({ "wine" }), HIG "��䱭"NOR);
		create_wine(RED "Ů����" NOR, ({ "wine" }), MAG "��̴��"NOR);
		create_food(RED "������" NOR, ({ "pork" }));
		create_food(HIB "��������" NOR, ({ "fish" }));
		create_food(HIR "����Ϻ��" NOR, ({ "shrimp" }));
		create_food(YEL "�л�ͯ��" NOR, ({ "chicken" }));
		create_food(HIR "��������" NOR, ({ "guihua geng" }));
		create_food(HIY "�ٹ��Ͱ�" NOR, ({ "baozi" }));

		message_vision("$N" NOR "΢΢һЦ���ڳ���һϯ���硣\n", me);
		CHANNEL_D->do_channel(this_object(), "rumor", mesg);
		set("order_owner", me->query("id"));
		set("order_type", arg);
		return 1;
	}
	else
		return notify_fail("���ֻ�а��Ļ�С�硣\n");
}

int do_close(string arg)
{
	object me = this_player();
	object room;

	if (arg != "door")
		return notify_fail("��Ҫ��ʲô��\n");

	if (! query("exits/down"))
		return notify_fail("�Ų��ǹ��ŵ�ô��\n");

	me->set_temp("plugin", 1);

	room = get_object(query("exits/down"));
	message_vision("$N�ٺ�ɵЦ���������İ��Ÿ������ˡ�\n", me);
	tell_room(room, "ֻ���������һ�������Ŵ����淴���ˡ�\n");

	delete("exits/down");
	room->delete("exits/up");
	return 1;
}

int do_open(string arg)
{
	object me = this_player();
	object room;

	if (arg != "door")
		return notify_fail("��Ҫ��ʲô��\n");

	if (query("exits/down"))
		return notify_fail("�Ų��ǿ��ŵ�ô��\n");
	
	set("exits/down", __DIR__ "jiulou");
	room = get_object(query("exits/down"));
	room->set("exits/up", __FILE__);

	message_vision("$N̾�˿�����������Ÿ����ˡ�\n", me);
	tell_room(room, "ֻ���������Ǹ���һ�����ſ��ˡ�\n");

	me->delete_temp("plugin", 1);
	return 1;
}

int valid_leave(object me, string dir)
{
	if (me->query("id") != query("order_owner"))
		return 1;

	return notify_fail("������ order end ���������ߡ�\n");
}

