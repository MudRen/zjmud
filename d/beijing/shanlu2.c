
inherit ROOM;

void create()
{
	set("short", "ɽ·");
	set("long", @LONG
�����ǻ�����ɽ·��ֻ��һ��������᫵�С��������������̣�����
���ñ������쬵ġ�
LONG );
	set("exits", ([
		"westup"    : __DIR__"shanlu3",
		"southdown" : __DIR__"shanlu1",
	]));
 	set("outdoors", "beijing");
	setup();
}
