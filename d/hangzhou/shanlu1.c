// shanlu1.c
// Date: Nov.1997 by Venus

inherit BUILD_ROOM;

void create()
{
	set("short", "ɽ·");
	set("long", @LONG
һ�������߳�����ɽ·�������������������졣����ɽ·�ϣ�ֻ
�����Է�����������ɫ���ˡ�һʱ���㶼���˳�ס�������ͷ����ʱ
�н���Ͳ�����������ϱ㵽�������ã����¾��Ǵ����
LONG);
	set("exits", ([
		"southup"   : __DIR__"fajingsi",
		"northdown" : __DIR__"road2",
	]));
	set("outdoors", "hangzhou");
	set("max_room", 4);
	setup();
}
