inherit ROOM;

void create()
{
	set("short", "������");
	set("long", @LONG
�����Ǳ������������⡣����������ɷ�����֡�
LONG );
	set("exits", ([
		"east" : __DIR__"xichengmen",
		"west" : "/d/heimuya/road3",
		"north" : __DIR__"liandan_lin1",
		//"south" : __DIR__"liandan_lin2",
	]));
	set("outdoors", "beijing");
	setup();
}
