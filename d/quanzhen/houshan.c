// houshan.c ��ɽ
inherit ROOM;

void create()
{
	set("short", "��ɽ");
	set("long", @LONG
�����Ѿ���������������������ɽ�ĺ�ɽ���������ﻨ�㣬
�������£�ɽ��Ҳƽ���ö��ˡ�
LONG
	);
	set("outdoors", "quanzhen");
	set("exits", ([
		"west" : __DIR__"jingxiushi",
		"northeast" : __DIR__"xiaolu1",
	]));
	set("no_clean_up", 0);
	setup();
}

