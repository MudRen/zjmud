//      shenghu.c ʥ��
inherit ROOM;

void create()
{
	set("short", "ʥ��");
	set("long", @LONG
��ǰ����������ʥ���������ĺ��浹Ӱ������Ͱ��ƣ�
����ˮ�������Ŀ�������Զ����̻Ի͵�ѩɽ��������
������Զ���Ǽ�������Ĵ�ѩɽ��������ߴ������ɽ��
�ഫɽ�������ɾ�ס��ѩɽ���ڻ���ѩˮ��������С�
LONG );
	set("resource/water", 1);
	set("exits", ([
		"south" : __DIR__"tulu3",
		"east"  : __DIR__"hubian1",
	]));

	set("outdoors", "xueshan");

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
