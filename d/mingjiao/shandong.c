// Room: /d/mingjiao/shandong.c
// Date: Java 97/04/9

#include <ansi.h>
inherit ROOM;

void create()
{
	set("short", "�����ܶ�");
	set("long", @LONG
������һ��СС��������Χ�ں����ĺ��ѿ����������ԼԼ����
�Կ���һ�ȴ�ʯ��(men)��
LONG );
	set("exits", ([
		"out"  : __DIR__"huangtulu2",
	]));
	set("item_desc", ([
		"men"  : "һ�ȴ�ʯ�ţ���������������ذɡ�\n",
	]));
	set("outdoors", "mingjiao");
	setup();
}

void init()
{
	add_action("do_break", "break");
}

int do_break(string arg)
{
	object *ob, me = this_player();
	int i;

	if (arg != "men")
		return notify_fail("���ڸ���? \n");

	if (me->query("neili") < 2000)
	{
		write("�����������������Լ����ڵ��������á�\n");
		return 1;
	}

	me->add("neili", -2000);
	if (me->query_skill("force", 1) < 300)
	{
		message_vision(CYN "$N" CYN "ѽѽ�ٺٷ��˰������������"
		   	       "ûʲô������\n", me);
		tell_object(me, "�������Լ����ڹ���򻹲�����\n");
		return 1;
	}

	message_vision(CYN "ʯ����$N" CYN "һ��֮���������죬�����ƿ���"NOR"\n",
		       me);

	set("exits/enter",__DIR__"midao0");
	me->add("neili", -400);
	remove_call_out("close");
	call_out("close", 5, this_object());
	return 1;
}

void close(object room)
{
	message("vision", "ʯ�������������죬�������ϡ�"NOR"\n", room);
	room->delete("exits/enter");
}

