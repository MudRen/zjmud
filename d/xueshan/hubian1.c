//      hubian1.c ����С·
inherit ROOM;

void create()
{
	set("short", "����С·");
	set("long", @LONG
����ʥ���ߵ�С·��·��ĺ�ˮ��Ϊ�峺��������ӳ
�Ű׶�ѩɽ�Գ�һƬ�����ĵ�������
LONG );
	set("outdoors", "xueshan");
	set("exits", ([
		"east" : __DIR__"hubian2",
		"west" : __DIR__"shenghu",
	]));
	setup();
}

int valid_leave(object me, string dir)
{
	if (! playerp(me))
		return ::valid_leave(me, dir);

	if (random(3))
	{
		write("��ͻȻ������ǰ�ľ�����Щ���ҡ�\n");
		return -1;
	}
	return ::valid_leave(me, dir);
}
