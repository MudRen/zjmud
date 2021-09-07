#include <room.h>

inherit ROOM;

void create()
{
	set("short", "�����鷿");
	set("long", @LONG
�����������鷿��ȴû��һ���顣���������쳣�Ŀյ���ֻ����һ��
��Ƥ̫ʦ��(yi)��������Щ��̫������
LONG );

	set("exits", ([
		"east" : __DIR__"aofu_zoulang3",
	]));

	setup();
}

void init()
{
	add_action("do_move", "move");
}

int do_move(string arg)
{
	object me;

	if (arg != "yi")
		return notify_fail("ʲô��\n");

	me = this_player();
	if (query("exits/down"))
		return notify_fail("�����Ѿ��Ὺ�ˡ�\n");

	message_vision("$N������̫ʦ���Ƶ�һ�ߣ�ֻ������¶��"
		       "��һ��������ĳ��ڡ�\n", me);
	set("exits/down", __DIR__"aofu_mishi");
	remove_call_out("close");
	call_out("close", 10);
	return 1;
}

void close()
{
	message("vision", "һ���������̫ʦ�λ����Ľ��ܵ����ڵ�ס�ˡ�\n",
		this_object());
	delete("exits/down");
}
