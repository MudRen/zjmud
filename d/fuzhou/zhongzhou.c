// Room: /d/fuzhou/zhongzhou.c

inherit ROOM;

void create()
{
	set("short", "������");
	set("long", @LONG
�����ź�Խ����������ƽ��������ˮ�����֡�����Ϊһ
С��������ˮ���˼ҡ�
LONG );
	set("exits", ([
		"north" : __DIR__"nanmen",
		"south" : __DIR__"puxian",
	]));
	set("outdoors", "fuzhou");
	setup();
}

