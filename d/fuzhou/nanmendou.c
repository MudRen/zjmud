// Room: /d/fuzhou/nanmendou.c
inherit ROOM;
void create()
{
	set("short", "���Ŷ�");
	set("long", @LONG
���Ŷ�������һ��޴���ţ�����Ҷï��Ũ���ڸ���Ķ��
�������ֿ��ڱ���ʵ��©�չ⡣����������һС����
��ظ��¡�
LONG );
	set("exits", ([ /* sizeof() == 1 */
	    "north"  : __DIR__"nandajie",
	    "south"  : __DIR__"nanmen",
	    "west"   : __DIR__"shiqiao",
	    "east"   : __DIR__"xiaochang",
	]));
	set("item_desc", ([
	    "��������"   : "һ�ž޴�Ĺ��ţ��±���������һ�������İ��Ķ�Ѩ��\n"
		ZJOBACTS2"�궴:enter dong\n",
	]));
	set("outdoors", "fuzhou");
	setup();
}

void init()
{
	add_action("do_enter", "enter");
	add_action("do_enter", "zuan");
}

int do_enter(string arg)
{
	object me;

	me = this_player();
	if (! arg || arg == "") return 0;
	if (arg == "dong")
	{
		if (me->query("family/family_name") == "ؤ��")
		{
			message("vision",
				me->name() + "����ؤ�����ǹ���һ�������������˽�ȥ��\n",
				environment(me), me);
			me->move("/d/gaibang/underfz");
			message("vision",
				me->name() + "�Ӷ������˽�����\n",
				environment(me), ({me}) );
			return 1;
		} else
			return notify_fail("��ôС�Ķ�������ý�ȥ��\n");
       }
}
