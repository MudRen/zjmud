// sroad3.c
inherit ROOM;
void create()
{
	set("short", "ɽ·");
	set("long", @LONG
�����ǿ��������ĳ�ɽ���룬��ʯ��ᾡ�������ȥ���Ǵ�����Ե�ˡ�
������һ��ѩɽ�������ơ�·������һ����ѩ��(hollow)��
LONG );
	set("exits", ([
		"eastdown"  : __DIR__"sroad2",
		"northdown"  : __DIR__"nroad1",
		"westup"    : __DIR__"sroad4",
	]));

	set("item_desc",([
		"��ѩ�ӡ�"  : "һ��ѩ�ӣ��ƺ�������(jump)��ȥ��\n"
		ZJOBACTS2"����ȥ:jump hollow\n",
	]));
	set("outdoors", "xuedao");
	setup();
}

void init()
{
	add_action("do_jump","jump");
}

int do_jump(string arg)
{
	object guo;
	if (arg == "hollow")
	{
		message_vision("$N����������������ѩ����һ����žߴһ��ˤ���ӵס�\n",this_player());
		this_player()->move(__DIR__"hollow");
	}
	else
	{
		message_vision("$N��������������ѩ����һ����ſ�ڵ����ˡ�\n",this_player());
	}
	return 1;
}

