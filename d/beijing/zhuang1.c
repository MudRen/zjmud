
inherit ROOM;

void create()
{
	set("short", "С·");
	set("long", @LONG
������һ��С·�ϡ�ǰ���·��᫣����˺��١�������һ������
��С��·��ɽ��
LONG );
	set("exits", ([
		"southwest" : __DIR__"road1",
		"north"     : __DIR__"zhuang2",
		"westup"    : __DIR__"shanlu1",
	]));
	set("objects", ([
		"/d/taishan/npc/seng-ren" : 1,
	]));
 	set("outdoors", "beijing");
	setup();
}
