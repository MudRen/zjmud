// Room: /d/xiakedao/xkroad5.c
#include <ansi.h>

inherit ROOM;

void create()
{
	set("short", "���");
	set("long", @LONG
�����Ǹ�СС��ۡ����溣��Ư���ż���С����̧������������
�����ޱ��޼ʡ���Ÿ�ӹ��˼⣬������Ȼ���м������������Ĵ���
���ߣ�����ͣ����һЩС��(boat)��
LONG );
	set("outdoors", "nanhai");

	set("exits", ([
		"east" : __DIR__"xkroad4",
	]));

	set("objects", ([
		__DIR__"npc/renter" : 1,
	]));

	set("item_desc", ([
		"���󴬡�" : "�������͵�������ϵ�Ĵ󴬡����ϵĿ���ֻҪ�ϴ�(enter)�Ϳ���ȥ���͵���\n"
		ZJOBACTS2"�ϴ�:enter boat\n",
	]));

	set("no_fight", 1);

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
	message_vision("�������𷫣��������Ϸ����С�\n", ob);
	ob->move("/d/xiakedao/duchuan");
	tell_object(ob, BLU "���ں��Ϻ�����һ����......."NOR"\n" ) ;
	call_out("home", 7, ob);
	return 1;
}

void home(object ob)
{
	if (! objectp(ob))
		return;

	tell_object(ob, "�����ڵִ����Ϻ����ߡ������´�����\n");
	ob->move (__DIR__"haitan");
	message("vision", ob->name() + "����С�ۣ����˹�����\n",environment(ob), ob);
}
