// Room: /d/xiakedao/xkroad3.c
inherit BUILD_ROOM;
void create()
{
	set("short", "ƽԭС·");
	set("long", @LONG
�������齭�����޵�ƽԭС·�ϡ��˴��������֮�磬�л���֮
��������������ģ���紾�ӡ�������������ز���
LONG );
	set("outdoors", "nanhai");
	set("exits", ([
		"north"   : "/d/foshan/southgate",
		"south"   : __DIR__"xkroad4",
	]));
	set("max_room", 5);
	setup();
}
