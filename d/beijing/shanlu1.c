
inherit ROOM;

void create()
{
	set("short", "ɽ·");
	set("long", @LONG
�����ǻ�����ɽ·��ֻ��һ��������᫵�С����
LONG );
	set("exits", ([
		"northup" : __DIR__"shanlu2",
		"eastdown": __DIR__"zhuang1",
	]));
 	set("outdoors", "beijing");
	setup();
}
