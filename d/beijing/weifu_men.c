inherit ROOM;
#include <ansi.h>

void create()
{
	set("short","Τ������");
	set("long", @LONG
������ǵ�����һ�購��������������Ϊ��һ��¹��������Τ��ү�ľ�լ��
�������һ�������ûʵĸߴ��������������ǰ��������������ͷ�ߴ��
ʯʨ�ӡ����Ϻ���һ����ң������Ǵ�ѧʿ����ͼ�ױ���д�ġ�¹����������
����ʴ��֡���ǰվ�Ÿ�Τ����������
LONG );
	set("exits", ([
		"west" : __DIR__"weifu_zoulang1",
		"east" : __DIR__"wang_1",
	]));
	set("objects", ([
		__DIR__"npc/lilishi" : 1,
	]));
	setup();
}

int valid_leave(object me, string dir)
{
	if (objectp(present("li lishi", environment(me))) && dir == "west")
		return notify_fail("�������ȵ������ҹ䣬��ү���첻���͡�\n\n");
	return ::valid_leave(me, dir);
}
