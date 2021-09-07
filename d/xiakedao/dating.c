//ROOM /d/xiakedao/dating.c

inherit ROOM;

int do_push(string arg);
void create()
{
	set("short", "����");
	set("long", @LONG
���ǡ����͵����Ĵ��������ܵ�����ţ�������������һ����
���硣���ڰ���һ���������ӣ�������������������������º��Ӵ�
������ȥ����������������
LONG );

	set("item_desc",([
		"�����硿" : "����һ���ǳ�Ư������ʯ���磬��֪����(push)����������ʲô��\n"
		ZJOBACTS2"�ƿ�:push pingfeng\n",
	]));

	set("exits", ([
		"north" : __DIR__"shidong5",
		"east"  : __DIR__"shufang",
		"west"  : __DIR__"wuqiku",
	]));

	set("objects",([
		__DIR__"npc/dizi" : 4,
	]));
	setup();

	set("no_fight", 1);
}

void init()
{
	add_action("do_push","push");
}

int do_push(string arg)
{
	object me = this_player();
	int n, i;

	if (! arg || arg != "pingfeng")
	{
		write("��Ҫ��ʲôѽ��\n");
		return 1;
	}

	n = me->query("neili");
	message_vision("$N������ǰվ��������һ���������ֽ���ס���硣\n", me);
	if (n >= 100)
	{
		message_vision("$N����һ�������͵�һ�ƣ�ֻ������֮��¶��һ������������\n", me);
		set("exits/south", __DIR__"yongdao3");
		me->deletet("neili", -100);
		remove_call_out("close");
		call_out("close", 5, this_object());
	} else
	{
		message_vision("$N����һ�������͵�һ�ƣ�����ȴ˿��û����\n", me);
		me->set("neili", 0);
	}
	return 1;
}

void close(object room)
{
	message("vision", "�����Զ��ֺ����ˡ�\n", room);
	room->delete("exits/south");
}

