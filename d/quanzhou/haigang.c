#include <ansi.h>

inherit ROOM;

void create()
{
	set("short", "����");
	set("long", @LONG
�����ǳ����ıؾ�֮�أ�Ȫ�ݺųƶ�����һ��ۣ���
����˿��֮·����㣬�۴�(chuan) ʮ�ַ��㡣
LONG );
	set("exits", ([
		"west" : __DIR__"zhongxin",
	]));
	set("item_desc", ([
		"chuan" : "һ���󺣴�����Զ��û�����Ĵ��ɲ��С�\n",
	]));
	set("objects", ([
		__DIR__"npc/boy": 2,
		__DIR__"npc/girl": 1,
		__DIR__"npc/chuanfu" : 1,
	]));

	set("outdoors", "quanzhou");
	setup();
}

void init()
{
	add_action("do_enter", "enter");
}

int do_enter(string arg)
{
	object ob ;
	string dir;

	ob = this_player();
	if (arg !="chuan")
	{
		tell_object(ob, "��Ҫȥ�Ķ���\n" );
		return 1;
	}

	message_vision("����һ�������ϴ���æ����һ��������ඣ�\n", ob);
	message_vision("�������𷫣������򶫷����С�\n", ob);
	ob->move(__DIR__"dahai");
	tell_object(ob, BLU "���ں��Ϻ����˺ܾúܾ�......."NOR"\n");
	call_out("tpenghu", 10 , ob);
	return 1 ;
}

void tpenghu(object ob)
{
	if (! objectp(ob) || find_object(__DIR__"dahai") != environment(ob))
		return;

	tell_object(ob, "�����ڵִ��˴���һ�����졣�����´�����\n");
	ob->move(__DIR__"penghu");
}
