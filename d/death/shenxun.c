//by ���� ranger's ednpc tools.
// shenxun.c

#include <ansi.h>
inherit ROOM;

void create()
{
	set("short","������");
	set("long","�����������ң�������򶫷�����qq���룺770340�������������ϡ�");
	set("exits", ([
		"north" : __DIR__"block",
	]));
	set("objects", ([
	]));
	setup();
}
void init()
{
	if (!wizardp(this_player()))
	{
		this_player()->set("startroom", "/d/death/block");
		add_action("discmds",({"use","eat","fly","research","yanjiu","jiqu","derive","suicide","jobto","myshop","study","inventory","sleep","kill","fight","hit","conjure","expell","perform","prcatice","fly","exercise","respirate"}));
	}
}
int discmds()
{
	tell_object(this_player(),"������ʵ���Űɣ�����\n");
	return 1;
}
