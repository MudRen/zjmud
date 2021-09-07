//Room: xubufang.c

inherit ROOM;

void create ()
{
	set ("short", "Ѳ����");
	set ("long", @LONG
�����ǳ�������ά���ΰ���Ѳ�������ĵط������ſڷ���������ͭ
ʨ��������һ��������ǽ�����Ű�ɫ���ᣬ��úܺ񣬷·�Ը�˿���
��ǽ��ʯ�ڣ�����������ͭ���������м�����ü��Ŀ�����������Ѳ��
����һ���ƺ���������ʲô���ϱ���һ��С�ţ��ƺ���������
LONG);
	set("exits", ([
		"west" : __DIR__"fengxu5",
	]));
	set("objects", ([
		__DIR__"npc/butou"  : 1,
		__DIR__"npc/guanbing" : 2,
	]));

	setup();
}

void init()
{
	add_action("do_open", "open");
}

int do_open(string arg)
{
	object me, key, nroom;
	me = this_player();
	if (! arg || arg != "door")
		return notify_fail("��Ҫ��ʲô��\n");

	if (! (key = present("laofang key", me)))
		return notify_fail("��û�п�����ŵ�Կ�ס�\n");

	if (! (nroom = find_object(__DIR__"laofang")))
	      	nroom = load_object(__DIR__"laofang");

	set("exits/south", __DIR__"laofang");
	message("vision", "ֻ�����꣡һ����Կ�׶��ˡ���"
		"�������Ѿ����ˡ�\n", this_object() );
	me->set_temp("used_laofang_key", 1);
	destruct(key);
	return 1;
}
