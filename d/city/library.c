// literate.c

inherit ROOM;

void create()
{
	set("short", "ͼ���");
	set("long", @LONG
����һ�伫Ϊ���ε�ͼ���ղ��ҡ�
LONG );
	set("exits", ([
		"south" : __DIR__"lichunyuan",
	]));
	setup();
}

