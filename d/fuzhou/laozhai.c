// room: laozhai.c
// Jay 4/8/96
#include <room.h>
#include <ansi.h>

inherit ROOM;
int do_break(string arg);

void create()
{
	set("short", "������լ");
	set("long", @LONG
�����Ǹ����ھ�����ͷ�������ڸ����ľɾӡ����ڵļҾߺ�����
�˵ص��ڵ��ϡ������һ�ǽ���һ��֩���������ﵽ���ǳ�������Ȼ
���Ѿ��ܾ�û����ס�ˡ�����ľ�ͷ��һ����(men)�� ���ѱ�̮����
ש�ߵ�ס�ˡ�
LONG );

	set("exits", ([
		"south" : __DIR__"xiangyang",
	]));
	set("objects", ([
		"/d/songshan/npc/bo": 1,
	]));

	set("item_desc", ([
		"men" : "�������ѱ���ס�޷�ͨ�У����������(break)����\n",
	]));
	setup();
}

void init()
{
	add_action("do_break", "break");
}

int do_break(string arg)
{
	int n;

	n = this_player()->query("neili");
	if (! arg || arg != "men")
	{
		write("��Ҫ��������˵Ķ�����\n");
		return 1;
	}

	message_vision("$N�ߵ�����ǰ���ݳ��������ʽ������һ��"
		       "����˫��ͬʱ�ĳ���\n", this_player());
	if (n >= 500)
	{
		message_vision("$Nֻ��һ�����죬$N�������ˣ�\n",
			       this_player());
		set("exits/north", __DIR__"houyuan");
		this_player()->set("neili",n - 200);
		remove_call_out("close");
		call_out("close", 5);
	} else
	{
		message_vision("$N���һ���������������ʲôҲû��������"
			       "��$N����������ǿ��\n", this_player());
		this_player()->set("neili", 0);
	}
	return 1;
}

void close()
{
	message("vision","���ϵ�שͷ�߿�ϡ�ﻩ��̮���������ֵ�"
		"ס�˺��š�\n", this_object());
	delete("exits/north");
}
