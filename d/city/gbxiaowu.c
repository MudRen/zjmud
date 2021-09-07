// Room: gbdixiaowu.c

inherit ROOM;
void create()
{
	set("short", "�ּ�С��");
	set("long", @LONG
���߽���һ��С�ݡ�����ǽ�ڶ�����������ɣ�������һ���޼ʵ����֡�
��������Ρ����̾�Ϊ���ơ���һ���˱Ƕ����Ĺ�����ζ��ȴ�Ե��������ŵ�
���׸���롣
LONG );
	set("exits", ([ /* sizeof() == 1 */
		"west" : __DIR__"gbandao",
		"out"  : __DIR__"ml7",
		"east" : "/d/gaibang/undertre.c"
	]));
	set("objects", ([
		CLASS_D("gaibang") + "/hong" : 1,
		__DIR__"obj/zhubang": 1,
		__DIR__"obj/gourou": 1,
		__DIR__"obj/jiudai": 1,
		__DIR__"obj/jitui": 1
	]));

	set("valid_startroom", 1);
	set("sleep_room", 1);
	setup();
}

int valid_leave(object me, string dir)
{
	object ob;

	if (dir == "west" && me->query("family/family_name") != "ؤ��" &&
	    objectp(ob = present("hong qigong", this_object())) &&
	    living(ob))
		return notify_fail("���߹���ס�㣺�����ߡ�\n");

	return ::valid_leave(me, dir);
}
