// Room: /city/dongdajie2.c
// YZC 1995/12/04 

inherit ROOM;

void create()
{
	set("short", "�����");
	set("long", @LONG
�����ڶ�����ϣ����ż�ʵ����ʯ����档������һ�����ֺŵ�ҩ
�̣��ϱ��Ǵ����̣�����������������Զ����������
LONG );
	set("outdoors", "city");
	set("exits", ([
		"east"  : __DIR__"dongmen",
		"south" : __DIR__"datiepu",
		"west"  : __DIR__"dongdajie1",
		"north" : __DIR__"yaopu",
	]));

	setup();
}

