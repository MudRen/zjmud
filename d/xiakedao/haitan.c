// haitan.c

#include <ansi.h>

inherit ROOM;

void create()
{
	set("short", "��̲");
	set("long", @LONG
����������͵��ˡ�������һ���޼ʵĴ󺣣���������һƬ���֡�
���ϵĿ����ƺ��ǳ����ʣ���ʪ�ĺ����д���һ�ɻ��㣬���Ǻô��
һƬɳ̲������ʯ����ͣ����ʮ���Ҵ�С�Ĵ�ֻ(boat)��
LONG );

	set("item_desc", ([
		"���󴬡�" : "�������͵�������ϵ�Ĵ󴬡����ϵĿ���ֻҪ�ϴ�(enter)�Ϳ��Ի���ԭ��\n"
		ZJOBACTS2"�ϴ�:enter boat\n",
	]));

	set("exits", ([
		"south" :__DIR__"lin1",
	]));

	set("objects", ([
		__DIR__"npc/shizhe" : 1,
	]));

	set("outdoors", "xiakedao");
	setup();
}

void init()
{
	add_action("do_enter", "enter");
}

int do_enter(string arg)
{
	object ob;
	string dir;

	if (arg != "boat")
		return notify_fail("��Ҫȥ�Ķ���\n" );

	ob = this_player();
	message_vision("����һ�������ϴ���æ����һ��������ඣ�\n", ob);
	message_vision("�������𷫣������򱱷����С�\n", ob);
	ob->move("/d/xiakedao/dahai") ;
	tell_object(ob, BLU "���ں��Ϻ�����һ��һҹ......."NOR"\n" ) ;
	call_out("home", 10, ob);
	return 1;
}

void home(object ob)
{
	if (! objectp(ob))
		return;

	tell_object(ob, "�����ڵִ����Ϻ����ߡ������´�����\n");
	ob->move (__DIR__"haigang");
	message("vision", ob->name() + "���˺��������˹�����\n",
		environment(ob), ob);
}
