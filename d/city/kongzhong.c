// Room: /city/kongzhong.c

inherit ROOM;
void create()
{
	set("short", "����");
	set("long", @LONG
�������ɸ߿գ���ΧƮ���ż�����ơ�
ż���ɹ���ֻ�׵�
LONG
	);
	set("outdoors", "city");
/*
	set("objects", ([
		CLASS_D("ouyang") + "/ouyangke" : 1,
	]));
	set("exits", ([
		"east"  : __DIR__"kedian",
		"south" : __DIR__"guangchang",
		"west"  : __DIR__"qianzhuang",
		"north" : __DIR__"beidajie2",
	]));
*/
	setup();
}
