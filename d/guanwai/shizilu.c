// /guanwai/shizilu.c

inherit ROOM;

void create()
{
	set("short", "ʯ·");
	set("long", @LONG
����һ����ʯ���̵�С·�������������Ƶģ�ǽ�ڶ���Щ�����ˣ�
����ȥ��Щ���ۣ���������ȴƮ�����������������ǳ�������������
һ���Ե���Щ������СԺ�ӣ��ƺ�ûʲô������ʱ��ʱ��һЩ���ҵ�
���ӴҴҶ�����
LONG );
	set("exits", ([
		"south" : __DIR__"houyuan",
		"west"  : __DIR__"chufang",
		"east"  : __DIR__"taxue",
	]));

	set("outdoor", "guanwai");
	setup();
}
