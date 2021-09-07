// liuzhuang.c
#include <room.h>
inherit ROOM;
int do_knock(string arg);

void create()
{
	set("short", "��ׯ");
	set("long", @LONG
ׯ԰�Ĵ������ǡ���ׯ���������֡�����(gate)���գ����澲��
�ĵ�һ��������û�С�
LONG);
	set("exits", ([
	    	"east"  : __DIR__"dadao3",
		"south" : __DIR__"liuzhuang1",
		"north" : __DIR__"liuzhuang2",
	]));
	set("item_desc", ([
	   	"�����š�" : "���Ĵ��Ž����ţ�����(knock)���ɡ�\n"
			ZJOBACTS2+ZJMENUF(2,2,8,30)"����:knock\n",
	]));
	set("objects", ([
		__DIR__"npc/guanjia" : 1,
		__DIR__"npc/jiading" : 2,
	]));
	setup();
}

void init()
{
	add_action("do_knock", "knock");
}

int do_knock(string arg)
{
	object me;

	me = this_player();
	message_vision("$N���ˣ��ˣ��ˣ����������������ţ�������ȴһ�㶯����û�С�\n", me);
	return 1;
}

