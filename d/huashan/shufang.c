//shufang.c

inherit ROOM;

#include <ansi.h>

void create()
{
	set("short","��ɽ�鷿");
	set("long",@LONG
�����ǻ�ɽ�ɵ��鷿����ǽ��һ����ܣ�����������߰����һ���
�飬�����������ɽѰ�£����ܾ�û�������鷿�ˣ�Ҫ��ɶ�鶼���鷳��
�Ҳ����������������ı��㱸��
LONG);
	set("exits",([
		"north" : __DIR__"garden",
	]));
	set("book_count", 1);
	setup();
}

void init()
{
	add_action("do_zhengli", "zhengli");
}

int do_zhengli()
{
	object ob, me=this_player();
	me->add("qi", -5);
	if ((query("book_count") > 0) && (random(5) == 3))
	{
		message_vision(HIY "$N" HIY "������������˺ð��죬��Ȼ��"
			       "��������﷢����һ���顣"NOR"\n",me);
		ob=new("/clone/book/sword_book2");
		ob->move(me);
		add("book_count", -1);
	} else
		message_vision(HIY "$N" HIY "������������˺ð��죬ɶ��û"
			       "�ҵ������ǰ�æ�ˡ�"NOR"\n",me);
	return 1;
}

void reset()
{
	::reset();
	set("book_count", 1);
}

