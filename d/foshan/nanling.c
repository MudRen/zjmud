// Room: /d/foshan/nanling.c ����ɽ��
// Modified by Java on Feb.14.1998
inherit BUILD_ROOM;

void create()
{
	set("short", "����ɽ��");
	set("long", @LONG
�����������һ��ɽ�ڡ�������Ƿ�ɽ�ˣ������Ǻ�ب���Ϲ�
�������롣����������ȣ����������쳤������ҲԶ����ԭ�ˡ�
LONG );
	set("outdoors", "foshan");
	set("exits", ([
		"northup" : "/d/henshan/hsroad9",
		"south"   : __DIR__"northgate",
	]));
	setup();
	replace_program(BUILD_ROOM);
}

