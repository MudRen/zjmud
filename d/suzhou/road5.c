// Room: /d/suzhou/road5.c
// Date: May 31, 98  Java

inherit BUILD_ROOM;

void create()
{
	set("short", "��ʯ�ٵ�");
	set("long", @LONG
������һ����ʯ����ϣ����������ǳ���æ����ʱ������
������ҴҶ���������������ݳ��ˡ����ϱ�ԶԶ��ȥ������
�������׷���׺����������������̫���ˡ�
LONG );
	set("outdoors", "suzhou");
	set("exits", ([
		"north"     : __DIR__"nanmen",
		"southwest" : "/d/yanziwu/hupan",
		"east"      : "/d/item/road1",
	]));

	set("max_room", 3);

	setup();
	replace_program(BUILD_ROOM);
}
